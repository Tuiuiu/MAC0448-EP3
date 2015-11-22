#ifndef _ROUTER_HPP
#define _ROUTER_HPP

#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

#include "link.hpp"

class Router;

class Interface : public Device {
  public:
  	Interface(const std::string &ip) : ip_(ip), interface_capacity_(0) {}
  	void set_ip(const std::string &ip);
    void set_capacity(int capacity);
    void print_test(int number);
    void receive_datagram(Datagram content) override;
    bool send_datagram(Datagram content) override;
    void set_link(LinkPtr link) override { link_ = link; }
    unsigned int get_interface_capacity() { return interface_capacity_; }
    Interface* get_pointer();

    
    std::queue<Datagram> send_datagram_queue;    // deixar friend pro router
    std::queue<Datagram> received_datagram_queue; // deixar friend pro router
  private:
    std::string ip_;
    unsigned int interface_capacity_;
    Router *interface_router;

    LinkPtr link_;
};

class Router {
  public:
  	Router(const std::string &name, int number_of_interfaces);
  	void set_interface_ip(int port, const std::string &ip);
  	void set_interface_capacity(int port, int capacity);
  	void set_processment_speed(int processment_speed);
    void add_route(std::string source, std::string destination);
    void print_test();
    std::string get_name();
    void network_tick();
    Interface *get_interface(int number);

  private:
    bool is_ip(std::string input);

  	std::string name_;
  	int number_of_interfaces_;
  	std::vector<Interface> interfaces_;
  	int virtual_time_;
    int processment_speed_;
    int interface_to_be_processed_;
    int send_or_receive_;
	std::unordered_map<std::string, std::string> routes_;
    int processment_stage_;

};

#endif // _ROUTER_HPP