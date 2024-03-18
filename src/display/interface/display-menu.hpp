#ifndef DISPLAY_MENU_HPP
#define DISPLAY_MENU_HPP

#include <gtk/gtk.h>
#include "../../game_features/main.hpp"

int main_display_menu();

static void resume_game(GtkWidget *widget, gpointer data);

static void new_game(GtkWidget *widget, gpointer data);

void show_menu();

void hide_menu();

#endif