#include <utility>
#include "router.hpp"

Router::Router(const std::string &name, int number_of_interfaces)
	: name_(name), number_of_interfaces_(number_of_interfaces),
      interfaces_(number_of_interfaces_, Interface("0.0.0.0")), virtual_time_(0) {
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

void Interface::set_ip(const std::string &ip) {
	ip_ = ip;
}

void Interface::set_capacity(int capacity) {
	interface_capacity_ = capacity;
}