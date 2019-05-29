all : mysort

mysort : main.o mysort.o check.o
	gcc -o mysort -O2 main.o mysort.o check.o

main.o : main.c func.h 
	gcc -c -O2 main.c

mysort.o : mysort.c func.h
	gcc -c -O2 mysort.c

check.o : check.c func.h
	gcc -c -O2 check.c

clean:
	rm mysort *.o
