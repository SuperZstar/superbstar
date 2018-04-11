main:main.o min.o max.o
	gcc -o main main.o min.o max.o
main.o:main.c
	gcc -o main.o -c main.c
min.o:min.c
	gcc -o min.o -c min.c
max.o:max.c
	gcc -o max.o -c max.c
clean:
	rm *.o main
