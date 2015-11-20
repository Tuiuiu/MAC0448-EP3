#include <regex>

#include "irc_client.hpp"

void IRC_Client::process_command(std::string command, Host & host)
{
	std::smatch result;
    if (std::regex_search(command, result, std::regex("^CONNECT (\\w+)\\s+(\\d+)$")))
    { // precisa de DNS
    	std::string content = "DNS " + std::string(result[1]);
    	host.datagram_queue.emplace_back(host.ip_, host.dns_server_ip_, content);
    }
}