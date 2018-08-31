# Raspberry Pi Explore environment

Exploring Raspberry Pi using C/C++ programming language

## Items

- multithread test
- gps client for Raspberry Pi based on the [gpsd](http://www.catb.org/gpsd/client-howto.html)

## Requirements

- gcc version 6.3.x or higher
- GNU Make 4.1 or higher

### Libraries

Depending of which client you want to test it is necessary to install the specific library. Otherwise you can install all libraries in order to compile using `make`.

#### GPS lib

- [gpsd](http://www.catb.org/gpsd/client-howto.html) lib `sudo apt-get install libgps-dev`
- [wiringPi](http://wiringpi.com/download-and-install/) lib

## Execution

Execute the command `make` under the root directory and an executalbe file `main` will be create at the `bin` directory.



