OBJ=main.o min.o max.o
CC     = gcc
CFLAGS = -g -Wall -O2

main:$(OBJ)		#${OBJ}		alternative in this position
	$(CC) -o $@ $(OBJ)
main.o:main.c
	$(CC) $(CFLAGS) -o $@ -c $^
min.o:min.c
	$(CC) $(CFLAGS) -o $@ -c $^
max.o:max.c
	$(CC) $(CFLAGS) -o $@ -c $^
clean:
	$(RM) $(OBJ) main
