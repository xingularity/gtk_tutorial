#include <stdio.h>
#include <gtk/gtk.h>

void print(GtkWidget* widget){
    g_print("click\n");
}

int main(int argc, char const *argv[])
{
  GtkWidget *window;
  GtkWidget *label;
  GtkWidget *event_box;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_window_set_title(GTK_WINDOW(window), "Eventbox");

  event_box = gtk_event_box_new();
  gtk_container_add(GTK_CONTAINER(window), event_box);
  gtk_widget_show(event_box);

  label = gtk_label_new("Clicke here");
  gtk_container_add(GTK_CONTAINER(event_box), label);
  gtk_widget_show(label);

  gtk_widget_set_size_request(label, 110, 20);

  //http://openhome.cc/Gossip/GTKGossip/EventMask.html
  gtk_widget_set_events(event_box, GDK_BUTTON_PRESS_MASK);
  g_signal_connect(event_box, "button_press_event", G_CALLBACK(print), NULL);

  //https://developer.gnome.org/gtk3/stable/GtkWidget.html#gtk-widget-realize
  gtk_widget_realize(event_box);
  //https://developer.gnome.org/gdk3/stable/gdk3-Windows.html#gdk-window-set-cursor
  gdk_window_set_cursor(event_box->window, gdk_cursor_new (GDK_HAND1));

  gtk_widget_show(window);

  /* Enter the event loop */
  gtk_main();

  return 0;
}
