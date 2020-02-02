#pragma once

#include <boost/asio.hpp>
#include <iostream>

using namespace boost;

class SyncTCPClient {
    asio::io_service m_ios;
    asio::ip::tcp::endpoint m_ep;
    asio::ip::tcp::socket m_sock;

    void sendRequest(const std::string& request);
    std::string receiveResponse();

public:
    SyncTCPClient(const std::string& raw_ip_addres, unsigned short port_num);

    void connect();
    void close();
    std::string emulationLongComputationOp(unsigned int duration_sec);




};


