#ifndef _DATAGRAM_HPP
#define _DATAGRAM_HPP

#include <iostream>

#include "segment.hpp"

class Datagram {
  public:
  	Datagram(const std::string &src_ip, const std::string &dst_ip, const std::string &content) 
  	: source_ip_(src_ip), destination_ip_(dst_ip), segment_(new UDP_Segment(content)) {}
    void print_test() { std::cout << "|____ ip_src: " << source_ip_ << " dst_src: " << destination_ip_ << " content: " << segment_->get_message() << std::endl; }
    std::string get_message() { return segment_->get_message(); }
    std::string get_source_ip() { return source_ip_; }
  private:	
	  std::string source_ip_;
	  std::string destination_ip_;
      std::string content_;
      Segment* segment_;
};


#endif // _DATAGRAM_HPP