#include "display-menu.hpp"

// sudo apt-get install libgtk-3-dev

// compiler avec: gcc `pkg-config --cflags gtk+-3.0` -o display-menu.exe display-menu.cpp `pkg-config --libs gtk+-3.0`

GtkBuilder *builder;
GObject *window;
GObject *button;
GError *error = NULL;
Parameters params;
Game *onGoingGame = NULL;
GObject *parametersWindow;

static void resume_game(GtkWidget *widget, gpointer data)
{
    GError *error = NULL;

    onGoingGame->pausedGame = 0;

    // Close the menu
    GtkWidget *window1 = GTK_WIDGET(data);
    gtk_widget_hide(window1);
}

static void new_game(GtkWidget *widget, gpointer data)
{
    // We need to check if there is already a game running to avoid starting again the display thread
    int firstGame = onGoingGame == NULL ? 1 : 0;

    // Create a new game
    onGoingGame = new Game(params);

    thread gameThread(&startGame, onGoingGame);
    gameThread.detach();

    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    char *argv[1];
    if (firstGame)
    {
        button = gtk_builder_get_object(builder, "resume-game");
        g_signal_connect(button, "clicked", G_CALLBACK(resume_game), window);
        thread displayThread(&main_display, 0, argv);
        displayThread.detach();
    }
    // Close the menu
    GtkWidget *window1 = GTK_WIDGET(data);
    gtk_widget_hide(window1);
}

static void quit_menu(GtkWidget *widget, gpointer data)
{
    // Close the menu

    if (onGoingGame != NULL)
    {
        onGoingGame->endedGame = 0;
        onGoingGame->pausedGame = 0;
        onGoingGame->pausedGame = 1;
        memoryFree();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        delete onGoingGame;
    }
    GtkWidget *window1 = GTK_WIDGET(data);
    gtk_widget_destroy(window1);
}

void changeVolume(GtkWidget *widget, gpointer data)
{
    // Get the new value of the volume
    GtkScale *volumeScale = GTK_SCALE(widget);
    int volume = gtk_range_get_value(GTK_RANGE(volumeScale));
    gtk_range_set_value(GTK_RANGE(volumeScale), volume);
    // Update the volume
    params.volume = volume;

    if (onGoingGame != NULL)
    {
        onGoingGame->params.volume = volume;
    }
}

void changeDifficulty(GtkWidget *widget, gpointer data)
{
    // Get the new value of the difficulty
    GtkScale *difficultyScale = GTK_SCALE(widget);
    int difficulty = gtk_range_get_value(GTK_RANGE(difficultyScale));
    gtk_range_set_value(GTK_RANGE(difficultyScale), difficulty);
    // Update the difficulty
    params.difficulty = difficulty;

    if (onGoingGame != NULL)
    {
        onGoingGame->params.difficulty = difficulty;
    }
}

static void parameters_menu(GtkWidget *widget, gpointer data)
{
    // Close the menu
    GtkWidget *window1 = GTK_WIDGET(data);
    gtk_widget_hide(window1);

    parametersWindow = gtk_builder_get_object(builder, "parameters-window");
    g_signal_connect(parametersWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Connect the signals
    // volume slider
    GtkScale *volumeScale = GTK_SCALE(gtk_builder_get_object(builder, "volume"));
    gtk_range_set_range(GTK_RANGE(volumeScale), 0, 100);
    gtk_widget_set_sensitive(GTK_WIDGET(volumeScale), TRUE);

    // Set the initial volume value
    gtk_range_set_value(GTK_RANGE(volumeScale), params.volume);

    // Connect the "value-changed" signal to a callback function
    g_signal_connect(volumeScale, "value-changed", G_CALLBACK(changeVolume), NULL);

    // Difficulty slider

    GtkScale *difficultyScale = GTK_SCALE(gtk_builder_get_object(builder, "difficulty"));
    gtk_range_set_range(GTK_RANGE(difficultyScale), 1, 10);
    gtk_widget_set_sensitive(GTK_WIDGET(difficultyScale), TRUE);

    // Set the initial difficulty value
    gtk_range_set_value(GTK_RANGE(difficultyScale), params.difficulty);

    // Connect the "value-changed" signal to a callback function
    g_signal_connect(difficultyScale, "value-changed", G_CALLBACK(changeDifficulty), NULL);

    button = gtk_builder_get_object(builder, "return");
    // show menu and hide parameters window
    g_signal_connect(button, "clicked", G_CALLBACK(show_menu), parametersWindow);

    gtk_widget_show(GTK_WIDGET(parametersWindow));
}

// Function to show the menu

gboolean show_menu(gpointer data)
{
    if (GTK_IS_WIDGET(parametersWindow))
        gtk_widget_hide(GTK_WIDGET(parametersWindow));
    GtkWidget *window1 = GTK_WIDGET(window);
    gtk_widget_show(window1);
    return G_SOURCE_REMOVE;
}

int main_display_menu()
{

    gtk_init(0, NULL);

    /* Construct a GtkBuilder instance and load our UI description */
    builder = gtk_builder_new();
    if (gtk_builder_add_from_file(builder, "./src/display/interface/builder.ui", &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }

    /* Connect signal handlers to the constructed widgets. */
    window = gtk_builder_get_object(builder, "window");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    button = gtk_builder_get_object(builder, "new-game");
    g_signal_connect(button, "clicked", G_CALLBACK(new_game), window);

    button = gtk_builder_get_object(builder, "quit");
    g_signal_connect(button, "clicked", G_CALLBACK(quit_menu), window);

    button = gtk_builder_get_object(builder, "parameters");
    g_signal_connect(button, "clicked", G_CALLBACK(parameters_menu), window);

    gtk_main();

    return 0;
}