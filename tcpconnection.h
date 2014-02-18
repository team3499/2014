#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <sockLib.h>

// If stuff needs to be included, try this list first
//#include <errno.h>#include <ioctl.h>#include <ioLib.h>#include <iostream>#include <logLib.h>#include <net/mbuf.h>#include <net/socketvar.h>#include <netdb.h>#include <netinet/in.h>#include <netinet/ip.h>#include <netLib.h>#include <socket.h>#include <stdio.h>#include <stdlib.h>#include <string.h>#include <sys/socket.h>#include <sys/types.h>#include <sysLib.h>#include <types.h>

class TCPConnection {
public:
    struct IPStruct {
        union {
            unsigned addr: 32;
            struct {
                unsigned a: 8;
                unsigned b: 8;
                unsigned c: 8;
                unsigned d: 8;
            };
        };
        unsigned short port;
    };

public:
    TCPConnection();
    ~TCPConnection();
    
    bool connect();
    bool setNonBlocking(bool noBlockEh);

    int send(char *str, int len);
    
private:
    IPStruct addr;
    sockaddr ad;

    int sock;
    int fd;

    bool runnableState;
};


#endif // TCPCONNECTION_H
