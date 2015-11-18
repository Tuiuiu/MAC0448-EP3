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

  	// std::vector<Link> links;
};