//
//  StratumClient.cpp
//  stratum client
//
//  Created by labdsv on 7/12/17.
//  Copyright © 2017 landsv. All rights reserved.
//

#include <stdio.h>
#include "StratumClient.hpp"

using boost::asio::ip::tcp;

StratumClient::StratumClient(StratumServer server_info)
    : socket(io_service)
{
    _server_info = server_info;
}

StratumClient::~StratumClient()
{
    // dealloc
}


void StratumClient::connect()
{
    tcp::resolver r(io_service);
    tcp::resolver::query q(_server_info.host, _server_info.port);
    tcp::resolver::iterator endpoint_iterator = r.resolve(q);
    tcp::resolver::iterator end;
    
    boost::system::error_code netdb_error = boost::asio::error::host_not_found;
    
    while (netdb_error && endpoint_iterator != end) {
        socket.connect(*endpoint_iterator++,
                       netdb_error);
    }
    
    if (netdb_error) {
        // try to reconect
    }
    else {
        connection_established();
    }
    
    _is_connected = true;
}

void StratumClient::connection_established()
{
}

void StratumClient::disconnect()
{
    _is_connected = false;
    socket.close();
    io_service.stop();
}
