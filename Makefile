main: main.o foodlist.o food.o
	gcc -g -o main main.o foodlist.o food.o
ingredient: ingredient.o foodlist.o food.o
	gcc -g -o ingredient ingredient.o foodlist.o food.o
gasRange: gasRange.o foodlist.o food.o
	gcc -g -o gasRange gasRange.o foodlist.o food.o
setFood: setFood.o foodlist.o food.o
	gcc -g -o setFood setFood.o foodlist.o food.o

hall: hall.o foodlist.o food.o table.o
	gcc -g -o hall hall.o foodlist.o food.o table.o
serving: serving.o foodlist.o food.o table.o
	gcc -g -o serving serving.o foodlist.o food.o table.o
clean: clean.o foodlist.o food.o table.o
	gcc -g -o clean clean.o foodlist.o food.o table.o


main.o: main.c foodlist.h
	gcc -c main.c foodlist.h
ingredient.o: ingredient.c foodlist.h
	gcc -c ingredient.c foodlist.h
gasRange.o: gasRange.c foodlist.h
	gcc -c gasRange.c foodlist.h
setFood.o: setFood.c foodlist.h
	gcc -c setFood.c foodlist.h

foodlist.o: foodlist.c foodlist.h food.h define.h
	gcc -c foodlist.c foodlist.h food.h define.h
food.o: food.c food.h
	gcc -c food.c food.h



hall.o: hall.c foodlist.h
	gcc -c hall.c foodlist.h
serving.o: serving.c
	gcc -c serving.c
clean.o: clean.c
	gcc -c clean.c


table.o: table.c table.h
	gcc -c table.c table.h
