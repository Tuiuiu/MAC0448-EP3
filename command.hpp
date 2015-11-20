#ifndef _COMMAND_HPP
#define _COMMAND_HPP

#include <iostream>

class Command
{
  public:
    Command(float time, std::string command) : time_(time), command_(command) {}
    void print_test() { std::cout << "      |____ at time : " << time_ << " execute command \"" << command_ << "\"" << std::endl; }
  private:
    float time_;
    std::string command_;
};


#endif // _COMMAND_HPP