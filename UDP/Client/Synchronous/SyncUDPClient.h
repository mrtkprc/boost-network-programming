#pragma once

#include <boost/asio.hpp>
#include <iostream>

using namespace boost;

class SyncUDPClient {
    asio::io_service m_ios;
    asio::ip::udp::endpoint m_ep;
    asio::ip::udp::socket m_sock;

    void sendRequest(const asio::ip::udp::endpoint &ep, const std::string &request);
    std::string receiveResponse(asio::ip::udp::endpoint &ep);

public:
    SyncUDPClient();

    std::string emulationLongComputationOp(unsigned int duration_sec, const std::string &raw_ip_address, unsigned short port_num);

};


