#include <cstdio>
#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

#include "host.hpp"
#include "router.hpp"
#include "link.hpp"

int main (int argc, char **argv) {
	std::ifstream file("entrada.txt");
    std::string str;
    std::vector<Host> hosts;
    std::vector<Router> routers;
    std::vector<Link> links;

    while (std::getline(file, str))
    {
        //std::regex rgx_set_host("^set host (\\w+)$");
        std::smatch result;
        if (std::regex_search(str, result, std::regex("^set host (\\w+)$")))
        {
        	std::cout << "Host: " << result[1] << std::endl;
        	hosts.emplace_back(result[1]);
        }
        else if (std::regex_search(str, result, std::regex("^set router (\\w+) (\\d+)$")))
        {
        	std::cout << "Router: " << result[1] << " " << result[2] << std::endl;
        	routers.emplace_back(result[1], stoi(result[2]));
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
        	/*std::cout << "IP de roteador: " << result[1] << " | " << result[2] << " | " << result[3] << " | " << result[4] << " | " << result[5] << " | " << result[6] << std::endl;
        	std::cout << "IP de roteador: " << result[1] << " | ";
        	for (unsigned int i = 3; i < result.size(); i += 3)
        		std::cout << result[i] << " " << result[i + 1] << " | ";
        	std::cout << std::endl;*/
        }
        else if (!str.empty())
        	std::cout << "Linha não compreendida: " << str << std::endl;
    }
}