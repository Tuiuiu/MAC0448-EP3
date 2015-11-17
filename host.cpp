#include "host.hpp"

void Host::set_ip(string ip) {
	ip_ = ip;
}

void Host::set_gateway_ip(string ip) {
	gateway_ip_ = ip;
}

void Host::set_dns_server_ip(string ip) {
	dns_server_ip_ = ip;
}