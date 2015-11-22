#ifndef _SEGMENT_HPP
#define _SEGMENT_HPP

class Segment
{
	public:
    	virtual std::string get_message() = 0;
    	virtual std::string get_info() = 0;
    	virtual int get_source_port() = 0;
    	virtual int get_destination_port() = 0;
    	virtual std::string get_type() = 0;
    	virtual size_t get_full_length() = 0;
    	virtual size_t get_message_length() = 0;
};

class UDP_Segment : public Segment
{
	public:
		UDP_Segment(int source_port, int destination_port, std::string message) 
		: source_port_(source_port), destination_port_(destination_port), message_(message) {}
		std::string get_info() { return std::string(" src_port: ") + std::to_string(source_port_) + " dst_port: " + std::to_string(destination_port_) + " msg: " + message_; }
		std::string get_message() { return message_; }
		int get_source_port() { return source_port_; }
		int get_destination_port() { return destination_port_; }
		size_t get_full_length() { return ( sizeof(source_port_) + sizeof(destination_port_) + message_.size() ); }
		size_t get_message_length() { return message_.size(); }
		std::string get_type() { return "17"; }
	private:
		int source_port_;
		int destination_port_;
		std::string message_;
};


#endif // _SEGMENT_HPP