/**
 * @file NetworkCapture.hpp
 * @brief NetworkCapture class header
 * 
 * @author Adam Valík <xvalik05@vutbr.cz>
 * 
*/

#ifndef NETWORKCAPTURE_HPP
#define NETWORKCAPTURE_HPP

#include "NetworkException.hpp"
#include "ConnectionCol.hpp"
#include "globals.hpp"

#include <string>
#include <pcap/pcap.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <netinet/ip.h> 
#include <netinet/ip6.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>
#include <netinet/ip_icmp.h>
#include <netinet/icmp6.h>
#include <netinet/igmp.h>

using namespace std;

/**
 * @class NetworkCapture
 * @brief NetworkCapture class 
 */
class NetworkCapture {

    string interface;
    pcap_t *handle;
    ConnectionCol& connectionCol;

    public:
        NetworkCapture(ConnectionCol& connectionCol) : handle(nullptr), connectionCol(connectionCol) {};

        void setInterface(const string& interface) {
            this->interface = interface;
        };

        pcap_t* getHandle() {
            return this->handle;
        };

        /**
         * @brief 
         */
        void startCapture();
        void prepareHandle();

        static void processPacket(u_char *user, const struct pcap_pkthdr *header, const u_char *bytes);
};

#endif //NETWORKCAPTURE_HPP
