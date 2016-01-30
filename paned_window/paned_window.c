#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<gtk/gtk.h>

GtkWidget* createList(void){

    GtkWidget *scrolled_window;
    GtkWidget *tree_view;
    GtkListStore *model;
    GtkTreeIter iter;
    GtkCellRenderer *cell;
    GtkTreeViewColumn *column;
    
    int i;
    
    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    
    //https://developer.gnome.org/gtk3/stable/GtkListStore.html
    model = gtk_list_store_new(1, G_TYPE_STRING);
    tree_view = gtk_tree_view_new();
    gtk_container_add(GTK_CONTAINER(scrolled_window), tree_view);
    gtk_tree_view_set_model(GTK_TREE_VIEW(tree_view), GTK_TREE_MODEL(model));
    gtk_widget_show(tree_view);
    
    for (i = 0; i < 10; ++i){
        gchar* msg = g_strdup_printf("Message #%d", i);
        gtk_list_store_append(GTK_LIST_STORE(model), &iter);
        //https://developer.gnome.org/gtk3/stable/GtkListStore.html
        gtk_list_store_set(GTK_LIST_STORE(model), &iter, 0, msg, -1);
        g_free(msg);
    }
    
    cell = gtk_cell_renderer_text_new();
    
    column = gtk_tree_view_column_new_with_attributes("Messages", cell, "text", 0, NULL);
    
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), GTK_TREE_VIEW_COLUMN(column));
    
    return scrolled_window;
    
}

static void insert_text(GtkTextBuffer* buffer){
    GtkTextIter iter;
    
    gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
    
    gtk_text_buffer_insert(buffer, &iter,
        "From: abc@gmail.com\n"
        "To: def@nasa.gov\n"
        "Subject: OOXX\n"
        "dererg feuriu uvernfuep rvufer\n"
        "fmerninrefneurinf  fuerifnuer\n"
        " -Path\n", -1
    );
}

static GtkWidget* create_text(void){
    GtkWidget* scrolled_window;
    GtkWidget* view;
    GtkTextBuffer *buffer;
    
    view = gtk_text_view_new();   
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));
    
    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    
    gtk_container_add(GTK_CONTAINER(scrolled_window), view);
    
    insert_text(buffer);
    
    gtk_widget_show_all(scrolled_window);
    
    return scrolled_window;
}

int main(int argc, char const *argv[]) {
    GtkWidget *window;
    GtkWidget *vpaned;
    GtkWidget *list;
    GtkWidget *text;
    
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Paned Window");

    g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    vpaned = gtk_vpaned_new();
    gtk_container_add(GTK_CONTAINER(window), vpaned);
    gtk_widget_show(vpaned);
    
    list = createList();
    gtk_paned_add1(GTK_PANED(vpaned), list);
    gtk_widget_show(list);
    
    text = create_text();
    gtk_paned_add2(GTK_PANED(vpaned), text);
    gtk_widget_show(text);
    
    /* Showing the window last so everything pops up at once. */
    gtk_widget_show(window);
    
    /* And of course, our main function. */
    gtk_main();
    
    return 0;
}
