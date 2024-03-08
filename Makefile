all:
	g++ -c src/display/3d/display-game.cpp -o obj/display-game.o -lGL -lGLU -lglut -lSOIL
	g++ -c src/game_features/game.cpp -o obj/game.o
	g++ -c src/game_features/piece.cpp -o obj/piece.o
	g++ -c src/game_features/board.cpp -o obj/board.o
	g++ src/game_features/main.cpp -o exe/main.exe obj/board.o obj/display-game.o obj/game.o obj/piece.o -lGL -lGLU -lglut -lSOIL -lvlc -fopenmp
