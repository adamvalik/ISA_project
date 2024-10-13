/**
 * @file NetworkInterface.hpp
 * @brief Network interface class header
 * 
 * @author Adam Valík <xvalik05@vutbr.cz>
 * 
*/

#ifndef NETWORKINTERFACE_HPP
#define NETWORKINTERFACE_HPP

#include "NetworkException.hpp"
#include "Controller.hpp"
#include "globals.hpp"

#include <pcap/pcap.h>
#include <iostream>
#include <ncurses.h>

using namespace std;

/**
 * @class NetworkInterface
 * @brief Abstract class for network interfaces
 */
class NetworkInterface {

    public:
        /**
         * @brief List all active interfaces
         * @throws NetworkException
         * @see https://www.tcpdump.org/manpages/pcap_findalldevs.3pcap.html
         */
        static void listInterfaces();

        /**
         * @brief Validate interface
         * @param interface Interface name
         * @throws NetworkException
         * @return bool True if the interface is valid
         */
        static bool validateInterface(const string& interface);
};

#endif // NETWORKINTERFACE_HPP
