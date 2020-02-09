#pragma once
#include <boost/asio/io_service.hpp>
#include "Session.h"

using namespace std;

class AsyncTCPClient {
private:
    boost::asio::io_service m_ios;
    std::map<int, SessionPtr> m_active_sessions;
    std::mutex m_active_sessions_guard;
    std::unique_ptr<boost::asio::io_service::work> m_work;
    std::unique_ptr<std::thread> m_thread;
public:
    AsyncTCPClient();
    void emulateLongComputationOp(unsigned int duration_sec, const std::string& raw_ip_address, unsigned short port_num, Callback callback, unsigned int request_id);
    void cancelRequest(unsigned int request_id);

    //continue from method close

};



