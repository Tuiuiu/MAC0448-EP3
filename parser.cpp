#include <cstdio>
#include <regex>
#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_map>


#include "parser.hpp"

void parse(std::string file_name, std::unordered_map<std::string, Host>& hosts, std::unordered_map<std::string, Router>& routers, std::vector<Link>& links, int& finish_time)
{
    std::string str;
    std::ifstream file(file_name);
    while (std::getline(file, str))
    {
        //std::regex rgx_set_host("^set host (\\w+)$");
        std::smatch result;
        if (std::regex_search(str, result, std::regex("^set host (\\w+)$")))
        {
        	std::cout << "Host: " << result[1] << std::endl;
        	hosts.insert({result[1], Host(result[1])});
        }
        else if (std::regex_search(str, result, std::regex("^set router (\\w+) (\\d+)$")))
        {
        	std::cout << "Router: " << result[1] << " " << result[2] << std::endl;
        	routers.insert({result[1], Router(result[1], stoi(result[2]))});
        }
        else if (std::regex_search(str, result, std::regex("^set duplex-link ([\\w\\.]+)\\s+([\\w\\.]+)\\s+(\\d+)Mbps\\s+(\\d+)ms$")))
        {
        	std::cout << "Duplex-link: " << result[1] << " " << result[2] << " " << result[3] << " " << result[4] << std::endl;
            Link link(result[1], result[2], stoi(result[3]), stoi(result[4]));
        	links.push_back(link);
        }
        else if (std::regex_search(str, result, std::regex("^set ip (\\w+)\\s+([\\d\\.]+)\\s+([\\d\\.]+)\\s+([\\d\\.]+)$")))
        {
            std::string hostname = result[1];
            std::string host_ip = result[2];
            std::string gateway_ip = result[3];
            std::string dns_server_ip = result[4];
        	std::cout << "IP de host: " << hostname << " " << host_ip << " " << gateway_ip << " " << dns_server_ip << std::endl;
            hosts.at(hostname).set_ip(host_ip);
            hosts.at(hostname).set_gateway_ip(gateway_ip);
            hosts.at(hostname).set_dns_server_ip(dns_server_ip);
        }
        else if (std::regex_search(str, result, std::regex("^set ip (\\w+)(\\s+(\\d+)\\s+([\\d\\.]+))+$")))
        {
        	printf("IP de roteador\n");

        	std::regex_search(str, result, std::regex("^set ip (\\w+)(.+)$"));
        	std::string router_name = result[1];
        	std::string rest_of_string = result[2];
        	printf("router_name = %s\n", router_name.c_str());

        	while (!rest_of_string.empty())
        	{
        		std::regex_search(rest_of_string, result, std::regex("^\\s+(\\d+)\\s+([\\d\\.]+)(.*)$"));
        		int port = stoi(result[1]);
        		std::string ip = result[2];
        		rest_of_string = result[3];
        		printf("port = %d, ip = %s\n", port, ip.c_str());

                routers.at(router_name).set_interface_ip(port, ip);
        	}
        }
        else if (std::regex_search(str, result, std::regex("^set route (\\w+)(\\s+([\\d\\.]+)\\s+([\\d\\.]+))+$")))
        {
        	printf("Rota\n");

        	std::regex_search(str, result, std::regex("^set route (\\w+)(.+)$"));
        	std::string router_name = result[1];
        	std::string rest_of_string = result[2];
        	printf("router_name = %s\n", router_name.c_str());

        	while (!rest_of_string.empty())
        	{
        		std::regex_search(rest_of_string, result, std::regex("^\\s+([\\d\\.]+)\\s+([\\d\\.]+)(.*)$"));
        		std::string source = result[1];
        		std::string destination = result[2];
        		rest_of_string = result[3];
        		printf("source = %s, destination = %s\n", source.c_str(), destination.c_str());
        		routers.at(router_name).add_route(source, destination);
        	}
        }
        else if (std::regex_search(str, result, std::regex("^set performance (\\w+)\\s+(\\d+)us((\\s+(\\d+)\\s+(\\d+))+)$")))
        {
        	std::cout << "Performance: ";

            std::string router_name = result[1];
            int performance = stoi(result[2]);
            std::string rest_of_string = result[3];

            printf("router_name = %s, performance = %d\n", router_name.c_str(), performance);

            routers.at(router_name).set_processment_speed(performance);
        	
        	while (!rest_of_string.empty())
        	{
        		std::regex_search(rest_of_string, result, std::regex("^\\s+(\\d+)\\s+(\\d+)(.*)$"));
        		int port = stoi(result[1]);
        		int queue_capacity = stoi(result[2]);
        		rest_of_string = result[3];
        		routers.at(router_name).set_interface_capacity(port, queue_capacity);
        		printf("port = %d, queue_capacity = %d\n", port, queue_capacity);
        	}

        }
        else if (std::regex_search(str, result, std::regex("^set ([a-z]+) (\\w+) (\\w+)$")))
        {
            std::string app_type = result[1];
            std::string hostname = result[2];
            std::string app_name = result[3];
        	std::cout << "Agente da camada de aplicação: ";
        	for (unsigned int i = 1; i < result.size(); i++)
        		std::cout << result[i] << " | ";
        	std::cout << std::endl;
            hosts.at(hostname).set_service_data(app_type, app_name);
        }
        else if (std::regex_search(str, result, std::regex("^set sniffer ([\\w\\.]+)\\s+([\\w\\.]+)\\s+\"(.*)\"$")))
        {
        	std::cout << "Sniffer: ";
        	for (unsigned int i = 1; i < result.size(); i++)
        		std::cout << result[i] << " | ";
        	std::cout << std::endl;

            std::string deviceA = result[1], deviceB = result[2], file_name = result[3];

            for (Link& link : links)
                if (link.links(deviceA, deviceB))
                {
                    link.start_sniffing(file_name);
                    break;
                }
        }
        else if (std::regex_search(str, result, std::regex("^simulate ([\\d\\.]+)\\s+(\\w+)\\s+\"(.*)\"$")))
        {
        	std::cout << "Simulate: ";
        	for (unsigned int i = 1; i < result.size(); i++)
        		std::cout << result[i] << " | ";
        	std::cout << std::endl;

            int command_time = 1000000 * stof(result[1]);
            std::string app_name = result[2];
            std::string command = result[3];

            for (auto& x: hosts)
                if (x.second.is_application(app_name))
                {
                    x.second.add_command(command_time, command);
                    break;
                }
        }
        else if (std::regex_search(str, result, std::regex("^finish ([\\d\\.]+)$")))
        {
        	std::cout << "Finish: ";
        	for (unsigned int i = 1; i < result.size(); i++)
        		std::cout << result[i] << " | ";
        	std::cout << std::endl;
            finish_time = 1000000 * stof(result[1]);
        }
        else if (!str.empty())
        	std::cout << "Linha não compreendida: " << str << std::endl;
    }

    file.close();

    std::cout << "================= HOSTS =================" << std::endl;
    for (auto& x: hosts) {
        std::cout << x.first << ": " << x.second.get_name() << std::endl;
        x.second.print_test();
    }

    std::cout << "================= ROUTERS =================" << std::endl;
    for (auto& y: routers) {
        std::cout << y.first << ": " << y.second.get_name() << std::endl;
        y.second.print_test();
    }

    std::cout << "================= LINKS =================" << std::endl;
    for (auto& z: links) {
        z.print_test();
    }
}