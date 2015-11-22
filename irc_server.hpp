#ifndef _IRC_SERVER_HPP
#define _IRC_SERVER_HPP

#include <string>
#include <unordered_map>

#include "application.hpp"
#define IRC_SERVER_PORT 6667

class Host;

class IRC_Server : public Application {
  public:
    IRC_Server() {}
  	void process_command(std::string command, Host & host) override {};
  	void receive_datagram(Datagram datagram, Host & host) override;
  private:
  	std::unordered_map<std::string, std::string> dns_mappings_;
};

#include "host.hpp"

#endif // _IRC_SERVER_HPP