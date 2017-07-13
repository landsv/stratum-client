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
    
    boost::system::error_code error = boost::asio::error::host_not_found;
    
    handle_connect(error, endpoint_iterator);
}

void StratumClient::connect(tcp::resolver::iterator endpoint_iterator,
                            boost::system::error_code error)
{
    _is_connected = false;
    socket.close();
    socket.connect(*endpoint_iterator++,
                   error);
}

void StratumClient::handle_connect(const boost::system::error_code& error,
                                  tcp::resolver::iterator endpoint_iterator)
{
    tcp::resolver::iterator end;
    
    if (!error) {
        connection_established();
    }
    else if (endpoint_iterator != end) {
        connect(endpoint_iterator, error);
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
