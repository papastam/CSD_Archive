###################################################
#
# file: Makefile
#
# @Author:   Iacovos G. Kolokasis
# @Version:  10-02-2021
# @email:    kolokasis@csd.uoc.gr
#
# Makefile
#
####################################################

CC = gcc
CFLAGS = -Wall -ansi -pedantic -g

translate:
	$(CC) $(CFLAGS) src/main.c -o $@

clean:
	-rm -f translate

turnin:
	-git tag assignment1
	-git push origin --tags

test:
	./translate < ./tests/test1.7 > test.1
	./translate < ./tests/test2.7 > test.2


	
