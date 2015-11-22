#ifndef _LINK_HPP
#define _LINK_HPP

#include <string>
#include <memory>
#include <fstream>
#include <iostream>

#include "datagram.hpp"

class Link;

class Device : public std::enable_shared_from_this<Device> {
  public:
  	Device(const std::string &name) : name_(name) {}
//  	virtual void network_tick() = 0;
  	virtual void receive_datagram(Datagram content) = 0;
  	virtual bool send_datagram(Datagram content) = 0;
  	virtual void set_link(Link *link) = 0;
  	std::string get_name() { return name_; }
    void set_name(const std::string &name) { name_ = name; }
  private:
  	std::string name_;
};

using DevicePtr = std::shared_ptr<Device>;


class Link {
  public:
  	Link(DevicePtr deviceA, DevicePtr deviceB, int speed, int latency) 
  	: deviceA_(deviceA), deviceB_(deviceB), speed_(speed), latency_(latency), is_sniffed_(false)
  	, processment_a_to_b_(-1), processment_b_to_a_(-1), virtual_time_(0), content_a_to_b_("","", nullptr) 
  	, content_b_to_a_("","", nullptr) {}
  	void print_test();
  	void start_sniffing(std::string file_name);
  	void stop_sniffing();
  	bool links(std::string A, std::string B);
  	bool send_datagram(std::string src_name, Datagram content); 
  	void network_tick();
  	void print_sniffed_content(int direction, Datagram content);

  private:	
	DevicePtr deviceA_;
	DevicePtr deviceB_;
	int speed_;
	int latency_;
	bool is_sniffed_;
	int processment_a_to_b_;
	int processment_b_to_a_;
	int virtual_time_;
	Datagram content_a_to_b_;
	Datagram content_b_to_a_;
	std::ofstream *sniff_output_;
};


#endif // _LINK_HPP