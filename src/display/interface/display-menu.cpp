#include <gtk/gtk.h>

//sudo apt-get install libgtk-3-dev

//compiler avec: gcc `pkg-config --cflags gtk+-3.0` -o display-menu.exe display-menu.cpp `pkg-config --libs gtk+-3.0`

static void execute_tetris3d(GtkWidget *widget, gpointer data) {
    const char *command = "../3d/tetris3d.exe";
    GError *error = NULL;

    // Execute the command asynchronously
    if (!g_spawn_command_line_async(command, &error)) {
        g_printerr("Error launching command: %s\n", error->message);
        g_clear_error(&error);
    }

    gtk_main_quit();
}

int main(int argc, char *argv[]) {
    GtkBuilder *builder;
    GObject *window;
    GObject *button;
    GError *error = NULL;

    gtk_init(&argc, &argv);

    /* Construct a GtkBuilder instance and load our UI description */
    builder = gtk_builder_new();
    if (gtk_builder_add_from_file(builder, "builder.ui", &error) == 0) {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }

    /* Connect signal handlers to the constructed widgets. */
    window = gtk_builder_get_object(builder, "window");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    button = gtk_builder_get_object(builder, "button1");
    g_signal_connect(button, "clicked", G_CALLBACK(execute_tetris3d), NULL);

    button = gtk_builder_get_object(builder, "quit");
    g_signal_connect(button, "clicked", G_CALLBACK(gtk_main_quit), NULL);

    gtk_main();

    return 0;
}
