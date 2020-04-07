#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
#pragma ide diagnostic ignored "cert-msc32-c"
#include <memory>
#include <boost/asio.hpp>
#include <iostream>
#include "header_files/myServer.h"
#include <QtSql/QSqlDatabase>
#include "header_files/dbService.h"

void cleanDBFlags(){
    dbService::DB_RESPONSE resp = dbService::tryCleanAll();
    QSqlDatabase::removeDatabase("MyConnect2");
}

int main(int argc, char* argv[])
{
    try
    {
        cleanDBFlags();
        srand(time(nullptr));
        boost::asio::io_context io_context;
        tcp::endpoint endpoint(tcp::v4(), std::atoi("63505"));
        myServer s(io_context, endpoint);
        io_context.run();
    }
    catch (std::exception& e)
    {
        cleanDBFlags();
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}
#pragma clang diagnostic pop