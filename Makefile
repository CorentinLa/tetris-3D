CC=g++
CFLAGS=`pkg-config --cflags gtk+-3.0` 
LIBS=`pkg-config --libs gtk+-3.0` -lGL -lGLU -lglut -lSOIL -lvlc -fopenmp

all: main
	
main: obj/display-game.o obj/board.o obj/game.o obj/piece.o obj/display-menu.o src/game_features/main.cpp
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

obj/display-game.o: src/display/3d/display-game.cpp
	$(CC) -o $@ -c $< $(CFLAGS) $(LIBS)

obj/board.o: src/game_features/board.cpp
	$(CC) -o $@ -c $< $(CFLAGS) $(LIBS)

obj/game.o: src/game_features/game.cpp
	$(CC) -o $@ -c $< $(CFLAGS) $(LIBS)

obj/piece.o: src/game_features/piece.cpp
	$(CC) -o $@ -c $< $(CFLAGS) $(LIBS)

obj/display-menu.o: src/display/interface/display-menu.cpp
	$(CC) -o $@ -c $< $(CFLAGS) $(LIBS)

clean:
	rm -f obj/*.o exe/main.exe