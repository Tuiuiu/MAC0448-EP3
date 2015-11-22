CXXFLAGS = -ansi -Wall -pedantic -std=c++11
CC = g++

simulator: simulator.o host.o router.o link.o parser.o irc_client.o dns_server.o irc_server.o

simulator.o host.o irc_client.o dns_server.o router.o link.o parser.o: host.hpp command.hpp router.hpp link.hpp parser.hpp application.hpp irc_client.hpp dns_server.hpp irc_server.hpp datagram.hpp segment.hpp 

.PHONY clean:
	rm *.o simulator
