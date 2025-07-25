

#include <stdint.h>
#include <xcb/xcb.h>

// opaque struct (full definition in .c)
typedef struct GrayShm GrayShm;

// ctx: context to hold state
GrayShm *gray_shm_create(xcb_window_t xid, int width, int height);
void     gray_shm_resize(GrayShm *ctx, int width, int height);
void     gray_shm_present(GrayShm *ctx, const uint8_t *frame); // frame is width*height bytes
void     gray_shm_commit(GrayShm *ctx);
void     gray_shm_commit_rect(GrayShm *ctx, int x, int y, int width, int height);
void     gray_shm_destroy(GrayShm *ctx);

xcb_connection_t *gray_shm_get_connection(GrayShm *ctx);

int      gray_shm_get_width(GrayShm *ctx);
int      gray_shm_get_height(GrayShm *ctx);
uint8_t *gray_shm_get_buffer(GrayShm *ctx);
