#include <utility>
#include "router.hpp"

Router::Router(std::string name, int number_of_interfaces) {
	name_ = name;
	number_of_interfaces_ = number_of_interfaces;
    ips = std::move(std::vector<std::string>(number_of_interfaces_,"0.0.0.0"));
}


void Router::set_ip(int port, std::string ip) {
	ips[port] = ip;
}
