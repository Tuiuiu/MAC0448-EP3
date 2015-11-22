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
	{
		service_type_ = IRCC;
		application_ = new IRC_Client();
	}
	else if (type == "ircs")
		service_type_ = IRCS;
	else if (type == "dnss")
	{
		service_type_ = DNSS;
		application_ = new DNS_Server();
	}
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


void Host::new_tick()
{
	while (!commands_.empty() && commands_.front().get_time() == virtual_time_)
	{
		Command command = commands_.front();
		commands_.pop();
		std::string cmd_string = command.get_command();

		if (service_type_ == IRCC)
			application_->process_command(cmd_string, *this);
	}
	virtual_time_++;
}


void Host::add_dns(std::string host, std::string ip)
{
	if (service_type_ == DNSS)
		((DNS_Server*) application_)->add_dns(host, ip);
	else
		printf("%s não é um servidor DNS\n", name_.c_str());
}

void Host::print_dns()
{
	if (service_type_ == DNSS)
	{
		printf("Mapeamentos DNS de %s:\n", name_.c_str());
		((DNS_Server*) application_)->print_dns();
	}
	else
		printf("%s não é um servidor DNS\n", name_.c_str());
}

void Host::print_test() {
	std::queue<Command> aux = commands_;
	std::cout << "IP do Host: " << ip_ << std::endl;
	std::cout << "    |____ Gateway IP: " << gateway_ip_ << std::endl;
	std::cout << "    |____ DNS Server IP: " << dns_server_ip_ << std::endl;
    std::cout << "    |____ Service name: " << service_name_ << std::endl;
    std::cout << "    |____ Service type: " << service_type_ << std::endl;
	std::cout << "    |____ Commands: " << commands_.size() << std::endl;
	while (!aux.empty()) {
        aux.front().print_test();
        aux.pop();
    }

}

void Host::print_datagrams()
{
	std::cout << "Datagramas do host " << name_ << std::endl;
	for (auto& datagram : datagram_queue)
	{
		datagram.print_test();
	}
}
