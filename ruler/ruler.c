#include <gtk/gtk.h>

#define EVENT_METHOD(i, x) GTK_WIDGET_GET_CLASS(i)->x

#define XSIZE  600
#define YSIZE  400

int main(int argc, char const *argv[] )
{
    GtkWidget *window;
    GtkWidget *area;
    GtkWidget *table;
    GtkWidget *hrule;
    GtkWidget *vrule;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(window), "Ruler example");
    g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);

    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_show(window);

    table = gtk_table_new(3, 2, FALSE);
    gtk_container_add(GTK_CONTAINER(window), table);
    //create a drawing area
    area = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(area), XSIZE, YSIZE);
    gtk_table_attach(GTK_TABLE(table), area, 1, 2, 1, 2, GTK_EXPAND|GTK_FILL, GTK_FILL, 0, 0);
    gtk_widget_set_events(area, GDK_POINTER_MOTION_MASK | GDK_POINTER_MOTION_HINT_MASK);

    /* hruler is on top of the drawing area. Drawing area will emit "motion_notify_event".
     The event is passed to appropriate event handler for the ruler.
    */
    hrule = gtk_hruler_new();
    gtk_ruler_set_metric(GTK_RULER(hrule), GTK_PIXELS);
    gtk_ruler_set_range(GTK_RULER(hrule), 7, 13, 0, 20);
    g_signal_connect_swapped(area, "motion_notify_event",
                             G_CALLBACK(EVENT_METHOD(hrule, motion_notify_event)), hrule);
    gtk_table_attach(GTK_TABLE(table), hrule, 1, 2, 0, 1,
                     GTK_EXPAND|GTK_SHRINK|GTK_FILL, GTK_FILL, 0, 0);
    vrule = gtk_vruler_new();
    gtk_ruler_set_metric(GTK_RULER(vrule), GTK_PIXELS);
    gtk_ruler_set_range(GTK_RULER(vrule), 0, YSIZE, 10, YSIZE );
    g_signal_connect_swapped(area, "motion_notify_event",
                             G_CALLBACK(EVENT_METHOD(vrule, motion_notify_event)), vrule);
    gtk_table_attach(GTK_TABLE(table), vrule, 0, 1, 1, 2,
                     GTK_FILL, GTK_EXPAND|GTK_SHRINK|GTK_FILL, 0, 0);

    gtk_widget_show (area);
    gtk_widget_show (hrule);
    gtk_widget_show (vrule);
    gtk_widget_show (table);
    gtk_widget_show (window);

    gtk_main();
    return 0;
}
