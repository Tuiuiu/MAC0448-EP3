
class Router : public Device {
  private:
  public:
  	Router(string name, int number_of_interfaces) : name_(name), number_of_interfaces_(number_of_interfaces);
  	void set_ip(int port, string ip);

  	string name_;
  	int number_of_interfaces_;
  	std::vector<string> ips;

  	std::vector<Link> links;
};