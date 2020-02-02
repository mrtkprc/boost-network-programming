#include "SyncUDPClient.h"

SyncUDPClient::SyncUDPClient() :
    m_sock(m_ios)
{
    m_sock.open(asio::ip::udp::v4());
}

void SyncUDPClient::sendRequest(const asio::ip::udp::endpoint &ep, const std::string &request)
{
    m_sock.send_to(asio::buffer(request), ep);
}

std::string SyncUDPClient::receiveResponse(asio::ip::udp::endpoint &ep)
{
    char response[6];

    std::size_t bytes_received = m_sock.receive_from(asio::buffer(response), ep);

    m_sock.shutdown(asio::ip::udp::socket::shutdown_both);


    return std::string(response, bytes_received);
}


std::string SyncUDPClient::emulationLongComputationOp(unsigned int duration_sec, const std::string &raw_ip_address,
                                                      unsigned short port_num)
{
    const std::string request = "EMULATION_LONG_COMP_OP" + std::to_string(duration_sec) + "\n";

    asio::ip::udp::endpoint ep(asio::ip::address::from_string(raw_ip_address), port_num);
    sendRequest(ep, request);
    return receiveResponse(ep);
}

