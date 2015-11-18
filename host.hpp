#include <string>

class Host {
  public:
  	Host(const std::string &name);
  	void set_ip(const std::string &ip);
  	void set_gateway_ip(const std::string &ip);
  	void set_dns_server_ip(const std::string &ip);
  
  private:
  	std::string name_;
  	std::string ip_;
  	std::string gateway_ip_;
  	std::string dns_server_ip_;

  	//std::vector<Link> links;
};

