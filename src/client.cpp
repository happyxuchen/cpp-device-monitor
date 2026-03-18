#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main()
{
    try
    {
        std::vector<std::string> devices = {"sensor1", "sensor2", "sensor3"};

        for (int i = 0; i < 6; i++)
        {
            boost::asio::io_context io_context;

            tcp::resolver resolver(io_context);
            auto endpoints = resolver.resolve("127.0.0.1", "8081");

            tcp::socket socket(io_context);
            boost::asio::connect(socket, endpoints);

            std::string device = devices[i % devices.size()];
            int temp = 30 + i * 2;
            int pressure = 100 + i * 3;

            std::string message =
                "DEVICE:" + device +
                ";TEMP:" + std::to_string(temp) +
                ";PRESSURE:" + std::to_string(pressure) +
                ";STATUS:OK";

            boost::asio::write(socket, boost::asio::buffer(message));

            char reply[1024] = {0};
            size_t reply_length = socket.read_some(boost::asio::buffer(reply));

            std::cout << "Sent: " << message << "\n";
            std::cout << "Server reply: ";
            std::cout.write(reply, reply_length);
            std::cout << "\n\n";

            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Client error: " << e.what() << std::endl;
    }

    return 0;
}