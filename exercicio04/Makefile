all: application
application: main.c image.o polygon.o util.o
	gcc main.c image.o polygon.o util.o -o application -lX11
image.o: image.c image.h
	gcc -o image.o -c image.c
polygon.o: polygon.c polygon.h util.o
	gcc -o polygon.o -c polygon.c
util.o: util.c util.h
	gcc -o util.o -c util.c
clean: 
	rm *.o