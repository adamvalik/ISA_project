# trafficGen.py
# generating specified traffic for isa-top testing purposes
# the filter has to be set (in NetworkCapture.cpp) to isolate the custom-generated traffic on the interface
# autor: Adam Valík <xvalik05@vutbr.cz>

from scapy.all import sendp, Ether, IP, IPv6, UDP, TCP, Raw
import time

def generate_traffic(interface, ip_version, proto, src_ip, src_port, dst_ip, dst_port, num_of_packets, num_of_payload_bytes):
    """Generate traffic with the specified parameters."""

    # create Ethernet frame
    pkt = Ether()

    # append IP header
    if ip_version == 4:
        pkt /= IP(src=src_ip, dst=dst_ip)
    elif ip_version == 6:
        pkt /= IPv6(src=src_ip, dst=dst_ip)

    # append transport layer header
    if proto == "TCP":
        pkt /= TCP(sport=src_port, dport=dst_port)
    elif proto == "UDP":
        pkt /= UDP(sport=src_port, dport=dst_port)
    
    # append payload (if any)
    if num_of_payload_bytes > 0:
        payload_data = b"X" * num_of_payload_bytes
        pkt /= Raw(load=payload_data)
    
    # send num_of_packets packets on the interface
    sendp(pkt, iface=interface, count=num_of_packets)


if __name__ == "__main__":
    generate_traffic("en0", 4, "UDP", "1.1.1.1", 1, "2.2.2.2", 2, 4000, 100)
    generate_traffic("en0", 4, "UDP", "2.2.2.2", 2, "1.1.1.1", 1, 3000, 100)
    generate_traffic("en0", 4, "TCP", "2.2.2.2", 2, "1.1.1.1", 1, 2000, 100)
    generate_traffic("en0", 4, "TCP", "1.1.1.1", 1, "2.2.2.2", 2, 1000, 100)
    



