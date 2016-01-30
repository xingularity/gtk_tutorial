#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<gtk/gtk.h>

gint x = 50;
gint y = 50;

static void move_button(GtkWidget* widget, GtkWidget* fixed){
    x = (x + 30) % 300;
    y = (y + 50) % 300;
    gtk_fixed_move(GTK_FIXED(fixed), widget, x, y); 
}

int main(int argc, char const *argv[]) {
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *fixed;
    gint i;
    
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Fixed Container");

    g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_widget_show(fixed);
    
    for(i = 0; i < 3; ++i){
        char * str = malloc(12);
        snprintf(str, 12, "Press me %i", i);
        button = gtk_button_new_with_label(str);
        g_signal_connect(button, "clicked", G_CALLBACK(move_button), (gpointer) fixed);
        gtk_fixed_put(GTK_FIXED(fixed), button, i*50, i*50);
        gtk_widget_show(button);
    }
    /* Showing the window last so everything pops up at once. */
    gtk_widget_show(window);
    
    /* And of course, our main function. */
    gtk_main();
    
    return 0;
}
