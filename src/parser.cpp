#include "../include/parser.h"
#include <sstream>
#include <cctype>

namespace
{
    std::string trim(const std::string &s)
    {
        size_t start = 0;
        while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start])))
        {
            start++;
        }

        size_t end = s.size();
        while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1])))
        {
            end--;
        }

        return s.substr(start, end - start);
    }
}

std::map<std::string, std::string> parse_message(const std::string &message)
{
    std::map<std::string, std::string> data;
    std::stringstream ss(message);
    std::string pair;

    while (std::getline(ss, pair, ';'))
    {
        size_t pos = pair.find(':');
        if (pos != std::string::npos)
        {
            std::string key = trim(pair.substr(0, pos));
            std::string value = trim(pair.substr(pos + 1));

            if (!key.empty() && !value.empty())
            {
                data[key] = value;
            }
        }
    }

    return data;
}

bool has_required_fields(const std::map<std::string, std::string> &data)
{
    return data.count("DEVICE") &&
           data.count("TEMP") &&
           data.count("PRESSURE") &&
           data.count("STATUS");
}

bool safe_to_int(const std::string &value, int &result)
{
    try
    {
        size_t idx = 0;
        int parsed = std::stoi(value, &idx);

        if (idx != value.size())
        {
            return false;
        }

        result = parsed;
        return true;
    }
    catch (...)
    {
        return false;
    }
}