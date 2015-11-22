#ifndef _DNS_SERVER_HPP
#define _DNS_SERVER_HPP

#define DNS_SERVER_PORT 53
#define DNS_CLIENT_PORT 5000

#include <string>
#include <unordered_map>

#include "application.hpp"

class Host;

class DNS_Server : public Application {
  public:
    DNS_Server() {}
  	void process_command(std::string command, Host & host) {};
  	void receive_datagram(Datagram datagram, Host & host);
  	void add_dns(std::string hostname, std::string ip);
  	void print_dns();
  private:
  	std::unordered_map<std::string, std::string> dns_mappings_;
};

#include "host.hpp"

#endif // _DNS_SERVER_HPP