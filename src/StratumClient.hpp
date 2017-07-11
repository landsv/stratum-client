//
//  Stratum_Client.hpp
//  dsv miner
//
//  Created by labdsv on 7/10/17.
//
//

#include <stdio.h>
#include <boost/asio.hpp>
#include "Worker.hpp"

using namespace std;
using namespace boost::asio;
using boost::asio::ip::tcp;

class StratumClient {
    
public:
    StratumClient();
    
    /// Connect to stratum server
    void connect();
    
    /// Reconnect to stratum server
    void reconnect();
    
    /// Disconnect from stratum server;
    void disconnect();
    
    /// Returns `true` if connection is established, otherwise - `false`
    bool is_connected();
    
private:
    
    boost::asio::io_service m_io_service;
    tcp::socket m_socket;
    
};
