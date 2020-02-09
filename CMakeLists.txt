cmake_minimum_required(VERSION 3.14)
project(BoostNetworkingCookbook)

FIND_PACKAGE( Boost 1.65.1 COMPONENTS program_options system REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

add_executable(BoostNetworkingCookbook main.cpp UDP/Client/Synchronous/SyncUDPClient.cpp UDP/Client/Synchronous/SyncUDPClient.h TCP/Client/Asynchronous/Definitions.h TCP/Client/Asynchronous/Session.cpp TCP/Client/Asynchronous/Session.h TCP/Client/Asynchronous/AsyncTCPClient.cpp TCP/Client/Asynchronous/AsyncTCPClient.h)

TARGET_LINK_LIBRARIES( BoostNetworkingCookbook LINK_PUBLIC ${Boost_LIBRARIES} )