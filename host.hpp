#include "foda-se.h"

class Host {
  private:
  public:
  	string name;
  	string ip;
  	string gateway_ip;
  	string dns_server_ip;
  	std::vector<Link> links;
};