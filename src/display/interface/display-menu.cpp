#include "display-menu.hpp"

//sudo apt-get install libgtk-3-dev

//compiler avec: gcc `pkg-config --cflags gtk+-3.0` -o display-menu.exe display-menu.cpp `pkg-config --libs gtk+-3.0`

GtkBuilder *builder;
GObject *window;
GObject *button;
GError *error = NULL;
Parameters params;
Game* onGoingGame = NULL;
GObject* buffer;

static void resume_game(GtkWidget *widget, gpointer data) {
    GError *error = NULL;

    onGoingGame->pausedGame = 0;

    // Close the menu
    GtkWidget *window1 = GTK_WIDGET(data);
    gtk_widget_hide(window1);
}

static void new_game(GtkWidget *widget, gpointer data) {

    // We need to check if there is already a game running to avoid starting again the display thread
    int firstGame = onGoingGame == NULL ? 1 : 0;

    // Create a new game
    onGoingGame = new Game(params);;
    
    thread gameThread(&startGame, onGoingGame);
    gameThread.detach();

    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    char* argv[1];
    if (firstGame) {
    thread displayThread(&main_display, 0, argv);
    displayThread.detach();
    }
    // Close the menu
    GtkWidget *window1 = GTK_WIDGET(data);
    gtk_widget_hide(window1);
    
}

static void quit_menu(GtkWidget *widget, gpointer data) {
    // Close the menu

    onGoingGame->pausedGame = 0;
    onGoingGame->endedGame = 0;
    onGoingGame->pausedGame = 1;
    memoryFree();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    delete onGoingGame;
    // print list of existing widgets
    GtkWidget *window1 = GTK_WIDGET(data);
    gtk_widget_destroy(window1);
}

// Function to show the menu

gboolean show_menu(gpointer data) {
    GtkWidget *window1 = GTK_WIDGET(window);
    gtk_widget_show(window1);
    return G_SOURCE_REMOVE;
}


int main_display_menu() {

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

    buffer = window;

    gtk_main();

    return 0;
}