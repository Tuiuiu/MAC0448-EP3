#include <regex>
#include <utility>
#include <iostream>

#include "router.hpp"

void Interface::set_ip(const std::string &ip) {
	ip_ = ip;
}

void Interface::set_capacity(int capacity) {
	interface_capacity_ = capacity;
}

void Interface::print_test(int number) {
	std::cout << "    |____ interface number: " << number << " in IP " << ip_ << " with capacity " << interface_capacity_ << std::endl;
}

Router::Router(const std::string &name, int number_of_interfaces)
	: name_(name), number_of_interfaces_(number_of_interfaces),
      interfaces_(number_of_interfaces_, Interface("0.0.0.0", name)), 
      virtual_time_(0), interface_to_be_processed_(0), processment_stage_(-1) {
      	for (unsigned int i = 0; i < interfaces_.size(); i++) {
      		std::string nome = interfaces_[i].get_name();
      		nome += "." + std::to_string(i);
      		interfaces_[i].set_name(nome);
      	}
}

void Router::set_interface_ip(int port, const std::string &ip) {
	interfaces_[port].set_ip(ip);
}

void Router::set_interface_capacity(int port, int capacity) {
	interfaces_[port].set_capacity(capacity);
}

void Router::set_processment_speed(int processment_speed) {
	processment_speed_ = processment_speed;
}

void Router::add_route(std::string source, std::string destination)
{
	routes_[source] = destination;
}

void Router::print_test() {
	std::cout << "Router name: " << name_ << " with " << number_of_interfaces_ << " interfaces" << std::endl;
	std::cout << "    |____ processment speed: " << processment_speed_ << std::endl;
	for (unsigned int i = 0; i < interfaces_.size(); i++)
		interfaces_[i].print_test(i);
	std::cout << "    |____ Rotas: " << routes_.size() << std::endl;
	for (auto& k: routes_) {
        std::cout << "      |____ Origem: " << k.first << " Destino: " << k.second << std::endl;
    }

}

std::string Router::get_name() {
	return name_;
}

Interface* Interface::get_pointer() {
	return this;
}

Interface* Router::get_interface(int number) {
	return interfaces_[number].get_pointer();
}


void Router::network_tick() {
	bool got_datagram = false;
	unsigned int interfaces_visited = 0;

	for (unsigned int i = 0; i < interfaces_.size(); i++) {
		if (!interfaces_[i].send_datagram_queue.empty())
			if (interfaces_[i].send_datagram(interfaces_[i].send_datagram_queue.front()))
				interfaces_[i].send_datagram_queue.pop();
	}

	if (processment_stage_ != -1) processment_stage_ -= 1; // Mais um tick processando algum pacote
	if (processment_stage_ == -1) {
		while (!got_datagram || interfaces_visited < interfaces_.size()) {
			if(interfaces_[interface_to_be_processed_].received_datagram_queue.empty()) {
				interfaces_visited++;
				interface_to_be_processed_ = (interface_to_be_processed_ + 1) % interfaces_.size();
			} 
			else {
				processment_stage_ = processment_speed_;
				got_datagram = true;
			}
		}
	}

	if (processment_stage_ == 0) {
		Datagram datagram_to_be_sent = interfaces_[interface_to_be_processed_].received_datagram_queue.front();
		interfaces_[interface_to_be_processed_].received_datagram_queue.pop();

		std::string destination = datagram_to_be_sent.get_destination_ip();
		std::string interface;

		std::size_t found = destination.find_last_of('.');
		destination = destination.substr(0, found+1);
		destination += "0";
		// Pega o destination, substitui os ultimos numeros por 0
		interface = routes_[destination];
		while (is_ip(interface)) {
			found = interface.find_last_of('.');
			interface = interface.substr(0, found+1);
			interface += "0";

			interface = routes_[interface];
			// Pega interface, substitui os ultimos numeros por 0
			// interface = routes_[interface]; 
		}

		int interface_index = stoi(interface);
		if (interfaces_[interface_index].received_datagram_queue.size() 
		    + interfaces_[interface_index].send_datagram_queue.size() 
		    < interfaces_[interface_index].get_interface_capacity()) 
		{
			interfaces_[interface_index].send_datagram_queue.push(datagram_to_be_sent);
		}

		processment_stage_ = -1;
	}

	virtual_time_ += 1;
}

void Interface::receive_datagram(Datagram content) {
	if ((send_datagram_queue.size() + received_datagram_queue.size()) < interface_capacity_)
		received_datagram_queue.push(content);
}

bool Interface::send_datagram(Datagram content) {
	return link_->send_datagram(get_name(), content);
}

bool Router::is_ip(std::string input) {
    std::smatch result;
	if (std::regex_search(input, result, std::regex("^\\d+\\.\\d+\\.\\d+\\.\\d+$")))
		return true;
	else return false;
}