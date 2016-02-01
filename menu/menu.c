#include<stdio.h>
#include<gtk/gtk.h>

static gboolean button_press(GtkWidget* widget, GdkEvent *event){
    if (event -> type == GDK_BUTTON_PRESS){
        GdkEventButton *bevent = (GdkEventButton*) event;
        //https://developer.gnome.org/gtk3/stable/GtkMenu.html
        gtk_menu_popup(GTK_MENU(widget), NULL, NULL, NULL, NULL, bevent -> button, bevent -> time);
        return TRUE;
    }
    return FALSE;
}

static void menuitem_response(gchar* string){
    printf("%s\n", string);
}

static void file_select_ok(GtkWidget *w, GtkFileSelection *fs){
    g_print("%s", gtk_file_selection_get_filename(GTK_FILE_SELECTION(fs)));
    gtk_widget_destroy(fs);
}

static void open_file_slector(GtkWidget* widget){
    GtkWidget *file_selector;
    file_selector = gtk_file_selection_new("Open file");
    g_signal_connect(GTK_FILE_SELECTION(file_selector) -> ok_button, "clicked", G_CALLBACK(file_select_ok), 
                     (gpointer) file_selector);
    g_signal_connect_swapped(GTK_FILE_SELECTION(file_selector) -> cancel_button, "clicked", G_CALLBACK(gtk_widget_destroy), 
                             (gpointer) file_selector);
    gtk_widget_show(file_selector);
}

int main(int argc, char const *argv[]) {
    GtkWidget *window;
    GtkWidget *menu;
    GtkWidget *menu_bar;
    GtkWidget *root_menu;
    GtkWidget *menu_item;
    GtkWidget *vbox;
    GtkWidget *button;
    int i;
    char buffer[128];
    
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Menu Items");

    g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_set_size_request(GTK_WIDGET(window), 200, 100);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    
    // Never use gtk_widget_show on menu
    menu = gtk_menu_new();
    
    snprintf(buffer, 128, "Open file");
    menu_item = gtk_menu_item_new_with_label(buffer);
    g_signal_connect(menu_item, "activate", G_CALLBACK(open_file_slector), NULL);
    gtk_widget_show(menu_item);

    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item);
    
    root_menu = gtk_menu_item_new_with_label("File");
    gtk_widget_show(root_menu);
    
    snprintf(buffer, 128, "Quit");
    menu_item = gtk_menu_item_new_with_label(buffer);
    g_signal_connect(menu_item, "activate", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show(menu_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item);
    
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(root_menu), menu);
    
    vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show(vbox);
    
    menu_bar = gtk_menu_bar_new();
    gtk_box_pack_start(GTK_BOX(vbox), menu_bar, FALSE, FALSE, 2);
    gtk_widget_show(menu_bar);
    gtk_menu_shell_append(GTK_MENU_ITEM(menu_bar), root_menu);
    
    button = gtk_button_new_with_label("press me");
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);
    g_signal_connect_swapped(button, "event", G_CALLBACK(button_press), menu);
    gtk_widget_show(button);
    
    /* Showing the window last so everything pops up at once. */
    gtk_widget_show_all(window);
    
    /* And of course, our main function. */
    gtk_main();
    
    return 0;
}
