#ifndef _IRC_CLIENT_HPP
#define _IRC_CLIENT_HPP

#include <string>

#include "application.hpp"

class Host;

class IRC_Client : public Application {
  public:
    IRC_Client() {}
  	void process_command(std::string command, Host & host);
  	void receive_datagram(Datagram datagram, Host & host);
  private:	
};

#include "host.hpp"

#endif // _IRC_CLIENT_HPP