#include <string>

class Host {
  public:
  	Host(std::string name) : name_(name) {}
  	void set_ip(std::string ip);
  	void set_gateway_ip(std::string ip);
  	void set_dns_server_ip(std::string ip);
  
  private:
  	std::string name_;
  	std::string ip_;
  	std::string gateway_ip_;
  	std::string dns_server_ip_;

  	//std::vector<Link> links;
};

