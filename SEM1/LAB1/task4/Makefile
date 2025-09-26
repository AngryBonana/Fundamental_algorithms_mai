all:
	gcc-14 -c main.c -o main.o
	gcc-14 -c src/exponent.c -o exponent.o
	gcc-14 -c src/pi.c -o pi.o
	gcc-14 -c src/log.c -o log.o
	gcc-14 -c src/sqrt.c -o sqrt.o
	gcc-14 -c src/gamma.c -o gamma.o
	gcc-14 -c src/mathFunctions.c -o mathFunctions.o
	gcc-14 main.o exponent.o pi.o log.o sqrt.o gamma.o mathFunctions.o -o program -lm