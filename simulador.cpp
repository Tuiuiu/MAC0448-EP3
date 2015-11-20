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

    parse("entrada.txt", hosts, routers, links);

    for (auto& z: links) {
        z.stop_sniffing();
    }
}