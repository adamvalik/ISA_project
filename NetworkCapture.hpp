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

        /**
         * @brief Set interface
         * 
         * @param interface Interface name
         */
        void setInterface(const string& interface) {
            this->interface = interface;
        };

        /**
         * @brief Get handle 
         * 
         * @return pcap_t* handle
         */
        pcap_t* getHandle() {
            return this->handle;
        };

        /**
         * @brief Prepare handle for capturing network traffic (open interface, set filter)
         * @see https://www.tcpdump.org/manpages/pcap_open_live.3pcap.html
         */
        void prepareHandle();

        /**
         * @brief Start capturing network traffic (pcap_loop)
         * @see https://www.tcpdump.org/manpages/pcap_loop.3pcap.html
         */
        void startCapture();

        /**
         * @brief Process packet
         * 
         * @param user User data
         * @param header Packet header
         * @param bytes Packet data
         */
        static void processPacket(u_char *user, const struct pcap_pkthdr *header, const u_char *bytes);
};

#endif //NETWORKCAPTURE_HPP
