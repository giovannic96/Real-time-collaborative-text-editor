#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include <iostream>
#include "myServer.h"

int main(int argc, char* argv[])
{
    try
    {
        boost::asio::io_context io_context;
        myServer s(io_context, std::atoi("63504"));
        io_context.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}