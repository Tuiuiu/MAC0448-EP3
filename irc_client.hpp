#ifndef _IRC_CLIENT_HPP
#define _IRC_CLIENT_HPP

#include <string>
#include <iostream>
#include <fstream>

class Host;

class IRC_Client {
  public:
    IRC_Client() {}
  	void process_command(std::string command, Host & host);
  private:	
};

#include "host.hpp"

#endif // _IRC_CLIENT_HPP