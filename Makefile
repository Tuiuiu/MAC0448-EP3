CXXFLAGS = -ansi -Wall -pedantic -std=c++11
CC = g++

simulador: simulador.o host.o router.o link.o parser.o

simulador.o: host.hpp router.hpp link.hpp parser.hpp

host.o: host.hpp

router.o: router.hpp

link.o: link.hpp

parser.o: parser.hpp

.PHONY clean:
	rm *.o simulador
