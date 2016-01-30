#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<gtk/gtk.h>

int main(int argc, char const *argv[]) {
    GtkWidget *window;
    GtkWidget *aspect_frame;
    GtkWidget *drawing_area;
    gint i;
    
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Aspect Frame");

    g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    aspect_frame = gtk_aspect_frame_new("2x1", 0.5, 0.5, 2, FALSE);
    gtk_container_add(GTK_CONTAINER(window), aspect_frame);
    gtk_widget_show(aspect_frame);
    
    drawing_area = gtk_drawing_area_new();
    
    gtk_widget_set_size_request(drawing_area, 200, 200);
    
    gtk_container_add(GTK_CONTAINER(aspect_frame), drawing_area);
    
    gtk_widget_show(drawing_area);
    
    /* Showing the window last so everything pops up at once. */
    gtk_widget_show(window);
    
    /* And of course, our main function. */
    gtk_main();
    
    return 0;
}
