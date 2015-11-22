#ifndef _DATAGRAM_HPP
#define _DATAGRAM_HPP

#include <iostream>

#include "segment.hpp"

class Datagram {
  public:
    Datagram(const std::string &src_ip, const std::string &dst_ip, Segment* segment) 
    : source_ip_(src_ip), destination_ip_(dst_ip), segment_(segment), ttl_(64) {}
    void print_test() { std::cout << "|____ ip_src: " << source_ip_ << " ip_dst: " << destination_ip_ << segment_->get_info() << std::endl; }
    std::string get_source_ip() { return source_ip_; }
    std::string get_destination_ip() { return destination_ip_; }
    std::string get_message() { return segment_->get_message(); }
    std::string get_id() { return id_; }
    std::string get_type() { return segment_->get_type(); }
    int get_source_port() { return segment_->get_source_port(); }
    int get_destination_port() { return segment_->get_destination_port(); }
    void decrement_ttl() { ttl_--; }
  private:	
	std::string source_ip_;
	std::string destination_ip_;
    Segment* segment_;
    std::string id_;
	int ttl_;
};


#endif // _DATAGRAM_HPP