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
 * @brief Class representing one connection 
 */
class Connection {
    string src; // src IP:port
    string dst; // dst IP:port
    string protocol; // protocol (tcp/udp/icmp)

    uint64_t bytesSent;
    uint64_t bytesReceived;
    uint64_t packetsSent;
    uint64_t packetsReceived;

    public:
        Connection() : bytesSent(0), bytesReceived(0), packetsSent(0), packetsReceived(0) {};

        /**
         * @brief Set connection parameters
         * 
         * @param src Source IP address and source port
         * @param dst Destination IP address and destination port
         * @param protocol Protocol
         */
        void set(const string& src, const string& dst, const string& protocol);

        /**
         * @brief Update transfer statistics
         * 
         * @param bytes Number of bytes
         * @param sent True if the bytes were sent, false if they were received
         */
        void updateTransfer(uint64_t bytes, bool sent); 

        /**
         * @brief Get source IP address and source port
         * 
         * @return string Source IP address and source port
         */
        string getSrc() { return this->src; };

        /**
         * @brief Get destination IP address and destination port
         * 
         * @return string Destination IP address and destination port
         */
        string getDst() { return this->dst; };

        /**
         * @brief Get protocol
         * 
         * @return string Protocol
         */
        string getProtocol() { return this->protocol; };

        /**
         * @brief Get number of received bytes
         * 
         * @return uint64_t Number of received bytes
         */
        uint64_t getRxBytes() { return this->bytesReceived; };

        /**
         * @brief Get number of sent bytes
         * 
         * @return uint64_t Number of sent bytes
         */
        uint64_t getTxBytes() { return this->bytesSent; };

        /**
         * @brief Get number of received packets
         * 
         * @return uint64_t Number of received packets
         */
        uint64_t getRxPackets() { return this->packetsReceived; };

        /**
         * @brief Get number of sent packets
         * 
         * @return uint64_t Number of sent packets
         */
        uint64_t getTxPackets() { return this->packetsSent; };

        /**
         * @brief Get total number of bytes sent and received
         * 
         * @return uint64_t Total number of bytes
         */
        uint64_t getBytes() { return this->bytesSent + this->bytesReceived; };

        /**
         * @brief Get total number of packets sent and received
         * 
         * @return uint64_t Total number of packets
         */
        uint64_t getPackets() { return this->packetsSent + this->packetsReceived; };
};

#endif // CONNECTION_HPP
