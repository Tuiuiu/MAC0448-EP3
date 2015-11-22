#ifndef _SEGMENT_HPP
#define _SEGMENT_HPP

class Segment
{
	public:
    	virtual std::string get_message() = 0;
};

class UDP_Segment : public Segment
{
	public:
		UDP_Segment(std::string message) : message_(message) {}
		std::string get_message() { return message_; } 
	private:
		int source_port_;
		int destination_port_;
		std::string message_;
};


#endif // _SEGMENT_HPP