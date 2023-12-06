CFLAGS = -O3 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_ttf -lm

INC = sdl2-light.h sdl2-ttf-light.h constantes.h graphique.h logique.h
SRC = main.c sdl2-light.c sdl2-ttf-light.c graphique.c logique.c
SPCTESTS = tests.c sdl2-light.c sdl2-ttf-light.c graphique.c logique.c
OBJ = $(SRC:%.c=%.o)
OBJTESTS = $(SPCTESTS:%.c=%.o)

PROG = spacebattle

%.o: %.c $(INC)
	gcc $(CFLAGS) -c $<

spacebattle: $(OBJ)
	gcc $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@

tests: $(OBJTESTS)
	gcc $(CFLAGS) $(OBJTESTS) $(LDFLAGS) -o $@

doc: $(PROG)
	doxygen ./$(PROG)
	make -C latex

clean:
	rm -f *~ *.o $(PROG)
	rm -f *~ *.o tests
	rm -rf latex html

