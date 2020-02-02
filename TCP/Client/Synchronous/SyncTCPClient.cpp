#include "SyncTCPClient.h"

SyncTCPClient::SyncTCPClient(const std::string& raw_ip_addres, unsigned short port_num):
    m_ep(asio::ip::address::from_string(raw_ip_addres), port_num),
    m_sock(m_ios)
{
    m_sock.open(m_ep.protocol());
}

void SyncTCPClient::sendRequest(const std::string &request)
{
    asio::write(m_sock,asio::buffer(request));
}

std::string SyncTCPClient::receiveResponse()
{
    asio::streambuf buf;
    asio::read_until(m_sock, buf, '\n');
    std::istream input(&buf);
    std::string response;

    std::getline(input, response);

    return response;
}

void SyncTCPClient::connect()
{
    m_sock.connect(m_ep);
}

void SyncTCPClient::close()
{
    m_sock.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    m_sock.close();
}

std::string SyncTCPClient::emulationLongComputationOp(unsigned int duration_sec)
{
    const std::string request = "EMULATION_LONG_COMP_OP" + std::to_string(duration_sec);

    sendRequest(request);
    return receiveResponse();
}

