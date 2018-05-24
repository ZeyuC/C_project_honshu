CC = gcc -Wall -Wextra -ansi -g
SDL = -framework SDL2 -framework SDL2_image -framework SDL2_ttf
LDFLAGS = $(SDL)
all : main

main: main.o structgrille.o structuile.o pile.o structure.o ../lotB/recouvrement.c ../lotB/village.c ../lotC/retrait.c ../lotC/Honshu_Opt.c ../lotD/mainSDL.o
	$(CC) $(LDFLAGS) $^ -o $@

main.o: main.c structgrille.h ../lotB/recouvrement.h structuile.h structure.h pile.h
	$(CC) -c $<


lot_a : structure.o structuile.o structgrille.o pile.o
	$(CC)  $^ -o $@


structure.o : structure.c structure.h
	$(CC) -c $< -o $@

structuile.o  :  structuile.c  structuile.h
	$(CC) -c $< -o $@

structgrille.o : structgrille.c structgrille.h
	$(CC) -c $< -o $@

pile.o : pile.c pile.h
	$(CC) -c $< -o $@

testunit.o: testunit.c
	$(CC) -L -lcunit -c $^ -o $@ -lcunit

testunit: testunit.o structure.o structuile.o structgrille.o pile.o
	$(CC) -L -lcunit $^ -o $@ -lcunit

mainSDL.o: ../lotD/mainSDL.c ../lotD/mainSDL.h
	clang++ -c -std=c++11 $< -o $@

clean:
	rm -f *.o
	rm -f lot_a
	rm -f main

doxyfile:
	doxygen Doxyfile
