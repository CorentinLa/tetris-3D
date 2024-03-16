all:
	g++ -c src/display/3d/display-game.cpp -o obj/display-game.o -lGL -lGLU -lglut -lSOIL `pkg-config --libs gtk+-3.0` `pkg-config --cflags gtk+-3.0`
	g++ -c src/game_features/board.cpp -o obj/board.o
	g++ -c src/game_features/game.cpp -o obj/game.o
	g++ -c src/game_features/piece.cpp -o obj/piece.o
	g++ -c src/display/interface/display-menu.cpp -o obj/display-menu.o `pkg-config --libs gtk+-3.0` `pkg-config --cflags gtk+-3.0`
	g++ src/game_features/main.cpp -g -o exe/main.exe obj/display-menu.o obj/board.o obj/display-game.o obj/game.o obj/piece.o -lGL -lGLU -lglut -lSOIL -lvlc -fopenmp `pkg-config --libs gtk+-3.0` `pkg-config --cflags gtk+-3.0`
