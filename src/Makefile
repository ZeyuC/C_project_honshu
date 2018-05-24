CC = gcc -Wall -Wextra -ansi -g

all : main

main: main_test_recouvrement.c lotA/structgrille.c lotA/structuile.c lotA/pile.c lotA/structure.c lotB/recouvrement.c lotB/village.c lotC/retrait.c lotC/Honshu_Opt.c
	$(CC) $^ -o $@
lot : structure.o structuile.o structgrille.o pile.o recouvrement.o
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

recouvrement.o : recouvrement.o recouvrement.o


clean:
	git rm -f *.o
	git rm lot_a



