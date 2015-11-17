#include <cstdio>
#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

#include "host.hpp"
#include "router.hpp"

int main (int argc, char **argv) {
	std::ifstream file("entrada.txt");
    std::string str;
    std::vector<Host> hosts;
    std::vector<Router> routers;

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
    }
}