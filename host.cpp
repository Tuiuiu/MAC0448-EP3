#include "host.hpp"

void Host::set_ip(std::string ip) {
	ip_ = ip;
}

void Host::set_gateway_ip(std::string ip) {
	gateway_ip_ = ip;
}

void Host::set_dns_server_ip(std::string ip) {
	dns_server_ip_ = ip;
}