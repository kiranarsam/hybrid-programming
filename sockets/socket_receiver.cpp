#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/if_packet.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/if_ether.h>
#include <linux/if.h>

int main() {
    int sockfd;
    struct sockaddr_ll addr;
    struct ifreq req;
    int res = -1;

    // Create a socket with AF_PACKET family and SOCK_DGRAM type
    sockfd = socket(AF_PACKET, SOCK_DGRAM, htons(ETH_P_ALL));
    if (sockfd < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    snprintf(req.ifr_name, sizeof(req.ifr_name), "%s", "lo");
    res = ioctl(sockfd, SIOCGIFINDEX, &req);
    if (res < 0) {
        perror("Failed to get interface index");
        return -1;
    }

    // Set up the loopback interface address
    addr.sll_family = AF_PACKET;
    addr.sll_ifindex = req.ifr_ifindex; // Use the loopback interface
    addr.sll_halen = 6;
    addr.sll_protocol = htons(ETH_P_ALL);

    // Bind the socket to the loopback interface
    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        std::cerr << "Error binding socket" << std::endl;
        return 1;
    }

    // Receive an IEEE 1722 packet
    uint8_t recv_buf[1024];
    recvfrom(sockfd, recv_buf, 1024, 0, NULL, NULL);

    // Print the received packet
    std::cout << "Received packet: ";
    for (int i = 0; i < 8; i++) {
        std::cout << std::hex << (int)recv_buf[i] << " ";
    }
    std::cout << std::endl;

    close(sockfd);
    return 0;
}