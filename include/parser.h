#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <map>

std::map<std::string, std::string> parse_message(const std::string &message);

bool has_required_fields(const std::map<std::string, std::string> &data);

bool safe_to_int(const std::string &value, int &result);

#endif