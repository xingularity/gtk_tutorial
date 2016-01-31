#include<stdio.h>
#include<gtk/gtk.h>

//rotate the positions of the notebook tabs.
static void rotate_book(GtkButton *button, GtkNotebook *notebook){
    gtk_notebook_set_tab_pos(notebook, (notebook->tab_pos + 1) % 4);
}

static void tabsborder_book(GtkButton *button, GtkNotebook* notebook){
    gint tval = FALSE;
    gint bval = FALSE;
    
    if (notebook -> show_tabs == 0)
        tval = TRUE;
    else
        bval = TRUE;
    
    gtk_notebook_set_show_tabs(notebook, tval);
    gtk_notebook_set_show_border(notebook, bval);
}

static void remove_book(GtkButton *button, GtkNotebook* notebook){
    gint page;
    
    page = gtk_notebook_get_current_page(notebook);
    gtk_notebook_remove_page(notebook, page);
    
    /* !!!Need to redraw the widget!!! */
    gtk_widget_queue_draw(GTK_WIDGET(notebook));
}

static gboolean delete(GtkWidget *widget, GtkWidget *event, gpointer data){
    gtk_main_quit();
    return FALSE;
}

int main(int argc, char const *argv[]) {
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *table;
    GtkWidget *notebook;
    GtkWidget *frame;
    GtkWidget *label;
    GtkWidget *checkbutton;
    int i;
    char bufferf[32];
    char bufferl[32];
    
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Button Boxes");

    g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    
    table = gtk_table_new(3, 6, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table);
    
    notebook = gtk_notebook_new();
    gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), GTK_POS_TOP);
    gtk_table_attach_defaults(GTK_TABLE (table), notebook, 0, 6, 0, 1);
    gtk_widget_show(notebook);
    
    //append pages
    for(i = 0; i < 5; ++i){
        snprintf(bufferf, sizeof(bufferf), "Append Frame %d", i + 1);
        snprintf(bufferl, sizeof(bufferl), "Page %d", i + 1);
        
        frame = gtk_frame_new(bufferf);
        gtk_container_set_border_width(GTK_CONTAINER(frame), 10);
        gtk_widget_set_size_request(frame, 100, 75);
        gtk_widget_show(frame);
        
        label = gtk_label_new(bufferf);
        gtk_container_add(GTK_CONTAINER(frame), label);
        gtk_widget_show(label);
        
        label = gtk_label_new(bufferl);
        gtk_notebook_append_page(GTK_NOTEBOOK(notebook), frame, label);
    }
    
    checkbutton = gtk_button_new_with_label("Check me please!");
    gtk_widget_set_size_request(checkbutton, 100, 75);
    gtk_widget_show(checkbutton);
    
    //prepend pages
    for(i = 0; i < 5; ++i){
        snprintf(bufferf, sizeof(bufferf), "Prepend Frame %d", i + 1);
        snprintf(bufferl, sizeof(bufferl), "Pre_Page %d", i + 1);
        
        frame = gtk_frame_new(bufferf);
        gtk_container_set_border_width(GTK_CONTAINER(frame), 10);
        gtk_widget_set_size_request(frame, 100, 75);
        gtk_widget_show(frame);
        
        label = gtk_label_new(bufferf);
        gtk_container_add(GTK_CONTAINER(frame), label);
        gtk_widget_show(label);
        
        label = gtk_label_new(bufferl);
        gtk_notebook_append_page(GTK_NOTEBOOK(notebook), frame, label);
    }
    
    gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook), 3);
    
    button = gtk_button_new_with_label("Close");
    g_signal_connect(button, "clicked", G_CALLBACK(delete), NULL);
    gtk_table_attach_defaults(GTK_TABLE(table), button, 0, 1, 1, 2);
    gtk_widget_show(button);
    
    button = gtk_button_new_with_label("Next page");
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_notebook_next_page), notebook);
    gtk_table_attach_defaults(GTK_TABLE(table), button, 1, 2, 1, 2);
    gtk_widget_show(button);

    button = gtk_button_new_with_label("Prev page");
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_notebook_prev_page), notebook);
    gtk_table_attach_defaults(GTK_TABLE(table), button, 2, 3, 1, 2);
    gtk_widget_show(button);

    button = gtk_button_new_with_label("tab position");
    g_signal_connect(button, "clicked", G_CALLBACK(rotate_book), notebook);
    gtk_table_attach_defaults(GTK_TABLE(table), button, 3, 4, 1, 2);
    gtk_widget_show(button);

    button = gtk_button_new_with_label("tabs/border on/off");
    g_signal_connect(button, "clicked", G_CALLBACK(tabsborder_book), notebook);
    gtk_table_attach_defaults(GTK_TABLE(table), button, 4, 5, 1, 2);
    gtk_widget_show(button);
    
    button = gtk_button_new_with_label("remove page");
    g_signal_connect(button, "clicked", G_CALLBACK(remove_book), notebook);
    gtk_table_attach_defaults(GTK_TABLE(table), button, 5, 6, 1, 2);
    gtk_widget_show(button);
    
    gtk_widget_show(table);
    /* Showing the window last so everything pops up at once. */
    gtk_widget_show_all(window);
    
    /* And of course, our main function. */
    gtk_main();
    
    return 0;
}
