
CC=gcc
CCFLAGS= -Wall -Wcomment -lm -lgps -lpthread
TARGET=bin
SRC=src

all: clean compile

%.o : %.c
	$(CC) -c $(CCFLAGS) $<

compile:
	mkdir $(TARGET)
	$(CC) $(SRC)/main.c $(SRC)/multithread/testMultiThread.c $(SRC)/gps/gpsClient.c $(SRC)/serial/read_serial.c $(SRC)/utils/metrics.c $(CCFLAGS) -o $(TARGET)/main

clean:
	rm -Rf $(TARGET)
