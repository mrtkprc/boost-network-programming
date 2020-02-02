#include <iostream>

#include "TCP/Client/Synchronous/SyncTCPClient.h"

using namespace std;

int main()
{

    const std::string raw_ip_address = "127.0.0.1";
    const unsigned short port_num = 3333;

    try
    {
        SyncTCPClient client(raw_ip_address, port_num);
        client.connect();

        cout << "Sending request to the server" << endl;

        string response = client.emulationLongComputationOp(5);

        cout << "Response received: "<< response << endl;

        client.close();

    }
    catch(system_error &e)
    {
        cout << "Error occurred: "<< e.what() << endl;
    }

    return 0;
}