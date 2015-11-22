#include <regex>

#include "dns_server.hpp"

void DNS_Server::process_command(std::string command, Host & host)
{
}

void DNS_Server::receive_datagram(Datagram datagram, Host & host)
{
	printf("=====================================================OI \n");

	std::smatch result;
    if (std::regex_search(datagram.get_message(), result, std::regex("^(\\w+) A IN$")))
    {
    	std::string hostname = result[1];
    	std::unordered_map<std::string, std::string>::const_iterator iterator = dns_mappings_.find(hostname);
		if (iterator == dns_mappings_.end()) // Não encontrou
		{	
			//printf("Não encontrou\n");
		}
		else // Encontrou
		{
			//printf("Encontrou\n");
			std::string source = host.ip_;
			std::string destination = datagram.get_source_ip();
			std::string content = hostname + " A IN " + dns_mappings_.at(hostname);
			host.datagram_queue.emplace_back(source, destination, content);
		}
    }
}

void DNS_Server::add_dns(std::string hostname, std::string ip)
{
	dns_mappings_.insert({hostname, ip});
}

void DNS_Server::print_dns()
{
	for (auto mapping : dns_mappings_)
		printf("    |____ %s: %s\n", mapping.first.c_str(), mapping.second.c_str());
}