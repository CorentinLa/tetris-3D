#ifndef DISPLAY_MENU_HPP
#define DISPLAY_MENU_HPP

#include <gtk/gtk.h>
#include <thread>
#include "../../game_features/main.hpp"
#include "../../game_features/game.hpp"

int main_display_menu();

static void resume_game(GtkWidget *widget, gpointer data);

static void new_game(GtkWidget *widget, gpointer data);

gboolean show_menu(gpointer data);

#endif