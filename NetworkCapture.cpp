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
    this->handle = pcap_open_live(interface.c_str(), BUFSIZ, 1, 1000, errbuf);
    if (this->handle == NULL) {
        throw NetworkException(1, "pcap_open_live() failed: " + string(errbuf));
    }

    // support only LINKTYPE_ETHERNET (corresponding to DLT_EN10MB) -> https://www.tcpdump.org/linktypes.html
    if (pcap_datalink(this->handle) != DLT_EN10MB && pcap_datalink(this->handle) != DLT_NULL){
        pcap_close(this->handle);
        throw NetworkException(1, "Unsupported link-layer header type");
    }

    // filter expression
    const char *filter = "ip or ip6";

    // filter expression for testing purposes
    // const char *filter = "host 1.1.1.1";


    // compile the filter expression 
    struct bpf_program fp;
    if (pcap_compile(this->handle, &fp, filter, 0, net) == PCAP_ERROR) {
        error = pcap_geterr(this->handle);
        pcap_close(this->handle);
        throw NetworkException(1, "pcap_compile() failed: " + error);
    }

    // set the filter
    if (pcap_setfilter(this->handle, &fp) == PCAP_ERROR) {
        error = pcap_geterr(this->handle);
        pcap_close(this->handle);
        throw NetworkException(1, "pcap_setfilter() failed: " + error);
    }
}

void NetworkCapture::startCapture() {
    // process packets from a live capture
    int ret = pcap_loop(this->handle, -1, NetworkCapture::processPacket, reinterpret_cast<u_char*>(&this->connectionCol));
    if (ret == PCAP_ERROR) {
        string error = pcap_geterr(this->handle);
        threadException = make_exception_ptr(NetworkException(1, "pcap_loop() failed: " + error));
    }
    pcap_close(this->handle);
}


void NetworkCapture::processPacket(u_char *user, const struct pcap_pkthdr *header, const u_char *bytes) {
    const struct ether_header *eth_header = (const struct ether_header *)bytes;
    uint8_t protocol = 0;
    int offset = sizeof(struct ether_header);

    string srcIp, dstIp, protocolName;
    int srcPort = -1, dstPort = -1;
    int len = 0;

    if (ntohs(eth_header->ether_type) == ETHERTYPE_IP) {
        // IPv4
        const struct ip *ip_header = (const struct ip *)(bytes + offset);
        // convert from binary to text using inet_ntoa()
        srcIp = inet_ntoa(ip_header->ip_src);
        dstIp = inet_ntoa(ip_header->ip_dst);
        len = ntohs(ip_header->ip_len);

        protocol = ip_header->ip_p;
        offset += ip_header->ip_hl * 4; // IPv4 header length is variable 20-60 bytes
    }
    else if (ntohs(eth_header->ether_type) == ETHERTYPE_IPV6) {
        // IPv6
        const struct ip6_hdr *ip6_header = (const struct ip6_hdr *)(bytes + offset);
        char ip6_src[INET6_ADDRSTRLEN];
        char ip6_dst[INET6_ADDRSTRLEN];
        // convert from binary to text using inet_ntop()
        inet_ntop(AF_INET6, &ip6_header->ip6_src, ip6_src, INET6_ADDRSTRLEN);
        inet_ntop(AF_INET6, &ip6_header->ip6_dst, ip6_dst, INET6_ADDRSTRLEN);
        srcIp = ip6_src;
        dstIp = ip6_dst;
        len = ntohs(ip6_header->ip6_plen);

        protocol = ip6_header->ip6_ctlun.ip6_un1.ip6_un1_nxt;
        offset += sizeof(struct ip6_hdr); // IPv6 header is always 40 bytes
    }
    else {
        // unsupported protocol
        srcIp = "unknown";
        dstIp = "unknown";
    }

    if (protocol == IPPROTO_TCP) {
        // TCP
        const struct tcphdr *tcp_header = (const struct tcphdr *)(bytes + offset);
        srcPort = ntohs(tcp_header->th_sport);
        dstPort = ntohs(tcp_header->th_dport);
        protocolName = "tcp";
    }
    else if (protocol == IPPROTO_UDP) {
        // UDP
        const struct udphdr *udp_header = (const struct udphdr *)(bytes + offset);
        srcPort = ntohs(udp_header->uh_sport);
        dstPort = ntohs(udp_header->uh_dport);
        protocolName = "udp";
    }
    else if (protocol == IPPROTO_ICMP) {
        // ICMP 
        protocolName = "icmp";
    }
    else if (protocol == IPPROTO_IGMP) {
        // IGMP
        protocolName = "igmp";
    }
    else if (protocol == IPPROTO_ICMPV6) {
        // ICMPv6
        protocolName = "icmp6";
    }
    else {
        // unsupported protocol
        protocolName = "unknown";
    }

    // update connection table
    ConnectionCol* connCol = reinterpret_cast<ConnectionCol*>(user);

    dataMutex.lock();
    connCol->updateTable(srcIp, srcPort, dstIp, dstPort, protocolName, len); // header-len
    dataMutex.unlock();
}