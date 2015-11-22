#ifndef _HOST_HPP
#define _HOST_HPP

#include <queue>
#include <string>

#include "link.hpp"
#include "command.hpp"
#include "datagram.hpp"
#include "irc_client.hpp"
#include "dns_server.hpp"
#include "application.hpp"

enum Service { IRCC, IRCS, DNSS };


class Host : public Device {
  //friend class IRC_Client;
  public:
  	Host(const std::string &name);
  	void set_ip(const std::string &ip);
  	void set_gateway_ip(const std::string &ip);
  	void set_dns_server_ip(const std::string &ip);
  	void set_service_data(const std::string &type, const std::string &name);
    void print_test();
    void add_command(int command_time, std::string command);
    bool is_application(std::string app_name);
    void network_tick(); // override;
    void print_datagrams();
    void receive_datagram(Datagram content) override;
    bool send_datagram(Datagram content) override;
    void set_link(Link *link) override { link_ = link; }

    std::queue<Datagram> send_datagram_queue; // deixar privado e usar friend class
    std::queue<Datagram> received_datagram_queue; // deixar privado e usar friend class
    void add_dns(std::string host, std::string ip);
    void print_dns();

    std::string ip_;
    std::string dns_server_ip_;
      
  private:
    // std::string name_;
    std::string gateway_ip_;
    Service service_type_;
    std::string service_name_;
    std::queue<Command> commands_;

    Application* application_;

  	int virtual_time_;
    Link *link_;

  	//std::vector<Link> links;
};


#endif // _HOST_HPP