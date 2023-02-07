CCFLAGS=--std=gnu++98 -pedantic -Wall -Werror -ggdb3
correl_matrix: main.o asset.o
	g++ -o correl_matrix $(CCFLAGS) main.o asset.o

%.o: %.cpp asset.h
	g++ -c $(CCFLAGS) $<
clean:
	rm -f *.o  *~ correl_matrix
