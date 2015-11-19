#ifndef _LINK_HPP
#define _LINK_HPP

#include <string>

/*
class Device {

};
*/

class Link {
  public:
  	Link(const std::string &deviceA, const std::string &deviceB, int speed, int latency) 
  	: deviceA_(deviceA), deviceB_(deviceB), speed_(speed), latency_(latency) {}
  private:	
	std::string deviceA_;
	std::string deviceB_;
	int speed_;
	int latency_;
};


#endif // _LINK_HPP