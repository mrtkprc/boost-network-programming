cmake_minimum_required(VERSION 3.14)
project(BoostNetworkingCookbook)

FIND_PACKAGE( Boost 1.65.1 COMPONENTS program_options system REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

add_executable(BoostNetworkingCookbook main.cpp TCP/Client/Synchronous/SyncTCPClient.cpp TCP/Client/Synchronous/SyncTCPClient.h)

TARGET_LINK_LIBRARIES( BoostNetworkingCookbook LINK_PUBLIC ${Boost_LIBRARIES} )