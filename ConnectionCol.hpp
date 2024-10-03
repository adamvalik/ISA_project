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
 * @brief ConnectionCol class 
 */
class ConnectionCol {

    map<tuple<string, string, string>, Connection> connections; 
    char sortOpt;

    public:
        ConnectionCol() : sortOpt('b') {};
        void updateTable(const string& srcIp, int srcPort, const string& dstIp, int dstPort, const string& protocol, uint64_t bytes);
        vector<Connection> getConnections();
        void eraseTable() { this->connections.clear(); };
        void setSortOpt(char sortOpt) { this->sortOpt = sortOpt; };
};

#endif // CONNECTIONCOL_HPP
