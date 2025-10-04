all:
	gcc-14 -c src/validation.c -o validation.o
	gcc-14 -c src/trapezoid.c -o trapezoid.o
	gcc-14 -c src/functions.c -o functions.o
	gcc-14 -c main.c -o main.o
	gcc-14 validation.o trapezoid.o functions.o main.o -lm -o program