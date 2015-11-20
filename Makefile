CXXFLAGS = -ansi -Wall -pedantic -std=c++11
CC = g++

simulador: simulador.o host.o router.o link.o

simulador.o: host.hpp router.hpp link.hpp

host.o: host.hpp

router.o: router.hpp

link.o: link.hpp

.PHONY clean:
	rm *.o simulador
