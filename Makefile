
CC=gcc
CCFLAGS= -Wall -Wcomment -lm -lgps -lpthread
TARGET=bin
SRC=src

all: clean compile

%.o : %.c
	$(CC) -c $(CCFLAGS) $<

compile:
	$(CC) $(SRC)/main.c $(SRC)/multithread/testMultiThread.c $(SRC)/gps/gpsClient.c $(CCFLAGS) -o $(TARGET)/main

clean:
	rm -Rf $(TARGET)/*
