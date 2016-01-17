#include <stdlib.h>
#include <gtk/gtk.h>

static GtkWidget *xpm_label_box(gchar *filename, gchar *label_text){
    GtkWidget *box;
    GtkWidget *label;
    GtkWidget *image;
    box = gtk_hbox_new(FALSE, 0);
    gtk_container_set_border_width(GTK_CONTAINER(box), 2);

    image = gtk_image_new_from_file(filename);
    label = gtk_label_new(label_text);

    gtk_box_pack_start(GTK_BOX(box), image, FALSE, FALSE, 3);
    gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 3);

    gtk_widget_show(label);
    gtk_widget_show(image);

    return box;
}

static void click_callback(GtkWidget *widget, gpointer data)
{
    g_print("Hello again - %s was clicked.\n", (char *) data);
}

static void press_callback(GtkWidget *widget, gpointer data)
{
    g_print("Hello again - %s was pressed.\n", (char *) data);
}

static void toggled_callback(GtkWidget *widget, gpointer data){
    g_print("Hello again - %s was toggled. ", (char *) data);
    g_print("%s \n", gtk_toggle_button_get_mode((GtkToggleButton*)widget) ? "TRUE" : "FALSE");
}

static void release_callback(GtkWidget *widget, gpointer data)
{
    g_print("Hello again - %s was released.\n", (char *) data);
}

static void enter_callback(GtkWidget *widget, gpointer data)
{
    g_print("Hello again - %s was entered.\n", (char *) data);
}

static void leave_callback(GtkWidget *widget, gpointer data)
{
    g_print("Hello again - %s was left behind.\n", (char *) data);
}

int main(int argc, char const *argv[] )
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *box;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(window), "Button with image");
    g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);

    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    // Use gtk_button_new create a button without parameters.
    button = gtk_toggle_button_new();

    gtk_widget_show(button);

    g_signal_connect(button, "released", G_CALLBACK(release_callback), (gpointer) "button");
    g_signal_connect(button, "clicked", G_CALLBACK(click_callback), (gpointer) "button");
    g_signal_connect(button, "toggled", G_CALLBACK(toggled_callback), (gpointer) "button");
    g_signal_connect(button, "pressed", G_CALLBACK(press_callback), (gpointer) "button");
    g_signal_connect(button, "enter", G_CALLBACK(enter_callback), (gpointer) "button");
    g_signal_connect(button, "leave", G_CALLBACK(leave_callback), (gpointer) "button");

    // Insert button 1 into the upper left quadrant of the table
    box = xpm_label_box("folder.xpm", "Open file");

    gtk_widget_show(box);

    gtk_container_add(GTK_CONTAINER(button), box);
    gtk_container_add(GTK_CONTAINER(window), button);

    gtk_widget_show(window);

    gtk_main();

    return 0;
}
