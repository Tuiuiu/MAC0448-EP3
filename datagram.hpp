#ifndef _DATAGRAM_HPP
#define _DATAGRAM_HPP

#include <iostream>

#include "segment.hpp"

class Datagram {
  public:
  	//Datagram(const std::string &src_ip, const std::string &dst_ip, const std::string &content) 
  	//: source_ip_(src_ip), destination_ip_(dst_ip), segment_(new UDP_Segment(content)) {}
    Datagram(const std::string &src_ip, const std::string &dst_ip, Segment* segment) 
    : source_ip_(src_ip), destination_ip_(dst_ip), segment_(segment) {}
    void print_test() { std::cout << "|____ ip_src: " << source_ip_ << " ip_dst: " << destination_ip_ << segment_->get_info() << std::endl; }
    std::string get_message() { return segment_->get_message(); }
    std::string get_source_ip() { return source_ip_; }
    int get_source_port() { return segment_->get_source_port(); }
    int get_destination_port() { return segment_->get_destination_port(); }
  private:	
	  std::string source_ip_;
	  std::string destination_ip_;
      std::string content_;
      Segment* segment_;
};


#endif // _DATAGRAM_HPP