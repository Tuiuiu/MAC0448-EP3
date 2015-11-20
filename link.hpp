#ifndef _LINK_HPP
#define _LINK_HPP

#include <string>
#include <iostream>
#include <fstream>

/*
class Device {

};
*/

class Link {
  public:
  	Link(const std::string &deviceA, const std::string &deviceB, int speed, int latency) 
  	: deviceA_(deviceA), deviceB_(deviceB), speed_(speed), latency_(latency), is_sniffed_(false) {}
  	void print_test();
  	void start_sniffing(std::string file_name);
  	void stop_sniffing();
  	bool links(std::string A, std::string B);
  private:	
	std::string deviceA_;
	std::string deviceB_;
	int speed_;
	int latency_;
	bool is_sniffed_;
	std::ofstream *sniff_output_;
};


#endif // _LINK_HPP