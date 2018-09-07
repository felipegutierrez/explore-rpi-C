
CC=gcc
CCFLAGS= -Wall -Wcomment -lm -lgps -lpthread -lwiringPi -lbcm2835
TARGET=bin
SRC=src

MULTITHREAD=$(SRC)/multithread/testMultiThread.c
GPS=$(SRC)/gps/gpsClient.c
READSERIAL=$(SRC)/serial/read_serial.c
METRICS=$(SRC)/utils/metrics.c
ULTRASONIC=$(SRC)/ultrasonic/ultrasonicClient.c
ULTRASONIC_BCM=$(SRC)/ultrasonic/ultrasonicBCM2835.c
GPIO_READ=$(SRC)/gpio/readall.c

all: clean compile

%.o : %.c
	$(CC) -c $(CCFLAGS) $<

compile:
	mkdir $(TARGET)
	$(CC) $(SRC)/main.c $(MULTITHREAD) $(GPS) $(READSERIAL) $(METRICS) $(ULTRASONIC) $(ULTRASONIC_BCM) $(GPIO_READ) $(CCFLAGS) -o $(TARGET)/main

clean:
	rm -Rf $(TARGET)
