//
// Created by mert on 09.02.2020.
//

#include "AsyncTCPClient.h"
#include <boost/asio/write.hpp>
#include <boost/asio/read_until.hpp>

AsyncTCPClient::AsyncTCPClient() {
    m_work.reset( new boost::asio::io_service::work(m_ios));

    m_thread.reset(new std::thread([this](){
        m_ios.run();
    }));
}

void AsyncTCPClient::emulateLongComputationOp(unsigned int duration_sec, const std::string &raw_ip_address,
                                              unsigned short port_num, Callback callback, unsigned int request_id) {

    std::string request = "EMULATE_LONG_CALC_OP" + std::to_string(duration_sec)+"\n";
    SessionPtr session = make_shared<Session>(m_ios, raw_ip_address, port_num, request, request_id, callback);

    session->m_sock.open(session->m_ep.protocol());

    std::unique_lock<std::mutex> lock(m_active_sessions_guard);

    m_active_sessions[request_id] = session;

    lock.unlock();

    session->m_sock.async_connect(session->m_ep, [this, session](const system::error_code& ec){
        if(0 != ec)
        {
            session->m_ec = ec;
            onRequestComplete(session);
        }

        std::unique_lock<std::mutex> cancel_lock(session->m_cancel_guard);

        if(session->m_was_cancelled)
        {
            onRequestComplete(session);
            return;
        }

        boost::asio::async_write(session->m_sock, asio::buffer(session->m_request), [this, session](const boost::system::error_code& ec, std::size_t byte_transferred){
            if(0 != ec)
            {
                session->m_ec = ec;
                onRequestComplete(session);
                return;
            }

            std::unique_lock<std::mutex> cancel_lock(session->m_cancel_guard);

            if(session->m_was_cancelled)
            {
                onRequestComplete(session);
                return;
            }

            boost::asio::async_read_until(session->m_sock, session->m_response_buf, '\n',[this, session](const boost::system::error_code& ec, std::size_t bytes_transferred){
                if(0 != ec){
                    session->m_ec = ec;
                } else{
                    std::istream strm(&session->m_response_buf);
                    std::getline(strm, session->m_response);
                }
                onRequestComplete(session);
            });
        });
    });

}

void AsyncTCPClient::cancelRequest(unsigned int request_id) {
    std::unique_lock<std::mutex> lock(m_active_sessions_guard);
    auto it = m_active_sessions.find(request_id);
    if(it != m_active_sessions.end())
    {
        std::unique_lock<std::mutex> cancel_lock(it->second->m_cancel_guard);
        it->second->m_was_cancelled = true;
        it->second->m_sock.cancel();
    }
}
