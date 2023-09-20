all: myls mysearch mystat mytail

myls: myls-Alexander.c
	gcc -o myls myls-Alexander.c

mysearch: mysearch-Alexander.c
	gcc -o mysearch mysearch-Alexander.c

mystat: mystat-Alexander.c
	gcc -o mystat mystat-Alexander.c

mytail: mytail-Alexander.c
	gcc -o mytail mytail-Alexander.c


