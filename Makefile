CC = gcc
CFLAGS = -Wall -g -O0
LIB = -pthread
CmBurnServer:CmBurnServer.c doublelist.c
	    $(CC) $(CFLAGS) $(LIB) $^ -o $@

clean:
	    $(RM)  CmBurnServer .*.sw?
