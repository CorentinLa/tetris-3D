#include "display-menu.hpp"

//sudo apt-get install libgtk-3-dev

//compiler avec: gcc `pkg-config --cflags gtk+-3.0` -o display-menu.exe display-menu.cpp `pkg-config --libs gtk+-3.0`

static void resume_game(GtkWidget *widget, gpointer data) {
    // const char *command = "./exe/main.exe";
    // GError *error = NULL;

    // // Execute the command asynchronously
    // if (!g_spawn_command_line_async(command, &error)) {
    //     g_printerr("Error launching command: %s\n", error->message);
    //     g_clear_error(&error);
    // }

    RUN_GAME = 1;
    NEW_GAME = 0;
    DISPLAY_GAME = 1;
    CLOSE_GAME = 0;

    // Close the menu
    GtkWidget *window = GTK_WIDGET(data);
    gtk_widget_destroy(window);

}

static void new_game(GtkWidget *widget, gpointer data) {

    RUN_GAME = 1;
    NEW_GAME = 1;
    DISPLAY_GAME = 1;
    CLOSE_GAME = 0;

    // Close the menu
    GtkWidget *window = GTK_WIDGET(data);
    gtk_widget_destroy(window);

}

static void quit_menu(GtkWidget *widget, gpointer data) {
    // Close the menu

    CLOSE_GAME = 1;

    GtkWidget *window = GTK_WIDGET(data);
    gtk_widget_destroy(window);
}

int main_display_menu() {
    GtkBuilder *builder;
    GObject *window;
    GObject *button;
    GError *error = NULL;

    gtk_init(0, NULL);

    /* Construct a GtkBuilder instance and load our UI description */
    builder = gtk_builder_new();
    if (gtk_builder_add_from_file(builder, "./src/display/interface/builder.ui", &error) == 0) {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }

    /* Connect signal handlers to the constructed widgets. */
    window = gtk_builder_get_object(builder, "window");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    button = gtk_builder_get_object(builder, "resume-game");
    g_signal_connect(button, "clicked", G_CALLBACK(resume_game), window);

    button = gtk_builder_get_object(builder, "new-game");
    g_signal_connect(button, "clicked", G_CALLBACK(new_game), window);

    button = gtk_builder_get_object(builder, "quit");
    g_signal_connect(button, "clicked", G_CALLBACK(quit_menu), window);

    gtk_main();

    return 0;
}