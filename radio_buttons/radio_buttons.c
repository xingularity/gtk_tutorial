include <stdlib.h>
include <gtk/gtk.h>

static void click_callback(GtkWidget *widget, gpointer data)
{
    g_print("Hello again - %s was clicked.\n",(char *) data);
}

static void click_callback(GtkWidget *widget, gpointer data)
{
    g_print("Hello again - %s was clicked.\n",(char *) data);
}

static void press_callback(GtkWidget *widget, gpointer data)
{
    g_print("Hello again - %s was pressed.\n",(char *) data);
}

static void toggled_callback(GtkWidget *widget, gpointer data){
    g_print("Hello again - %s was toggled. ",(char *) data);
    g_print("%s \n", gtk_toggle_button_get_mode((GtkToggleButton*)widget) ? "TRUE" : "FALSE");
}

static void release_callback(GtkWidget *widget, gpointer data)
{
    g_print("Hello again - %s was released.\n",(char *) data);
}

static void enter_callback(GtkWidget *widget, gpointer data)
{
    g_print("Hello again - %s was entered.\n",(char *) data);
}

static void leave_callback(GtkWidget *widget, gpointer data)
{
    g_print("Hello again - %s was left behind.\n",(char *) data);
}

int main(int argc, char const *argv[] )
{
    GtkWidget *window = NULL;
    GtkWidget *button;
    GtkWidget *box1;
    GtkWidget *box2;
    GtkWidget *seperator;
    GList* group;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(window), "radio buttons");
    g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    box1 = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), box1);
    gtk_widget_show(box1);

    box2 = gtk_vbox_new(FALSE, 10);
    gtk_container_add(GTK_CONTAINER(window), box2);
    gtk_widget_show(box2);

    //button 1
    button = gtk_radio_button_new_with_label(NULL, "button 1");
    gtk_box_pack_start(GTK_BOX(box2), button, TRUE, TRUE, 0);
    gtk_widget_show(button);

    g_signal_connect(button1, "released", G_CALLBACK(release_callback),(gpointer) "button");
    g_signal_connect(button1, "clicked", G_CALLBACK(click_callback),(gpointer) "button");
    g_signal_connect(button1, "toggled", G_CALLBACK(toggled_callback),(gpointer) "button");
    g_signal_connect(button1, "pressed", G_CALLBACK(press_callback),(gpointer) "button");
    g_signal_connect(button1, "enter", G_CALLBACK(enter_callback),(gpointer) "button");
    g_signal_connect(button1, "leave", G_CALLBACK(leave_callback),(gpointer) "button");
    group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(button));
    
    //button 2
    button = gtk_radio_button_new_with_label(group, "button 2");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button), TRUE);
    gtk_box_pack_start(GTK_BOX(box2), button, TRUE, TRUE, 0);
    gtk_widget_show(button);

    // button 3
    button = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(button),
	                                                  "button 3");
    gtk_box_pack_start(GTK_BOX(box2), button, TRUE, TRUE, 0);
    gtk_widget_show(button);

    // Insert button 1 into the upper left quadrant of the table
    box = xpm_label_box("folder.xpm", "Open file");

    gtk_widget_show(box);

    gtk_container_add(GTK_CONTAINER(button), box);
    gtk_container_add(GTK_CONTAINER(window), button);

    gtk_widget_show(window);

    gtk_main();

    return 0;
}
