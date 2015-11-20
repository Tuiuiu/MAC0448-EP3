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
	sniff_output_.open (file_name);
	sniff_output_ << "Sniffing interfaces " << deviceA_ << " to " << deviceB_ << ".\n";
}

void Link::stop_sniffing()
{
	sniff_output_.close();
}