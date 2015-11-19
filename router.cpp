#include <utility>
#include "router.hpp"

Router::Router(const std::string &name, int number_of_interfaces)
	: name_(name), number_of_interfaces_(number_of_interfaces),
      ips_(number_of_interfaces_, "0.0.0.0"), virtual_time_(0) {
}


void Router::set_ip(int port, const std::string &ip) {
	ips_[port] = ip;
}
