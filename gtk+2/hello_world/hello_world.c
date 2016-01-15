#include<gtk/gtk.h>

static void hello(GtkWidget *widget, gpointer data){
    g_print("Hello World\n");
}

static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data){
    g_print("delete event \n");
    return TRUE;
}

static void destroy(GtkWidget *widget, gpointer data){
    gtk_main_quit();
}

int main(int argc, char const *argv[]) {
    GtkWidget *window;
    GtkWidget *button;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    g_signal_connect(window, "delete_event", G_CALLBACK(delete_event), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL);

    gtk_container_set_border_width(GTK_CONTAINER (window), 10);

    button = gtk_button_new_with_label ("Hello World!!");

    g_signal_connect(button, "clicked", G_CALLBACK(hello), NULL);

    //Use g_signal_connect_swapped, the expected parameters of the callback function are swapped.
    //The callback function should be like "void func(data, GtkWidget *widget)".
    //The follwing line will act gtk_widget_destroy on window instance.
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), window);

    gtk_container_add(GTK_CONTAINER (window), button);

    gtk_widget_show(button);

    gtk_widget_show (window);

    gtk_main ();

    return 0;
}
