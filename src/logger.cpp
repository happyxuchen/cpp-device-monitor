#include "../include/logger.h"
#include <fstream>
#include <ctime>

std::string get_current_time()
{
    std::time_t now = std::time(nullptr);
    char buf[100];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return std::string(buf);
}

void write_log(const std::string &raw_message,
               const std::map<std::string, std::string> &parsed_data,
               const std::string &alert_message)
{
    std::ofstream log_file("logs/device.log", std::ios::app);

    if (!log_file.is_open())
    {
        return;
    }

    log_file << "[" << get_current_time() << "] "
             << "RAW: " << raw_message << "\n";

    log_file << "  Parsed -> "
             << "DEVICE: " << parsed_data.at("DEVICE") << ", "
             << "TEMP: " << parsed_data.at("TEMP") << ", "
             << "PRESSURE: " << parsed_data.at("PRESSURE") << ", "
             << "STATUS: " << parsed_data.at("STATUS") << "\n";

    if (!alert_message.empty())
    {
        log_file << "  ALERT -> " << alert_message << "\n";
    }

    log_file << "\n";
}