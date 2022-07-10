#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#include<errno.h>
#include<string.h>

static void *nmemset(void *src, int start, int count, char byte) {
    int i;
    char *tmp;

    tmp = (char *)src;
    
    for (i = 0; i < count; i++) {
        tmp[start+i] = byte;
    }

    src = (void *)tmp;
    return tmp;
}

static void *nmemcopy(void *src, int start, char *mac_address) {
    int i;
    char *tmp;

    tmp = (char *)src;

    for (i = 0; i < 6; i++) {
        tmp[start+i] = mac_address[i];
    }
    src = (void *)tmp;
    return src;
}

static char *construct_magic_packet(char *mac_address) {
    int i;
    char *magic_packet;

    magic_packet = (char *)malloc(102);
    magic_packet = (char *)nmemset(magic_packet, 0, 6, 0xff);
    
    for (i = 0; i < 16; i++) {
        magic_packet = (char *)nmemcopy(magic_packet, (i+1)*6, mac_address);
    }

    return magic_packet;
}

int main() {
    char tank_mac[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    char *packet;
    packet = construct_magic_packet(tank_mac);

    // create socket
    // (IPV4, UDP?, internet_protocol)
    int sock_fd;
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    printf("%d\n", sock_fd);

    // create socket structure
    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(40000);
    sin.sin_addr.s_addr = inet_addr("0.0.0.0");

    int check = sendto(sock_fd,
            packet,
            102,
            MSG_NOSIGNAL,
            (struct sockaddr *)&sin,
            sizeof(sin));

    if (check <= 0) {
        printf("Error %s\n", strerror(errno));
    }
    
    return 0;
}
