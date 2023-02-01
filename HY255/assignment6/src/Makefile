all: data3 data6 data9 

data3: createdata3.o
	gcc -ansi -Wall -pedantic -o createdata3.out createdata3.o
	./createdata3.out > data3.txt 


data6: createdata6.o
	gcc -ansi -Wall -pedantic -o createdata6.out createdata6.o
	./createdata6.out > data6.txt 


data9: createdata9.o
	gcc -ansi -Wall -pedantic -o createdata9.out createdata9.o
	./createdata9.out > data9.txt 


createdata3.o: createdata3.c
	gcc -ansi -Wall -pedantic -c createdata3.c 


createdata6.o: createdata6.c
	gcc -ansi -Wall -pedantic -c createdata6.c 


createdata9.o: createdata9.c
	gcc -ansi -Wall -pedantic -c createdata9.c 


clean:
	rm -f *.o
	rm -f *.out
	rm -f *.txt

