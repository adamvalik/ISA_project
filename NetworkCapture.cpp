/**
 * @file NetworkCapture.cpp
 * @brief NetworkCapture class implementation
 * 
 * @author Adam Valík <xvalik05@vutbr.cz>
 * 
*/

#include "NetworkCapture.hpp"

void NetworkCapture::prepareHandle() {
    char errbuf[PCAP_ERRBUF_SIZE];
    string error;

    // find the network number and mask for the network interface 
    bpf_u_int32 net, mask;
    if (pcap_lookupnet(interface.c_str(), &net, &mask, errbuf) == PCAP_ERROR) {
        throw NetworkException(1, "pcap_lookupnet() failed: " + string(errbuf));
    }

    // open interface in promiscuous mode (1) with 1s timeout
    handle = pcap_open_live(interface.c_str(), BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        throw NetworkException(1, "pcap_open_live() failed: " + string(errbuf));
    }

    // support only LINKTYPE_ETHERNET (corresponding to DLT_EN10MB) -> https://www.tcpdump.org/linktypes.html
    if (pcap_datalink(handle) != DLT_EN10MB && pcap_datalink(handle) != DLT_NULL){
        pcap_close(handle);
        throw NetworkException(1, "Unsupported link-layer header type");
    }

    // filter expression
    char filter[] = "ip or ip6";

    // compile the filter expression 
    struct bpf_program fp;
    if (pcap_compile(handle, &fp, filter, 0, net) == PCAP_ERROR) {
        error = pcap_geterr(handle);
        pcap_close(handle);
        throw NetworkException(1, "pcap_compile() failed: " + error);
    }

    // set the filter
    if (pcap_setfilter(handle, &fp) == PCAP_ERROR) {
        error = pcap_geterr(handle);
        pcap_close(handle);
        throw NetworkException(1, "pcap_setfilter() failed: " + error);
    }   
}

void NetworkCapture::startCapture() {
    // process packets from a live capture
    if (pcap_loop(handle, 0, NetworkCapture::processPacket, NULL) < 0) {
        string error = pcap_geterr(handle);
        pcap_close(handle);
        throw NetworkException(1, "pcap_loop() failed: " + error);
    }
}

void NetworkCapture::stopCapture() {
    if (handle != NULL) {
        pcap_breakloop(handle);
        pcap_close(handle);
    }
}

void NetworkCapture::processPacket(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {

}