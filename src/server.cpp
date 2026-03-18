#include <iostream>
#include <string>
#include <vector>
#include <boost/asio.hpp>
#include "../include/parser.h"
#include "../include/logger.h"

using boost::asio::ip::tcp;

int main()
{
    try
    {
        boost::asio::io_context io_context;

        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8081));
        std::cout << "Server is listening on port 8081...\n";

        while (true)
        {
            tcp::socket socket(io_context);
            acceptor.accept(socket);

            std::cout << "Client connected: "
                      << socket.remote_endpoint().address().to_string()
                      << ":"
                      << socket.remote_endpoint().port() << "\n";

            char data[1024] = {0};
            size_t length = socket.read_some(boost::asio::buffer(data));

            std::string received_message(data, length);
            std::cout << "Received: " << received_message << "\n";

            auto parsed_data = parse_message(received_message);

            if (!has_required_fields(parsed_data))
            {
                std::string error_response = "ERROR: malformed device message\n";
                boost::asio::write(socket, boost::asio::buffer(error_response));
                std::cout << "ERROR: Missing required fields.\n";
                std::cout << "----------------------------------------\n";
                continue;
            }

            int temp = 0;
            int pressure = 0;

            if (!safe_to_int(parsed_data["TEMP"], temp) ||
                !safe_to_int(parsed_data["PRESSURE"], pressure))
            {
                std::string error_response = "ERROR: invalid numeric field\n";
                boost::asio::write(socket, boost::asio::buffer(error_response));
                std::cout << "ERROR: Invalid numeric values.\n";
                std::cout << "----------------------------------------\n";
                continue;
            }

            std::cout << "Parsed Data:\n";
            std::cout << "  DEVICE   = " << parsed_data["DEVICE"] << "\n";
            std::cout << "  TEMP     = " << temp << "\n";
            std::cout << "  PRESSURE = " << pressure << "\n";
            std::cout << "  STATUS   = " << parsed_data["STATUS"] << "\n";

            std::vector<std::string> alerts;

            if (temp > 35)
            {
                alerts.push_back("High temperature detected");
                std::cout << "WARNING: High temperature detected!\n";
            }

            if (pressure > 110)
            {
                alerts.push_back("High pressure detected");
                std::cout << "WARNING: High pressure detected!\n";
            }

            std::string alert_message;
            if (!alerts.empty())
            {
                for (size_t i = 0; i < alerts.size(); i++)
                {
                    alert_message += alerts[i];
                    if (i + 1 < alerts.size())
                    {
                        alert_message += "; ";
                    }
                }
            }

            write_log(received_message, parsed_data, alert_message);

            std::string response = alerts.empty()
                                       ? "ACK: data received\n"
                                       : "ACK: data received with alerts\n";

            boost::asio::write(socket, boost::asio::buffer(response));

            std::cout << "----------------------------------------\n";
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Server error: " << e.what() << "\n";
    }

    return 0;
}