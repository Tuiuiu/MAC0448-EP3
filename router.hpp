#ifndef _ROUTER_HPP
#define _ROUTER_HPP


#include <string>
#include <vector>

class Router {
  public:
  	Router(const std::string &name, int number_of_interfaces);
  	void set_ip(int port, const std::string &ip);

  private:
  	std::string name_;
  	int number_of_interfaces_;
  	std::vector<std::string> ips_;

  	int virtual_time_;


  	// std::vector<Link> links;
};

#endif // _ROUTER_HPP