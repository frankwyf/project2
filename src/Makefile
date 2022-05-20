
# code details

EXE_DIR = .
EXE = $(EXE_DIR)/game

SRC= main.c GameOfLife.c Show.c Check.c

# generic build details

CC =     gcc
CFLAGS = -Wall -O
LIBS =   -lSDL2 -lSDL2_ttf 

SDLDIR = D:\SDL2
# compile to  object code

OBJ= $(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< 

# build executable

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(LIBS)

# clean up compilation

clean:
	rm -f $(OBJ) $(EXE)

# dependencies

main.o:  main.c DataStructure.h NextGenre.h GameWindow.h
GameOfLife.o:  GameOfLife.c DataStructure.h NextGenre.h GameWindow.h
Shwo.o: Show.c DataStructure.h GameWindow.h
Check.o: Check.c Check.h DataStructure.h