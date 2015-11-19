#ifndef _HOST_HPP
#define _HOST_HPP

#include <string>

enum Service { IRCC, IRCS, DNSS };

class Host {
  public:
  	Host(const std::string &name);
  	void set_ip(const std::string &ip);
  	void set_gateway_ip(const std::string &ip);
  	void set_dns_server_ip(const std::string &ip);
  	void set_service_data(const std::string &type, const std::string &name);
  	std::string get_name();
  
  private:
  	std::string name_;
  	std::string ip_;
  	std::string gateway_ip_;
  	std::string dns_server_ip_;
  	Service service_type_;
  	std::string service_name_;

  	int virtual_time_;

  	//std::vector<Link> links;
};


#endif // _HOST_HPP