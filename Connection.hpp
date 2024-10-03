/**
 * @file Connection.hpp
 * @brief Connection class header
 * 
 * @author Adam Valík <xvalik05@vutbr.cz>
 * 
*/

#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <string>

using namespace std;

/**
 * @class Connection
 * @brief Connection class 
 */
class Connection {
    string src;
    string dst;
    string protocol;

    uint64_t bytesSent;
    uint64_t bytesReceived;
    uint64_t packetsSent;
    uint64_t packetsReceived;

    public:
        Connection() : bytesSent(0), bytesReceived(0), packetsSent(0), packetsReceived(0) {};
        void set(const string& src, const string& dst, const string& protocol);
        void updateTransfer(uint64_t bytes, bool sent); 

        string getSrc() { return this->src; };
        string getDst() { return this->dst; };
        string getProtocol() { return this->protocol; };
        uint64_t getRxBytes() { return this->bytesReceived; };
        uint64_t getTxBytes() { return this->bytesSent; };
        uint64_t getRxPackets() { return this->packetsReceived; };
        uint64_t getTxPackets() { return this->packetsSent; };
        uint64_t getBytes() { return this->bytesSent + this->bytesReceived; };
        uint64_t getPackets() { return this->packetsSent + this->packetsReceived; };
       

};

#endif // CONNECTION_HPP
