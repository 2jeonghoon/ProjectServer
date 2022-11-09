main: main.o queue.o
	gcc -g -o main main.o queue.o
main.o: main.c
	gcc -c main.c

ingredient: ingredient.o queue.o
	gcc -g -o ingredient  ingredient.o queue.o
ingredient.o: ingredient.c
	gcc -c ingredient.c

gasRange: gasRange.o queue.o
	gcc -g -o gasRange gasRange.o queue.o
gasRange.o: gasRange.c
	gcc -c gasRange.c

setFood: setFood.o queue.o
	gcc -g -o setFood setFood.o queue.o
setFood.o: setFood.c
	gcc -c setFood.c

makeshm: makeshm.o queue.o
	gcc -g -o makeshm makeshm.o queue.o
makeshm.o: makeshm.c
	gcc -c makeshm.c

queue.o: queue.c
	gcc -c queue.c

clean:
	rm -rf *.o
