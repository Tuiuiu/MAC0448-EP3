#ifndef _CLIENT_HPP
#define _CLIENT_HPP

class Host;

#include "datagram.hpp"

class Application
{
	public:
		virtual void process_command(std::string command, Host & host) = 0;
		virtual void receive_datagram(Datagram datagram, Host & host) = 0;
};

#include "host.hpp"

#endif // _CLIENT_HPP