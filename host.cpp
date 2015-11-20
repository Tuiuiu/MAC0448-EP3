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

void Host::add_command(int command_time, std::string command)
{
	commands_.emplace(command_time, command);
}

bool Host::is_application(std::string app_name)
{
	return service_name_ == app_name;
}

void Host::print_test() {
	std::cout << "IP do Host: " << ip_ << std::endl;
	std::cout << "    |____ Gateway IP: " << gateway_ip_ << std::endl;
	std::cout << "    |____ DNS Server IP: " << dns_server_ip_ << std::endl;
    std::cout << "    |____ Service name: " << service_name_ << std::endl;
    std::cout << "    |____ Service type: " << service_type_ << std::endl;
	std::cout << "    |____ Commands: " << commands_.size() << std::endl;
	while (!commands_.empty()) {
        commands_.front().print_test();
        commands_.pop();
    }

}