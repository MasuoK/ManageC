all : bsort

bsort : main.o bsort.o check.o
	gcc -o bsort main.o bsort.o check.o

main.o : main.c func.h 
	gcc -c main.c

bsort.o : bsort.c func.h
	gcc -c bsort.c

check.o : check.c func.h
	gcc -c check.c

decode: b_sort_decode.c
	gcc -o decode b_sort_decode.c

clean :
	rm -f *.o *~ bsort
