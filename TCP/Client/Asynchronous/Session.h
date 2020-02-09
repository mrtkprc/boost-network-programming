#pragma once

#include <string>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/streambuf.hpp>
#include "Definitions.h"

using  namespace boost;
using  namespace std;

struct Session {

    asio::ip::tcp::socket m_sock;
    asio::ip::tcp::endpoint m_ep;
    std::string m_request;
    boost::asio::streambuf m_response_buf;
    std::string m_response;
    system::error_code m_ec;
    unsigned int m_id;
    Callback m_callback;
    bool m_was_cancelled;
    std::mutex m_cancel_guard;

    Session(asio::io_service &ios,
            const std::string &raw_ip_addrs,
            unsigned short port_num,
            const std::string &request,
            unsigned int id,
            Callback callback);

};

typedef std::shared_ptr<Session> SessionPtr;