CLFAGS=-std=c99 -Wall -Werror -Wextra
CC=gcc
MAIN=proj1.c

.PHONY: main

main: $(MAIN)
	$(CC) $(CLFAGS) $(MAIN) -o proj1
