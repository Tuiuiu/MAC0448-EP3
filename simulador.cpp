#include <cstdio>
#include <vector>
#include <unordered_map>

#include "host.hpp"
#include "router.hpp"
#include "link.hpp"
#include "parser.hpp"

int main (int argc, char **argv) {
    std::vector<Link> links;
    std::unordered_map<std::string, Host> hosts;
    std::unordered_map<std::string, Router> routers;
    int finish_time;
    int server_tick = 0; // tempo em microssegundos desde que começou a simulação

    parse("entrada.txt", hosts, routers, links, finish_time);
    printf("finish_time = %d\n", finish_time);




    for (auto& z: links) {
        z.stop_sniffing();
    }
}