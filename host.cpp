#include "host.hpp"

#include <iostream>

Host::Host(const std::string &name) : Device(name), virtual_time_(0) {
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

void Host::add_command(int command_time, std::string command)
{
	commands_.emplace(command_time, command);
}

bool Host::is_application(std::string app_name)
{
	return service_name_ == app_name;
}


void Host::network_tick()
{
	while (!commands_.empty() && commands_.front().get_time() == virtual_time_)
	{
		Command command = commands_.front();
		commands_.pop();
		std::string cmd_string = command.get_command();

		// ================== NESSE MOMENTO ==================
		// PROCESSAR O COMANDO ATRAVÉS DA APLICAÇÃO. A APLICAÇÃO
		// SERÁ RESPONSÁVEL POR COLOCAR NA FILA OS DATAGRAMAS A SEREM
		// ENVIADOS.
		if (service_type_ == IRCC)
			application_->process_command(cmd_string, *this);
	}

	if (!send_datagram_queue.empty())
		if (send_datagram(send_datagram_queue.front()))
			send_datagram_queue.pop();

	if (!received_datagram_queue.empty()) {
		// Recolhe os datagramas da fila de datagramas recebidos (provavelmente
		// vai ser só 1 por vez, mas né) e manipula ele do jeito que precisa.
		// Provavelmente o melhor a se fazer é algo como, enviar para a
		// aplicação, que daí ela processa esse datagrama e depois converte isso
		// em novos datagramas pra serem enviados.

		// application.receive_datagram(received_datagram_queue.front());
		// received_datagram_queue.pop();
	}

	virtual_time_ += 1;
}


void Host::add_dns(std::string host, std::string ip)
{
	if (service_type_ == DNSS)
		((DNS_Server*) application_)->add_dns(host, ip);
	else
		printf("%s não é um servidor DNS\n", get_name().c_str());
}

void Host::print_dns()
{
	if (service_type_ == DNSS)
	{
		printf("Mapeamentos DNS de %s:\n", get_name().c_str());
		((DNS_Server*) application_)->print_dns();
	}
	else
		printf("%s não é um servidor DNS\n", get_name().c_str());
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
	std::queue<Datagram> aux = send_datagram_queue;
	std::cout << "Datagramas do host " << get_name() << std::endl;
	while (!aux.empty()) {
		std::cout << "    |____ Content: " << aux.front().get_message() << std::endl;
		aux.pop();
	}
}

void Host::receive_datagram(Datagram content) {
	received_datagram_queue.push(content);
}

bool Host::send_datagram(Datagram content) {
	return link_->send_datagram(get_name(), content);
}
