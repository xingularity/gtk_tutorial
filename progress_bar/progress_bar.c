#include <gtk/gtk.h>

typedef struct _ProgressData{
    GtkWidget *window;
    GtkWidget *pbar;
    int timer;
    gboolean activity_mode;
}ProgressData;

//update progress bar
static gboolean progress_timeout(gpointer data){
    ProgressData *pdata = (ProgressData*)data;
    gdouble new_val;

    if (pdata -> activity_mode)
        gtk_progress_bar_pulse(GTK_PROGRESS_BAR(pdata->pbar));
    else{
        new_val = gtk_progress_bar_get_fraction(GTK_PROGRESS_BAR(pdata->pbar)) + 0.01;
        if(new_val > 1.0)
            new_val = 0.0;
        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pdata->pbar), new_val);
    }
    return TRUE;
}

static void toggle_show_text(GtkWidget *widget, ProgressData *pdata){
    const gchar *text;

    text = gtk_progress_bar_get_text(GTK_PROGRESS_BAR(pdata->pbar));
    if(text && *text){
        gtk_progress_bar_set_text(GTK_PROGRESS_BAR(pdata->pbar), "");
    }
    else{
        gtk_progress_bar_set_text(GTK_PROGRESS_BAR(pdata->pbar), "some text");
    }
}

static void toggle_activity_mode(GtkWidget *widget, ProgressData *pdata){
    pdata -> activity_mode = !pdata -> activity_mode;
    if(pdata -> activity_mode){
        // becomes a running bar
        gtk_progress_bar_set_pulse_step(pdata->pbar, 0.05);
        gtk_progress_bar_pulse(GTK_PROGRESS_BAR(pdata->pbar));
    }
    else
        // shows actual progress fraction
        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pdata->pbar), 0.0);
}

static void toggle_orientation(GtkWidget *widget, ProgressData *pdata){
    switch(gtk_progress_bar_get_orientation(GTK_PROGRESS_BAR(pdata->pbar))){
    case GTK_PROGRESS_LEFT_TO_RIGHT:
        gtk_progress_bar_set_orientation(GTK_PROGRESS_BAR(pdata->pbar), GTK_PROGRESS_RIGHT_TO_LEFT);
        break;
    case GTK_PROGRESS_RIGHT_TO_LEFT:
        gtk_progress_bar_set_orientation(GTK_PROGRESS_BAR(pdata->pbar), GTK_PROGRESS_LEFT_TO_RIGHT);
        break;
    default:
        ;
    }
}

static void destroy_progress(GtkWidget *widget, ProgressData *pdata){
    g_source_remove(pdata->timer);
    pdata->timer = 0;
    pdata->window = NULL;
    g_free(pdata);
    gtk_main_quit();
}

int main(int argc, char const *argv[] )
{
    ProgressData *pdata;
    GtkWidget *align;
    GtkWidget *separator;
    GtkWidget *table;
    GtkWidget *button;
    GtkWidget *check;
    GtkWidget *vbox;

    gtk_init(&argc, &argv);
    pdata = g_malloc(sizeof(ProgressData));
    pdata->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_resizable(GTK_WINDOW(pdata->window), TRUE);
    g_signal_connect(pdata->window, "destroy", G_CALLBACK(destroy_progress),(gpointer) pdata);
    gtk_window_set_title(GTK_WINDOW(pdata->window), "GTK Progress Bar");
    gtk_container_set_border_width(GTK_CONTAINER(pdata->window), 10);

    vbox = gtk_vbox_new(FALSE, 5);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);
    gtk_container_add(GTK_CONTAINER(pdata->window), vbox);
    gtk_widget_show(vbox);

    //https://developer.gnome.org/gtk3/stable/GtkAlignment.html#gtk-alignment-new
    align = gtk_alignment_new(0.5, 0.5, 0, 0);
    gtk_box_pack_start(GTK_BOX(vbox), align, FALSE, FALSE, 5);
    gtk_widget_show(align);

    pdata->pbar = gtk_progress_bar_new();
    pdata->activity_mode = FALSE;

    gtk_container_add(GTK_CONTAINER(align), pdata->pbar);
    gtk_widget_show(pdata->pbar);

    //https://developer.gnome.org/glib/stable/glib-The-Main-Event-Loop.html#g-timeout-add
    pdata->timer = g_timeout_add(100, progress_timeout, pdata);
    separator = gtk_hseparator_new();
    gtk_box_pack_start(GTK_BOX(vbox), separator, FALSE, FALSE, 0);
    gtk_widget_show(separator);

    table = gtk_table_new(2, 3, FALSE);
    gtk_box_pack_start(GTK_BOX(vbox), table, FALSE, TRUE, 0);
    gtk_widget_show(table);

    // add a button for showing text
    check = gtk_check_button_new_with_label("Show text");
    gtk_table_attach(GTK_TABLE(table), check, 0, 1, 0, 1,
                     GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 5, 5);
    g_signal_connect(check, "clicked", G_CALLBACK(toggle_show_text), pdata);
    gtk_widget_show(check);

    // add a button to choose activity mode
    check = gtk_check_button_new_with_label("Activity mode");
    gtk_table_attach(GTK_TABLE(table), check, 0, 1, 1, 2,
                     GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 5, 5);
    g_signal_connect(check, "clicked", G_CALLBACK(toggle_activity_mode), pdata);
    gtk_widget_show(check);

    // add a button to change orientation
    check = gtk_check_button_new_with_label("Right to Left");
    gtk_table_attach(GTK_TABLE(table), check, 0, 1, 2, 3,
                     GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 5, 5);
    g_signal_connect(check, "clicked", G_CALLBACK(toggle_orientation),pdata);
    gtk_widget_show(check);

    // add a button to quit program
    button = gtk_button_new_with_label ("close");
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), pdata->window);
    gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 0);

    gtk_widget_show(button);
    gtk_widget_show(pdata->window);

    gtk_main();
    return 0;
}
