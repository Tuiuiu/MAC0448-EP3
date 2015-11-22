#include <cstdio>
#include <vector>
#include <unordered_map>

#include "host.hpp"
#include "router.hpp"
#include "link.hpp"
#include "parser.hpp"

int main (int argc, char **argv) {
    {
        std::vector<LinkPtr> links;
        std::unordered_map<std::string, Host> hosts;
        std::unordered_map<std::string, Router> routers;
        int finish_time;
        int simulator_tick; // tempo em microssegundos desde que começou a simulação

        parse("entrada.txt", hosts, routers, links, finish_time);
        printf("finish_time = %d\n", finish_time);
        
        for (simulator_tick = 0; simulator_tick <= finish_time; simulator_tick++)
        {
        	for (auto& host : hosts)
        	{
        		host.second.network_tick();
        	}
        	for (auto& router : routers)
        	{
        		router.second.network_tick();
        	}
        	for (auto link : links)
        	{
        		link->network_tick();
        	}
        }

        for (auto z: links) {
            z->stop_sniffing();
        }
        
        for (auto& h: hosts) {
            h.second.print_datagrams();
        }
    }
    return 0;
}