#include <regex>

#include "irc_client.hpp"

std::vector<std::string> commands_waiting_for_dns;

std::string connected_server_ip;
int connected_server_port;

void IRC_Client::process_command(std::string command, Host & host)
{
	std::smatch result;
    if (std::regex_search(command, result, std::regex("^CONNECT ([\\w\\d]+)\\s+(\\d+)$")))
    { // precisa de DNS
    	std::string content = std::string(result[1]) + " A IN";
    	host.add_to_send_datagram_queue(Datagram(host.ip_, host.dns_server_ip_, new UDP_Segment(DNS_CLIENT_PORT, DNS_SERVER_PORT, content)));
    	commands_waiting_for_dns.push_back(command);
    }
    else if (std::regex_search(command, result, std::regex("^CONNECT ([\\d\\.]+)\\s+(\\d+)$")))
    { // não precisa de DNS
    	std::string content = "CONNECT";
    	std::string destination_ip = result[1];
    	int destination_port = stoi(result[2]);
    	std::string source_ip = host.ip_;
    	int source_port = IRC_CLIENT_PORT;

    	host.add_to_send_datagram_queue(Datagram(source_ip, destination_ip, new UDP_Segment(source_port, destination_port, content)));
    }
    else if (std::regex_search(command, result, std::regex("^USER ([\\w\\d]+)$"))
    	|| std::regex_search(command, result, std::regex("^QUIT$")))
    {
    	std::string source_ip = host.ip_;
    	int source_port = IRC_CLIENT_PORT;
    	std::string destination_ip = connected_server_ip;
    	int destination_port = connected_server_port;
    	host.add_to_send_datagram_queue(Datagram(source_ip, destination_ip, new UDP_Segment(source_port, destination_port, command)));
    }
    else
    	printf("Comando desconhecido no %s\n", host.get_name().c_str());
}

void IRC_Client::receive_datagram(Datagram datagram, Host & host)
{
	int port = datagram.get_destination_port();
	if (port == DNS_CLIENT_PORT)
	{
		std::string dns_response = datagram.get_message();

		std::smatch result;
		std::regex_search(dns_response, result, std::regex("^(\\w+) A IN ([\\d\\.]+)$"));
		std::string response_hostname = result[1];
		std::string response_ip = result[2];

		for (std::string cmd : commands_waiting_for_dns)
		{
			std::smatch result2;
			std::regex_search(cmd, result2, std::regex("^CONNECT ([\\w\\d]+)\\s+(\\d+)$"));
			if (result2[1] == response_hostname)
			{
				std::string new_command = std::string("CONNECT ") + response_ip + " " + std::string(result2[2]);
				process_command(new_command, host);
			}
		}
	}
	else if (port == IRC_CLIENT_PORT)
	{
		std::string irc_response = datagram.get_message();

		std::smatch result;
		if (std::regex_search(irc_response, result, std::regex("^:([\\w\\d]+) CONNECT$")))
		{
			connected_server_ip = datagram.get_source_ip();
			connected_server_port = datagram.get_source_port();
		}
		printf("Datagrama desconhecido no %s\n", host.get_name().c_str());
	}
}