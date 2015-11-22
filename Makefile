CXXFLAGS = -ansi -Wall -pedantic -std=c++11
CC = g++

simulador: simulador.o host.o router.o link.o parser.o irc_client.o

simulador.o: host.hpp router.hpp link.hpp parser.hpp

host.o: host.hpp command.hpp irc_client.hpp datagram.hpp link.hpp

irc_client.o: irc_client.hpp host.hpp

router.o: router.hpp link.hpp

link.o: link.hpp datagram.hpp

parser.o: parser.hpp

.PHONY clean:
	rm *.o simulador
