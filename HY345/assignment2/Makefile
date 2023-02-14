#Xristos Papastamos csd4569
all:
	make ferry
	make narrow

ferry:
	gcc -pthread -o ferry ferry.c -lm

narrow:
	gcc -pthread -o nr narrow.c

clean: 
	rm nr ferry a.out a.exe