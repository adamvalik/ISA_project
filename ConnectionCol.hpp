/**
 * @file ConnectionCol.hpp
 * @brief ConnectionCol class header
 * 
 * @author Adam Valík <xvalik05@vutbr.cz>
 * 
*/

#ifndef CONNECTIONCOL_HPP
#define CONNECTIONCOL_HPP

#include "Connection.hpp"

#include <map>
#include <tuple>

using namespace std;

/**
 * @class ConnectionCol
 * @brief Collection of connections 
 */
class ConnectionCol {

    // map of connections - key is tuple of srcIP:port, dstIP:port and protocol
    map<tuple<string, string, string>, Connection> connections; 
    char sortOpt;

    public:
        ConnectionCol() : sortOpt('b') {};

        /**
         * @brief Update connection table
         * 
         * @param srcIp Source IP address
         * @param srcPort Source port
         * @param dstIp Destination IP address
         * @param dstPort Destination port
         * @param protocol Protocol
         * @param bytes Number of bytes
         */
        void updateTable(const string& srcIp, int srcPort, const string& dstIp, int dstPort, const string& protocol, uint64_t bytes);

        /**
         * @brief Get top 10 connections sorted by bytes or packets (sortOpt)
         * 
         * @return vector<Connection> Vector of connections to print out
         */
        vector<Connection> getConnections();

        /**
         * @brief Erase all connections from the table
         */
        void eraseTable() { this->connections.clear(); };

        /**
         * @brief Set sorting option
         * 
         * @param sortOpt Sorting option ('b' for bytes, 'p' for packets)
         */
        void setSortOpt(char sortOpt) { this->sortOpt = sortOpt; };
};

#endif // CONNECTIONCOL_HPP
