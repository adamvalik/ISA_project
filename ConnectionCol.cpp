/**
 * @file ConnectionCol.cpp
 * @brief ConnectionCol class implementation
 * 
 * @author Adam Valík <xvalik05@vutbr.cz>
 * 
*/

#include "ConnectionCol.hpp"

void ConnectionCol::updateTable(const string& srcIp, int srcPort, const string& dstIp, int dstPort, const string& protocol, uint64_t bytes) {
    string src = (srcPort == -1) ? srcIp : srcIp + ":" + to_string(srcPort);
    string dst = (dstPort == -1) ? dstIp : dstIp + ":" + to_string(dstPort);
    // identify the connection by the tuple of srcIP:port, dstIP:port and protocol
    using Key = tuple<string, string, string>;
    Key key = make_tuple(src, dst, protocol);
    Key keyRev = make_tuple(dst, src, protocol);
    bool sent = true;
    // check if the connection already exists, if not create a new one and update transfer statistics
    if (connections.find(key) == connections.end() && connections.find(keyRev) == connections.end()) {
        // new connection
        connections[key].set(src, dst, protocol);
        connections[key].updateTransfer(bytes, true);
        // created and updated so return
        return; 
    } else if (connections.find(key) == connections.end()) {
        // connection already exists, but in reverse direction
        key = keyRev;
        sent = false;
    }
    // update existing connection
    connections[key].updateTransfer(bytes, sent);
}

vector<Connection> ConnectionCol::getConnections() {
    // return top 10 sorted connections (based on the sortOpt and total sent+received)
    vector<Connection> sortedConnections;
    for (auto& connection : connections) {
        sortedConnections.push_back(connection.second);
    }
    if (sortOpt == 'b') {
        sort(sortedConnections.begin(), sortedConnections.end(), [](Connection& a, Connection& b) {
            return a.getBytes() > b.getBytes();
        });
    } else if (sortOpt == 'p') {
        sort(sortedConnections.begin(), sortedConnections.end(), [](Connection& a, Connection& b) {
            return a.getPackets() > b.getPackets();
        });
    }
    if (sortedConnections.size() > 10) {
        sortedConnections.resize(10);
    }
    return sortedConnections;
}