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
    tcp::resolver resolver(io_service);
    tcp::resolver::query query(_server_info.host, _server_info.port);
    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
    tcp::resolver::iterator end;
    
    boost::system::error_code error = boost::asio::error::host_not_found;
    
    while (error && endpoint_iterator != end) {
        socket.close();
        socket.connect(*endpoint_iterator++,
                       error);
    }
    
    if (error) {
        throw boost::system::system_error(error);
    }
    else {
        connection_established();
    }
}

void StratumClient::connection_established()
{
    _is_connected = true;
}

void StratumClient::reconnect()
{
    _is_connected = false;
    io_service.reset();
    disconnect();
}

void StratumClient::disconnect()
{
    _is_connected = false;
    socket.close();
    io_service.stop();
}
