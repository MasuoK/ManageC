all : runlength

runlength : main.o runlength.o check.o
	gcc -o runlength -O2 main.o runlength.o check.o

main.o : main.c func.h 
	gcc -c -O2 main.c

runlength.o : runlength.c func.h
	gcc -c -O2 runlength.c

check.o : check.c func.h
	gcc -c -O2 check.c

decode : runlength_decode.c
	gcc -o decode runlength_decode.c

clean:
	rm runlength *.o
