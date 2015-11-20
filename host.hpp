#ifndef _HOST_HPP
#define _HOST_HPP

#include <queue>
#include <string>

#include "command.hpp"
#include "datagram.hpp"
#include "irc_client.hpp"

enum Service { IRCC, IRCS, DNSS };

class Host {
  //friend class IRC_Client;
  public:
  	Host(const std::string &name);
  	void set_ip(const std::string &ip);
  	void set_gateway_ip(const std::string &ip);
  	void set_dns_server_ip(const std::string &ip);
  	void set_service_data(const std::string &type, const std::string &name);
  	std::string get_name();
    void print_test();
    void add_command(int command_time, std::string command);
    bool is_application(std::string app_name);
    void new_tick();
    void print_datagrams();
    std::vector<Datagram> datagram_queue; // deixar privado e usar friend class
    std::string ip_;
    std::string dns_server_ip_;
      
  private:
    std::string name_;
    std::string gateway_ip_;
    Service service_type_;
    std::string service_name_;
    std::queue<Command> commands_;
    IRC_Client application;

  	int virtual_time_;

  	//std::vector<Link> links;
};


#endif // _HOST_HPP