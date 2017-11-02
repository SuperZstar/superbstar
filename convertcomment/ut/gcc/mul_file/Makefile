main:main.o max.o min.o
	gcc -o main main.o max.o min.o
main.o:main.c
	gcc -o main.o -c main.c
max.o:max.c
	gcc -o max.o -c max.c
min.o:min.c
	gcc -o min.o -c min.c
clean:
	rm *.o main
