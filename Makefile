CC = g++ 
CFLAGS = -g -std=c++20
LDLIBS = -lm

build: beamdrone.o curatare.o curse.o fortificatii.o

run-p1:
	./curatare

run-p2:
	./fortificatii

run-p3:
	./beamdrone

run-p4:
	./curse

beamdrone.o: beamdrone.cpp
	g++ $(CFLAGS) beamdrone.cpp -o beamdrone

curatare.o: curatare.cpp
	g++ $(CFLAGS) curatare.cpp -o curatare

curse.o: curse.cpp
	g++ $(CFLAGS) curse.cpp -o curse

fortificatii.o: fortificatii.cpp
	g++ $(CFLAGS) fortificatii.cpp -o fortificatii

.PHONY: clean

clean:
	rm -rf *.o beamdrone curatare curse fortificatii
