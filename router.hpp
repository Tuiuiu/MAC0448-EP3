#ifndef _ROUTER_HPP
#define _ROUTER_HPP


#include <string>
#include <vector>

class Interface {
  public:
  	Interface(const std::string &ip) : ip_(ip), interface_capacity_(0) {}
  	void set_ip(const std::string &ip);
    void set_capacity(int capacity);
  private:
	std::string ip_;
  	int interface_capacity_;
};

class Router {
  public:
  	Router(const std::string &name, int number_of_interfaces);
  	void set_interface_ip(int port, const std::string &ip);
  	void set_interface_capacity(int port, int capacity);
  	void set_processment_speed(int processment_speed);
  	std::string get_name();

  private:
  	std::string name_;
  	int number_of_interfaces_;
  	std::vector<Interface> interfaces_;

  	int virtual_time_;
	int processment_speed_;



  	// std::vector<Link> links;
};

#endif // _ROUTER_HPP