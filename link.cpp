#include <iostream>

#include "link.hpp"

void Link::print_test() {
	std::cout << "Duplex-link entre " << deviceA_ << " e " << deviceB_ << std::endl;
	std::cout << "    |____ velocidade: " << speed_ << "Mbps" << std::endl;
	std::cout << "    |____ latencia: " << latency_ << "ms" << std::endl;
}

void Link::start_sniffing(std::string file_name)
{
	is_sniffed_ = true;
	sniff_output_ = new std::ofstream;
	sniff_output_->open (file_name);
	(*sniff_output_) << "Sniffing interfaces " << deviceA_ << " to " << deviceB_ << ".\n";
	//printf ("link %s para %s: is_sniffed_? %d\n", deviceA_.c_str(), deviceB_.c_str(), is_sniffed_);
}

void Link::stop_sniffing()
{
	//printf ("link %s para %s: is_sniffed_? %d\n", deviceA_.c_str(), deviceB_.c_str(), is_sniffed_);
	if (is_sniffed_)
		sniff_output_->close();
	is_sniffed_ = false;
}

bool Link::links(std::string A, std::string B)
{
	if ((A == deviceA_ && B == deviceB_) || (A == deviceB_ && B == deviceA_))
		return true;
	else
		return false;
}