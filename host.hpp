
class Host : public Device {
  private:
  public:
  	Host(name) : name_(name);
  	void set_ip(string ip);
  	void set_gateway_ip(string ip);
  	void set_dns_server_ip(string ip);

  	string name_;
  	string ip_;
  	string gateway_ip_;
  	string dns_server_ip_;
  	
  	std::vector<Link> links;
};

