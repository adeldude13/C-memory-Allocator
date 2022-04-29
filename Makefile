CC := gcc
CFiles := main.c alloc.c
Headers := alloc.h
Args := -ggdb3 -O0 -lm -Wall -o main
Files := $(CFiles) $(Headers)

main: $(Files)
	$(CC) $(Args) $(CFiles)
