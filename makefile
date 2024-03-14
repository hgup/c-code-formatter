# Aum Sri Sai Ram

format: main.o functions.o
	gcc main.o functions.o -o format

main.o: main.c
	gcc -c main.c

functions.o: functions.c
	gcc -c functions.c

clear:
	rm *.o
