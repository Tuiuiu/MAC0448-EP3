#ifndef _DATAGRAM_HPP
#define _DATAGRAM_HPP

class Datagram {
  public:
  	Datagram(const std::string &src_ip, const std::string &dst_ip, const std::string &content) 
  	: source_ip_(src_ip), destination_ip_(dst_ip), content_(content) {}
    void print_test() { std::cout << "|____ ip_src: " << source_ip_ << " dst_src: " << destination_ip_ << " content: " << content_ << std::endl; }
  private:	
	  std::string source_ip_;
	  std::string destination_ip_;
    std::string content_;
};


#endif // _DATAGRAM_HPP