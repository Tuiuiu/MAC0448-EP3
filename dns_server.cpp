#include <regex>

#include "dns_server.hpp"

void DNS_Server::receive_datagram(Datagram datagram, Host & host)
{
	std::smatch result;
	std::string datagram_message = datagram.get_message();
	
    if (std::regex_search(datagram_message, result, std::regex("^(\\w+) A IN$")))
    {
    	std::string hostname = result[1];
    	std::unordered_map<std::string, std::string>::const_iterator iterator = dns_mappings_.find(hostname);
		if (iterator != dns_mappings_.end()) // Encontrou
		{
			// printf("Encontrou\n");
			std::string datagram_id = hostname + "." + std::to_string(host.get_count_and_add());
			std::string source_ip = host.ip_;
			int source_port = DNS_SERVER_PORT;
			std::string destination_ip = datagram.get_source_ip();
			int destination_port = datagram.get_source_port();
			std::string content = hostname + " A IN " + dns_mappings_.at(hostname);
			host.add_to_send_datagram_queue(Datagram(source_ip, destination_ip, new UDP_Segment(source_port, destination_port, content), datagram_id));
		}
		else 
		{
			printf("Hostname não encontrado.\n");
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