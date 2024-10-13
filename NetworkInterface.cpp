/**
 * @file NetworkInterface.cpp
 * @brief Network interface class implementation
 * 
 * @author Adam Valík <xvalik05@vutbr.cz>
 * 
*/

#include "NetworkInterface.hpp"

void NetworkInterface::listInterfaces() {
    pcap_if_t *alldevsp;
    char errbuf[PCAP_ERRBUF_SIZE];

    // find all active interfaces
    if (pcap_findalldevs(&alldevsp, errbuf) == PCAP_ERROR) {
        throw NetworkException(1, "pcap_findalldevs() failed: " + string(errbuf));
    }

    // disable ncurses to print to stdout
    Controller::closeNcurses();

    // list all active interfaces
    cout << endl << "Active interfaces:" << endl;
    for (pcap_if_t* i = alldevsp; i; i = i->next) {
        cout << i->name << endl;
    }
    cout << endl;

    // free the device list
    pcap_freealldevs(alldevsp);
}

bool NetworkInterface::validateInterface(const string& interface) {
    pcap_if_t *alldevsp;
    char errbuf[PCAP_ERRBUF_SIZE];

    // find all active interfaces
    if (pcap_findalldevs(&alldevsp, errbuf) == PCAP_ERROR) {
        throw NetworkException(1, "pcap_findalldevs() failed: " + string(errbuf));
    }

    // find the specified interface in the list
    for (pcap_if_t* i = alldevsp; i; i = i->next) {
        if (i->name == interface) {
            pcap_freealldevs(alldevsp);
            return true;
        }
    }

    pcap_freealldevs(alldevsp);
    return false;
}