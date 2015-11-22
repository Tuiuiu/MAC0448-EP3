#include <regex>

#include "dns_server.hpp"

void IRC_Server::receive_datagram(Datagram datagram, Host & host)
{
	std::smatch result;
	std::string message = datagram.get_message();
    if (std::regex_search(message, result, std::regex("^CONNECT$"))
    	|| std::regex_search(message, result, std::regex("^USER [\\w\\d]+$"))
    	|| std::regex_search(message, result, std::regex("^QUIT$"))
    	)
    {
    	std::string source = host.ip_;
		std::string destination = datagram.get_source_ip();
		std::string content = ":" + host.get_name() + " " + message;
    	host.datagram_queue.emplace_back(source, destination, content);
    }
}
