#include "gray_shm.h"
#include <xcb/xcb.h>
#include <xcb/shm.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

struct GrayShm {
    xcb_connection_t *conn;
    xcb_window_t      xid;
    xcb_shm_seg_t     seg;
    xcb_gcontext_t    gc;
    uint8_t          *shmaddr;
    int               w, h;
};

static void cleanup_shm(GrayShm *st)
{
    if (st->conn && st->seg) {
        xcb_shm_detach(st->conn, st->seg);
        xcb_flush(st->conn);
        st->seg = 0;
    }
    if (st->shmaddr) {
        shmdt(st->shmaddr);
        st->shmaddr = NULL;
    }
}

static void setup_shm_surface(GrayShm *st, int new_w, int new_h)
{
    cleanup_shm(st);

    st->w = new_w;
    st->h = new_h;

    if (st->w <= 0 || st->h <= 0)
        return;

    size_t shm_size = st->w * st->h;
    int shmid = shmget(IPC_PRIVATE, shm_size, IPC_CREAT | 0600);
    if (shmid < 0) {
        perror("shmget failed");
        return;
    }
    st->shmaddr = shmat(shmid, NULL, 0);

    st->seg = xcb_generate_id(st->conn);
    xcb_shm_attach(st->conn, st->seg, shmid, 0);
    xcb_flush(st->conn);

    shmctl(shmid, IPC_RMID, NULL);
}

GrayShm *gray_shm_create(xcb_window_t xid, int width, int height)
{
    GrayShm *st = calloc(1, sizeof(GrayShm));
    st->xid  = xid;
    st->conn = xcb_connect(NULL, NULL);

    if (xcb_connection_has_error(st->conn)) {
        free(st);
        return NULL;
    }

    xcb_screen_t *screen = xcb_setup_roots_iterator(
        xcb_get_setup(st->conn)).data;

    st->gc = xcb_generate_id(st->conn);
    uint32_t gc_values[] = { screen->black_pixel };
    xcb_create_gc(st->conn, st->gc, st->xid,
                  XCB_GC_FOREGROUND, gc_values);

    setup_shm_surface(st, width, height);
    return st;
}

void gray_shm_resize(GrayShm *st, int width, int height)
{
    if (width != st->w || height != st->h) {
        setup_shm_surface(st, width, height);
    }
}

uint8_t *gray_shm_get_buffer(GrayShm *st)
{
    return st->shmaddr;
}

void gray_shm_commit(GrayShm *st)
{
    if (!st->shmaddr) return;

    xcb_shm_put_image(
        st->conn,
        st->xid,
        st->gc,
        st->w, st->h,
        0, 0,
        st->w, st->h,
        0, 0,
        8,
        XCB_IMAGE_FORMAT_Z_PIXMAP,
        0,
        st->seg,
        0
    );
    xcb_flush(st->conn);
}

// https://github.com/gfxprim/gfxprim/blob/71f540762f7b179f2b2cf6e25b67fd70ff440311/libs/backends/gp_xcb.c#L198-L204
void gray_shm_commit_rect(GrayShm *st, int src_x, int src_y, int width, int height)
{
    if (!st->shmaddr) return;

    //xcb_void_cookie_t ck = xcb_shm_put_image_checked(
    xcb_shm_put_image(
        st->conn,
        st->xid,
        st->gc,
        st->w, st->h,
        src_x, src_y, // src_x, src_y: offset in shm (and in drawable)
        width, height,
        src_x, src_y, // dst_x, dst_y in window
        8,
        XCB_IMAGE_FORMAT_Z_PIXMAP,
        0,            // send_event
        st->seg,
        0
    );

    xcb_flush(st->conn);
    
    // xcb_generic_error_t *err = xcb_request_check(st->conn, ck);

    // if (err) {
    //     fprintf(stderr, "X error on SHM PutImage: code %d\n", err->error_code);
    //     free(err);
    // }    



    // while (1) {
    //   xcb_generic_event_t *ev = xcb_wait_for_event(st->conn);
    //   if (!ev) {
    //     fprintf(stderr, "Server connection dropped!\n");
    //     return;
    //   }
    //   if ((ev->response_type & ~0x80) == XCB_SHM_COMPLETION) {
    //     // arrived! we can free the event and break
    //     free(ev);
    //     break;
    //   }
    //   // some other event—ignore it
    //   free(ev);
    // }

}

void gray_shm_present(GrayShm *st, const uint8_t *frame)
{
    if (frame && st->shmaddr)
        memcpy(st->shmaddr, frame, st->w * st->h);
    gray_shm_commit(st);
}

xcb_connection_t *gray_shm_get_connection(GrayShm *st)
{
    return st->conn;
}

int gray_shm_get_width(GrayShm *st) { return st->w; }
int gray_shm_get_height(GrayShm *st) { return st->h; }

void gray_shm_destroy(GrayShm *st)
{
    cleanup_shm(st);
    if (st->conn)
        xcb_disconnect(st->conn);
    free(st);
}