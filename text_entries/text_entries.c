#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

static void enter_callback(GtkWidget *widget, GtkWidget *entry){
    const gchar *entry_text;
    entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
    printf("Entry content: %s\n", entry_text);
}

static void editable_toggled(GtkWidget *button, GtkWidget *entry){
    gtk_editable_set_editable(GTK_EDITABLE(entry), GTK_TOGGLE_BUTTON(button)->active);
}

static void visibility_toggled(GtkWidget *button, GtkWidget *entry){
    gtk_entry_set_visibility(GTK_ENTRY(entry), GTK_TOGGLE_BUTTON(button)->active);
}

int main(int argc, char const *argv[] )
{
    GtkWidget *window;
    GtkWidget *hbox;
    GtkWidget *vbox;
    GtkWidget *entry;
    GtkWidget *button;
    GtkWidget *check;
    gint tmp_pos;

    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
    g_signal_connect(window, "destroy", gtk_main_quit, NULL);
    g_signal_connect_swapped(window, "destroy", gtk_widget_destroy, window);
    gtk_window_set_title(GTK_WINDOW(window), "Entry");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    vbox = gtk_vbox_new(FALSE, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show(vbox);

    entry = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(entry), 100);
    g_signal_connect(entry, "activate", enter_callback, entry);
    gtk_entry_set_text(GTK_ENTRY(entry), "hello");
    tmp_pos = GTK_ENTRY(entry) -> text_length;
    //https://developer.gnome.org/gtk3/stable/GtkEditable.html#gtk-editable-insert-text
    gtk_editable_insert_text(GTK_EDITABLE(entry), " world", -1, &tmp_pos);
    gtk_editable_select_region(GTK_EDITABLE(entry), 0, GTK_ENTRY(entry)->text_length);
    gtk_box_pack_start(GTK_CONTAINER(vbox), entry, TRUE, TRUE, 0);
    gtk_widget_show(entry);

    hbox = gtk_hbox_new(FALSE, 5);
    gtk_container_add(GTK_CONTAINER(vbox), hbox);
    gtk_widget_show(hbox);

    check = gtk_check_button_new_with_label("Editable");
    gtk_box_pack_start(GTK_BOX(hbox), check, TRUE, TRUE, 0);
    g_signal_connect(check, "toggled", G_CALLBACK(editable_toggled), entry);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check), TRUE);
    gtk_widget_show(check);
    
    check = gtk_check_button_new_with_label("Visible");
    gtk_box_pack_start(GTK_BOX(hbox), check, TRUE, TRUE, 0);
    g_signal_connect(check, "toggled", G_CALLBACK(visibility_toggled), entry);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check), TRUE);
    gtk_widget_show(check);

    //https://developer.gnome.org/gtk3/stable/GtkButton.html#gtk-button-new-from-stock
    //https://developer.gnome.org/gtk3/stable/gtk3-Stock-Items.html
    button = gtk_button_new_from_stock(GTK_STOCK_CLOSE);
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), window);
    gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);
    gtk_widget_set_can_default(button, TRUE);
    gtk_widget_grab_default(button);

    gtk_widget_show(button);
    gtk_widget_show(window);

    gtk_main();
    return 0;
}
