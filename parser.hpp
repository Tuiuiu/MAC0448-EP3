#ifndef _PARSER_HPP
#define _PARSER_HPP


#include "host.hpp"
#include "router.hpp"
#include "link.hpp"

void parse(std::string file_name, std::unordered_map<std::string, Host>& hosts, std::unordered_map<std::string, Router>& routers, std::vector<LinkPtr>& links, int& finish_time);


#endif // _PARSER_HPP