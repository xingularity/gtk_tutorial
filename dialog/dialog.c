#include <assert.h>
#include <gtk/gtk.h>

void print_usage(){
    printf("You have to input a integer parameter.\n");
    printf("Entering 0 to produce a dialog using non-default constructor.\n");
    printf("Entering 1 to produce a dialog with a background window.\n");
    printf("Entering 2 to produce a error message dialog with a background window.\n");
}

static void click_callback(GtkWidget *widget, gpointer data)
{
    g_print("Main window button pressed.\n");
}

void create_error_message_dialog_with_window(){
    GtkWindow *window;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(window), "Background window");
    g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);

    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_show(window);
    
    GtkButton *button;
    button = gtk_button_new_with_label("button to demostrate dialog modal property.");
    g_signal_connect(button, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    gtk_container_add(GTK_CONTAINER(window), button);
    gtk_widget_show(button);

    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
    GtkDialog *dialog;
    dialog = gtk_message_dialog_new(window, flags, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE,
                                    "Error reading “%s”: %s", "some file", g_strerror(0));
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    g_signal_connect_swapped (dialog, "response", G_CALLBACK(gtk_widget_destroy), dialog);
}

void create_dialog_with_window_parent(){
    GtkWindow *window;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(window), "Background window");
    g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);

    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_show(window);
    /*
    GtkLabel *mainwin_label;
    mainwin_label = gtk_label_new("This is background window to demostrate dialog modal property.");
    gtk_container_add(GTK_CONTAINER(window), mainwin_label);
    gtk_widget_show(mainwin_label);
    */
    GtkButton *button;
    button = gtk_button_new_with_label("button to demostrate dialog modal property.");
    gtk_container_add(GTK_CONTAINER(window), button);
    gtk_widget_show(button);

    GtkDialog *dialog;

    GtkDialogFlags flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;
    //https://developer.gnome.org/gtk3/stable/GtkDialog.html#gtk-dialog-new
    //dialog = gtk_dialog_new_with_buttons("Dialog Yes/No", window, "OK",
    //                                     GTK_RESPONSE_ACCEPT, "Cancel", GTK_RESPONSE_REJECT, NULL);
    dialog = gtk_dialog_new_with_buttons("Dialog Yes/No", window, flags, NULL);
    g_signal_connect(dialog, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    GtkBox *vbox;
    vbox = gtk_vbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->action_area), vbox, FALSE, FALSE, 0);
    gtk_widget_show(vbox);

    GtkBox *hbox;
    hbox = gtk_hbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    GtkLabel *label;
    label = gtk_label_new("Warning ok?");
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    gtk_widget_show(label);

    // add buttons
    hbox = gtk_hbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
    gtk_widget_show(hbox);

    button = gtk_button_new_with_label("OK");
    g_signal_connect(button, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    gtk_widget_show(button);

    button = gtk_button_new_with_label("Cancel");
    g_signal_connect(button, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    gtk_widget_show(button);

    gtk_widget_show(dialog);

}

void create_dialog_with_non_default_constructor(){
    GtkDialog *dialog;

    GtkDialogFlags flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;
    //https://developer.gnome.org/gtk3/stable/GtkDialog.html#gtk-dialog-new
    //dialog = gtk_dialog_new_with_buttons("Dialog Yes/No", window, "OK",
    //                                     GTK_RESPONSE_ACCEPT, "Cancel", GTK_RESPONSE_REJECT, NULL);
    dialog = gtk_dialog_new_with_buttons("Dialog Yes/No", NULL, flags, NULL);
    g_signal_connect(dialog, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    GtkBox *vbox;
    vbox = gtk_vbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->action_area), vbox, FALSE, FALSE, 0);
    gtk_widget_show(vbox);

    GtkBox *hbox;
    hbox = gtk_hbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
    gtk_widget_show(hbox);
    GtkLabel *label;
    label = gtk_label_new("Warning ok?");
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    gtk_widget_show(label);

    // add buttons
    hbox = gtk_hbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
    gtk_widget_show(hbox);

    GtkButton *button;
    button = gtk_button_new_with_label("OK");
    g_signal_connect(button, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    gtk_widget_show(button);

    button = gtk_button_new_with_label("Cancel");
    g_signal_connect(button, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    gtk_widget_show(button);

    gtk_widget_show(dialog);
}

int main(int argc, char const *argv[] )
{
    if(argc != 2){
        print_usage();
        return 0;
    }

    gtk_init(&argc, &argv);
    if(atoi(argv[1]) == 0)
        create_dialog_with_non_default_constructor();
    else if(atoi(argv[1]) == 1)
        create_dialog_with_window_parent();
    else if(atoi(argv[1]) == 2)
        create_error_message_dialog_with_window();
    else{
        print_usage();
        return 0;
    }
    gtk_main();
    return 0;
}
