#include <stdlib.h>
#include <gtk/gtk.h>

static gboolean find_which_button_in_group_activated(GtkWidget *widget){
    GSList * tmp_list = gtk_radio_button_get_group ((GtkRadioButton*) widget);
    GtkRadioButton* tmp_button = NULL;
    while(tmp_list){
        tmp_button = tmp_list -> data;
        if (gtk_toggle_button_get_active(tmp_button))
            g_print("%s is activated.\n", gtk_button_get_label(tmp_button));
        tmp_list = tmp_list -> next;
    }
    return TRUE;
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
    gtk_box_pack_start(GTK_BOX(box1), box2, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(window), box2);
    gtk_widget_show(box2);

    //button 1
    button = gtk_radio_button_new_with_label(NULL, "button 1");
    gtk_box_pack_start(GTK_BOX(box2), button, TRUE, TRUE, 0);
    gtk_widget_show(button);

    //g_signal_connect(button, "released", G_CALLBACK(release_callback),(gpointer) "button");
    //g_signal_connect(button, "clicked", G_CALLBACK(click_callback),(gpointer) "button");
    g_signal_connect(button, "released", G_CALLBACK(find_which_button_in_group_activated), NULL);
    //g_signal_connect(button, "pressed", G_CALLBACK(press_callback),(gpointer) "button");
    //g_signal_connect(button, "enter", G_CALLBACK(enter_callback),(gpointer) "button");
    //g_signal_connect(button, "leave", G_CALLBACK(leave_callback),(gpointer) "button");
    group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(button));

    //button 2
    button = gtk_radio_button_new_with_label(group, "button 2");
    g_signal_connect(button, "released", G_CALLBACK(find_which_button_in_group_activated), NULL);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button), TRUE);
    gtk_box_pack_start(GTK_BOX(box2), button, TRUE, TRUE, 0);
    gtk_widget_show(button);

    // button 3
    // gtk_radio_button_new_with_label(gtk_radio_button_get_group (GTK_RADIO_BUTTON (button)), "button 3");
    button = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(button), "button 3");
    g_signal_connect(button, "released", G_CALLBACK(find_which_button_in_group_activated), NULL);
    gtk_box_pack_start(GTK_BOX(box2), button, TRUE, TRUE, 0);
    gtk_widget_show(button);

    seperator = gtk_hseparator_new();
    gtk_box_pack_start(GTK_BOX(box1), button, FALSE, TRUE, 0);
    gtk_widget_show(seperator);

    box2 = gtk_vbox_new(FALSE, 10);
    gtk_container_set_border_width(GTK_CONTAINER(box2), 10);
    gtk_box_pack_start(GTK_BOX(box1), box2, TRUE, TRUE, 0);
    gtk_widget_show(box2);

    button = gtk_button_new_with_label("close");
    g_signal_connect(button, "clicked", gtk_main_quit, NULL);
    gtk_box_pack_start(GTK_BOX(box2), button, TRUE, TRUE, 0);
    gtk_widget_set_can_default(button, TRUE);
    gtk_widget_grab_default(button);
    gtk_widget_show(button);

    gtk_widget_show(window);

    gtk_main();

    return 0;
}
