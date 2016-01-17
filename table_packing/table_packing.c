#include <gtk/gtk.h>

static void callback(GtkWidget *widget, gpointer data)
{
    g_print("Hello again - %s was pressed\n", (char *) data);
}

static gboolean delete_event(GtkWidget *widget, GdkEvent  *event, gpointer data)
{
    gtk_main_quit();
    return FALSE;
}

int main(int argc, char const *argv[] )
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *table;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(window), "Table");
    g_signal_connect(window, "delete-event", G_CALLBACK(delete_event), NULL);

    gtk_container_set_border_width(GTK_CONTAINER(window), 20);

    // create a table with 3x3
    table = gtk_table_new(3, 3, TRUE);
    gtk_container_add(GTK_CONTAINER(window), table);

    button = gtk_button_new_with_label("button 1");

    g_signal_connect(button, "clicked", G_CALLBACK(callback), (gpointer) "button 1");

    // Insert button 1 into the upper left quadrant of the table
    gtk_table_attach_defaults(GTK_TABLE(table), button, 0, 1, 0, 1);

    gtk_widget_show(button);

    button = gtk_button_new_with_label("button 2");

    g_signal_connect(button, "clicked", G_CALLBACK(callback), (gpointer) "button 2");
    // Insert button 1 into the upper right quadrant of the table
    gtk_table_attach_defaults(GTK_TABLE(table), button, 1, 3, 0, 1);

    gtk_widget_show(button);

    button = gtk_button_new_with_label("Quit");

    g_signal_connect(button, "clicked", G_CALLBACK(delete_event), NULL);

    gtk_table_attach_defaults(GTK_TABLE(table), button, 1, 3, 1, 3);

    gtk_widget_show(button);

    /* The above code intensionally let left lower quandrant empty. */

    gtk_widget_show(table);
    gtk_widget_show(window);

    gtk_main();

    return 0;
}
