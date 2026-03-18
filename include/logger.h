#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <map>

std::string get_current_time();

void write_log(const std::string &raw_message,
               const std::map<std::string, std::string> &parsed_data,
               const std::string &alert_message = "");

#endif