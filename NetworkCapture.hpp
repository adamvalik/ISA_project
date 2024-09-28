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


#include <string>
#include <pcap/pcap.h>

using namespace std;

/**
 * @class NetworkCapture
 * @brief NetworkCapture class 
 */
class NetworkCapture {

    string interface;
    pcap_t *handle;

    public:
        NetworkCapture() : handle(nullptr) {};

        /**
         * @brief 
         */
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
        void stopCapture();

        static void processPacket(u_char *args, const struct pcap_pkthdr *header, const u_char *packet);
};

#endif //NETWORKCAPTURE_HPP
