#include <regex>

#include "irc_server.hpp"

void IRC_Server::receive_datagram(Datagram datagram, Host & host)
{
	std::smatch result;
    std::string datagram_id = host.get_name();
	std::string message = datagram.get_message();
    if (std::regex_search(message, result, std::regex("^CONNECT$"))
    	|| std::regex_search(message, result, std::regex("^USER [\\w\\d]+$"))
    	|| std::regex_search(message, result, std::regex("^QUIT$"))
    	)
    {
        datagram_id = datagram_id + "." + std::to_string(host.get_count_and_add());
    	std::string source_ip = host.ip_;
        int source_port = IRC_SERVER_PORT;
		std::string destination_ip = datagram.get_source_ip();
        int destination_port = datagram.get_source_port();
		std::string content = ":" + host.get_name() + " " + message;
    	host.add_to_send_datagram_queue(Datagram(source_ip, destination_ip, new UDP_Segment(source_port, destination_port, content), datagram_id));
    }
}
