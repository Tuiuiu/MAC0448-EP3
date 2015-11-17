class Router {
  private:
  public:
  	string name;
  	int number_of_interfaces;
  	std::vector<string> ips;
  	std::vector<Link> links;
};