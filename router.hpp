#include <string>

class Router {
  public:
  	Router(std::string name, int number_of_interfaces);
  	void set_ip(int port, std::string ip);
  private:
  	std::string name_;
  	int number_of_interfaces_;
  	std::vector<std::string> ips;

  	// std::vector<Link> links;
};