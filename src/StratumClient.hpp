//
//  StratumClient.cpp
//  stratum client
//
//  Created by labdsv on 7/10/17.
//  Copyright © 2017 landsv. All rights reserved.
//

#include <stdio.h>
#include <boost/asio.hpp>
#include "Work.hpp"

using namespace std;
using namespace boost::asio;
using boost::asio::ip::tcp;

struct StratumServer {
    string host;
    string port;
};

class StratumClient {
    
public:
    StratumClient(StratumServer server_info);
    ~StratumClient();
    
    /// Connect to stratum server.
    void connect();
    
    /// Reconnect to stratum server.
    void reconnect();
    
    /// Disconnect from stratum server.
    void disconnect();
    
    /// Returns `true` if connection is established, otherwise - `false`.
    bool is_connected() { return _is_connected; }
    
    /// Returns `true` if a solution is successfully submitted, otherwise - `false`.
    bool submit(Work work);
    
private:
    
    StratumServer _server_info;
    
    boost::asio::io_service io_service;
    tcp::socket socket;
    
    bool _is_connected;
    
    void connect(tcp::resolver::iterator endpoint_iterator,
                 boost::system::error_code error);
    void handle_connect(const boost::system::error_code& error,
                        tcp::resolver::iterator endpoint_iterator);
    void connection_established();
    
};
