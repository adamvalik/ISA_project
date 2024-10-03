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
    using Key = tuple<string, string, string>;
    Key key = make_tuple(src, dst, protocol);
    Key keyRev = make_tuple(dst, src, protocol);
    bool sent = true;
    if (connections.find(key) == connections.end() && connections.find(keyRev) == connections.end()) {
        connections[key].set(src, dst, protocol);
        connections[key].updateTransfer(bytes, true);
    } else if (connections.find(key) == connections.end()) {
        key = keyRev;
        sent = false;
    }
    connections[key].updateTransfer(bytes, sent);
    // printf("Connection %s -> %s: %llu bytes\n", src.c_str(), dst.c_str(), bytes);
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