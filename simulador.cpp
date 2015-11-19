#include <cstdio>
#include <fstream>
#include <iostream>
#include <regex>
#include <vector>
#include <unordered_map>

#include "host.hpp"
#include "router.hpp"
#include "link.hpp"

int main (int argc, char **argv) {
	std::ifstream file("entrada.txt");
    std::string str;
    // std::vector<Host> hosts;
    // std::vector<Router> routers;
    std::vector<Link> links;
    std::unordered_map<std::string, Host> hosts;
    std::unordered_map<std::string, Router> routers;

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
        	links.emplace_back(result[1], result[2], stoi(result[3]), stoi(result[4]));
        }
        else if (std::regex_search(str, result, std::regex("^set ip (\\w+)\\s+([\\d\\.]+)\\s+([\\d\\.]+)\\s+([\\d\\.]+)$")))
        {
        	std::cout << "IP de host: " << result[1] << " " << result[2] << " " << result[3] << " " << result[4] << std::endl;
        }
        else if (std::regex_search(str, result, std::regex("^set ip (\\w+)(\\s+(\\d+)\\s+([\\d\\.]+))+$")))
        {
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
        	}
        }
        else if (!str.empty())
        	std::cout << "Linha não compreendida: " << str << std::endl;
    }

    for (auto& x: hosts)
        std::cout << x.first << ": " << x.second.get_name() << std::endl;

    for (auto& y: routers)
        std::cout << y.first << ": " << y.second.get_name() << std::endl;
}

