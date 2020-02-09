#pragma once

#include <thread>
#include <mutex>
#include <memory>
#include <iostream>
#include <boost/system/error_code.hpp>

using namespace std;

typedef void(*Callback)(unsigned int request_id, const std::string &response, const error_code& ec);