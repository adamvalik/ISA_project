/**
 * @file Connection.cpp
 * @brief Connection class implementation
 * 
 * @author Adam Valík <xvalik05@vutbr.cz>
 * 
*/

#include "Connection.hpp"

void Connection::set(const string& src, const string& dst, const string& protocol) {
    this->src = src;
    this->dst = dst;
    this->protocol = protocol;
}

void Connection::updateTransfer(uint64_t bytes, bool sent) {
    if (sent) {
        this->bytesSent += bytes;
        this->packetsSent += 1;
    } else {
        this->bytesReceived += bytes;
        this->packetsReceived += 1;
    }
}


