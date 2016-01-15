#include<gtk/gtk.h>

static void callback(GtkWidget *widget, gpointer data){
    g_print("Hello again - %s was pressed\n", (gchar *) data);
}

static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data){
    gtk_main_quit();
    return FALSE;
}

int main(int argc, char const *argv[]) {
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *box1;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(window), "Hello with 2Buttons!");

    g_signal_connect(window, "delete_event", G_CALLBACK(delete_event), NULL);

    gtk_container_set_border_width(GTK_CONTAINER (window), 10);

    button = gtk_button_new_with_label("Button 1");

    g_signal_connect(button, "clicked", G_CALLBACK(callback), (gpointer) "Button 1");

    // https://developer.gnome.org/gtk2/stable/GtkHBox.html
    box1 = gtk_hbox_new(FALSE, 20);

    gtk_container_add(GTK_CONTAINER (window), box1);

    // Start packing widgets
    // https://developer.gnome.org/gtk2/stable/GtkBox.html#gtk-box-pack-start
    gtk_box_pack_start(GTK_BOX(box1), button, TRUE, TRUE, 10);

    gtk_widget_show(button);

    button = gtk_button_new_with_label("Button 2");

    g_signal_connect(button, "clicked", G_CALLBACK(callback), (gpointer) "Button 2");

    gtk_box_pack_start(GTK_BOX(box1), button, TRUE, TRUE, 10);

    gtk_widget_show(button);

    gtk_widget_show(box1);

    gtk_widget_show (window);

    gtk_main ();

    return 0;
}
