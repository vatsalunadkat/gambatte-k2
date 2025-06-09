#include <gtk/gtk.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAX_PATH_LEN 1024

/* current directory & final selection */
static gchar *current_dir = NULL;
static gchar *selected_path = NULL;

/* our clist and its “row → fullpath” data */
static GtkCList *clist = NULL;
static gint selected_row = -1;

/* 1) signal handler */
static void
on_clist_row_selected(GtkCList  *clist,
                      gint        row,
                      gint        column,
                      GdkEvent   *event,
                      gpointer    user_data)
{
    GtkWidget *dlg = GTK_WIDGET(user_data);
    selected_row = row;

    gchar *path = gtk_clist_get_row_data(clist, row);
    struct stat st;
    if (stat(path, &st) == 0 && !S_ISDIR(st.st_mode)) {
        // It's a file, accept the dialog
    }
    gtk_dialog_response(GTK_DIALOG(dlg), GTK_RESPONSE_ACCEPT);
    
}

/* Populate the GtkCList from current_dir */
static void
update_file_list(void)
{
    GDir *d;
    const gchar *name;
    gchar full[MAX_PATH_LEN];
    int row = 0;
    selected_row = -1;

    /* Clear out old rows & free their row-data */
    if (clist)
    {
        int n_rows = GTK_CLIST (clist)->rows;
        for (int i = 0; i < n_rows; i++)
        {
            gpointer old = gtk_clist_get_row_data(clist, i);
            g_free(old);
        }
        gtk_clist_clear(clist);
    }

    /* First entry: go up */
    row = gtk_clist_append(clist, (gchar*[]){"../"});
    gtk_clist_set_row_data(clist, row, g_strdup_printf("%s/..", current_dir));

    /* Open directory */
    d = g_dir_open(current_dir, 0, NULL);
    if (!d) return;
    /*
    while ((name = g_dir_read_name(d)))
    {
        // only dirs or .gb/.gbc files
        snprintf(full, sizeof(full), "%s/%s", current_dir, name);
        struct stat st;
        if (stat(full, &st) == 0 &&
           ( S_ISDIR(st.st_mode)
          || g_str_has_suffix(name, ".gb")
          || g_str_has_suffix(name, ".gbc")))
        {
            row = gtk_clist_append(clist, (gchar*[]){(gchar*)name});
            gtk_clist_set_row_data(clist, row, g_strdup(full));
        }
    }

    g_dir_close(d);
    */
    // Collect names into a GList
    GList *file_list = NULL;
    while ((name = g_dir_read_name(d)))
    {
        snprintf(full, sizeof(full), "%s/%s", current_dir, name);
        struct stat st;
        if (stat(full, &st) == 0 &&
           ( S_ISDIR(st.st_mode)
          || g_str_has_suffix(name, ".gb")
          || g_str_has_suffix(name, ".gbc")))
        {
            file_list = g_list_prepend(file_list, g_strdup(name));
        }
    }
    g_dir_close(d);

    // Sort the list alphabetically (case-insensitive)
    file_list = g_list_sort(file_list, (GCompareFunc)g_ascii_strcasecmp);

    // Add sorted entries to the clist
    for (GList *l = file_list; l != NULL; l = l->next) {
        name = l->data;
        snprintf(full, sizeof(full), "%s/%s", current_dir, name);
        row = gtk_clist_append(clist, (gchar*[]){(gchar*)name});
        gtk_clist_set_row_data(clist, row, g_strdup(full));
        g_free(l->data); // Free the strdup'd name
    }
    g_list_free(file_list);



}

/* Run the dialog — returns a malloc’d string or NULL */
char *
simple_file_chooser_list(GtkWindow *parent)
{
    GtkWidget *dlg, *sw;
    gint       resp;

    if (!current_dir)
        current_dir = g_strdup("/mnt/us"); // g_get_current_dir();

    selected_path = NULL;
    /* 1) Create the dialog */
    dlg = gtk_dialog_new_with_buttons(
       "L:A_N:application_ID:filepicker",
        parent,
        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
//        GTK_STOCK_OK,     GTK_RESPONSE_ACCEPT,
        NULL
    );

    /* 2) Create & pack the CList */
    sw    = gtk_scrolled_window_new(NULL, NULL);
    clist = GTK_CLIST(gtk_clist_new(1));
    gtk_clist_set_column_title(clist, 0, "Name");
    gtk_clist_set_selection_mode(clist, GTK_SELECTION_SINGLE);
    gtk_clist_set_row_height(clist, 40);

    gtk_scrolled_window_set_policy(
      GTK_SCROLLED_WINDOW(sw),
      GTK_POLICY_NEVER,
      GTK_POLICY_AUTOMATIC
    );
    gtk_widget_set_size_request(sw, 400, 600);

    gtk_container_add(GTK_CONTAINER(sw), GTK_WIDGET(clist));
    gtk_box_pack_start(
      GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(dlg))),
      sw, TRUE, TRUE, 0
    );
    /* connect the select_row signal once */
    g_signal_connect(clist, "select_row",
                     G_CALLBACK(on_clist_row_selected),
                     dlg);

    update_file_list();
    gtk_widget_show_all(dlg);

    while ((resp = gtk_dialog_run(GTK_DIALOG(dlg))) != GTK_RESPONSE_CANCEL)
    {
        if (resp == GTK_RESPONSE_ACCEPT && selected_row >= 0)
        {
            gchar *path = gtk_clist_get_row_data(clist, selected_row);
            struct stat st;
            if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
            {
                /* navigate into directory */
                g_free(current_dir);
                current_dir = g_strdup(path);
                update_file_list();
                continue;
            }
            /* selected a file */
            selected_path = g_strdup(path);
        }
        break;
    }

    gtk_widget_destroy(dlg);
    return selected_path;
}
