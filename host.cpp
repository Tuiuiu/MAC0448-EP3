#include "host.hpp"
#include <iostream>

Host::Host(const std::string &name) : name_(name), virtual_time_(0) {
}


void Host::set_ip(const std::string &ip) {
	ip_ = ip;
}

void Host::set_gateway_ip(const std::string &ip) {
	gateway_ip_ = ip;
}

void Host::set_dns_server_ip(const std::string &ip) {
	dns_server_ip_ = ip;
}

void Host::set_service_data(const std::string &type, const std::string &name) {
	service_name_ = name;
	if (type == "ircc")
		service_type_ = IRCC;
	else if (type == "ircs")
		service_type_ = IRCS;
	else if (type == "dnss")
		service_type_ = DNSS;
	else
		std::cout << "Tipo de serviço não existente!" << std::endl;
}

std::string Host::get_name() {
	return name_;
}

