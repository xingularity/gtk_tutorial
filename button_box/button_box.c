#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<gtk/gtk.h>

GtkWidget* create_bbox(gint horizontal, gchar* title, gint spacing, gint child_w, gint child_h, gint layout){

    GtkWidget *frame;
    GtkWidget *bbox;
    GtkWidget *button;
    
    frame = gtk_frame_new(title);
    if(horizontal)
        bbox = gtk_hbutton_box_new();
    else
        bbox = gtk_vbutton_box_new();
    
    gtk_container_set_border_width(GTK_CONTAINER(bbox), 5);
    gtk_container_add(GTK_CONTAINER(frame), bbox);
    
    gtk_button_box_set_layout(GTK_BUTTON_BOX(bbox), layout);
    gtk_box_set_spacing(GTK_BUTTON_BOX(bbox), spacing);
    
    button = gtk_button_new_from_stock(GTK_STOCK_OK);
    gtk_container_add(GTK_CONTAINER(bbox), button);
    
    button = gtk_button_new_from_stock(GTK_STOCK_CANCEL);
    gtk_container_add(GTK_CONTAINER(bbox), button);

    button = gtk_button_new_from_stock(GTK_STOCK_HELP);
    gtk_container_add(GTK_CONTAINER(bbox), button);
    
    return frame;
    
}

int main(int argc, char const *argv[]) {
    GtkWidget *window;
    GtkWidget *main_vbox;
    GtkWidget *vbox;
    GtkWidget *hbox;
    GtkWidget *frame_horz;
    GtkWidget *frame_vert;
    
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Button Boxes");

    g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    
    main_vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), main_vbox);
    
    frame_horz = gtk_frame_new("Horizon frame boxes");
    gtk_container_add(GTK_CONTAINER(main_vbox), frame_horz);
    
    vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);
    gtk_container_add(GTK_CONTAINER(frame_horz), vbox);
    
    /* Note:
     * GtkWidget* create_box(gint horizontal, gchar* title, gint spacing, gint child_w, gint child_h, gint layoout)
     */
    
    gtk_box_pack_start(GTK_BOX(vbox), create_bbox(TRUE, "Spread(spacing 40)", 40, 85, 20, GTK_BUTTONBOX_SPREAD),
        TRUE, TRUE, 0);
    
    gtk_box_pack_start(GTK_BOX(vbox), create_bbox(TRUE, "Edge(spacing 30)", 30, 85, 20, GTK_BUTTONBOX_EDGE),
        TRUE, TRUE, 5);
    
    gtk_box_pack_start(GTK_BOX(vbox), create_bbox(TRUE, "Start(spacing 20)", 20, 85, 20, GTK_BUTTONBOX_START),
        TRUE, TRUE, 5);

    gtk_box_pack_start(GTK_BOX(vbox), create_bbox(TRUE, "End(spacing 10)", 10, 85, 20, GTK_BUTTONBOX_END),
        TRUE, TRUE, 5);
    
    frame_vert = gtk_frame_new("Vertical frame boxes");
    gtk_container_add(GTK_CONTAINER(main_vbox), frame_vert);
    
    hbox = gtk_hbox_new(FALSE, 0);
    gtk_container_set_border_width(GTK_CONTAINER(hbox), 10);
    gtk_container_add(GTK_CONTAINER(frame_vert), hbox);
    
    gtk_box_pack_start(GTK_BOX(hbox), create_bbox(FALSE, "Spread(spacing 5)", 5, 85, 20, GTK_BUTTONBOX_SPREAD),
        TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(hbox), create_bbox(FALSE, "Edge(spacing 30)", 30, 85, 20, GTK_BUTTONBOX_EDGE),
        TRUE, TRUE, 5);

    gtk_box_pack_start(GTK_BOX(hbox), create_bbox(FALSE, "Start(spacing 20)", 20, 85, 20, GTK_BUTTONBOX_START),
        TRUE, TRUE, 5);

    gtk_box_pack_start(GTK_BOX(hbox), create_bbox(FALSE, "End(spacing 20)", 20, 85, 20, GTK_BUTTONBOX_END),
        TRUE, TRUE, 5);
    
    /* Showing the window last so everything pops up at once. */
    gtk_widget_show_all(window);
    
    /* And of course, our main function. */
    gtk_main();
    
    return 0;
}
