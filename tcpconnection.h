#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <types.h>
#include <net/mbuf.h>
//#include <mbuf.h>
#include <socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <net/socketvar.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <netdb.h>
#include <iostream>
#include <stdlib.h>


#include <socket.h>
#include <sockLib.h>
#include <stdlib.h>
#include <sysLib.h>
#include <logLib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h> /*<winsock.h>*/
#include <stdio.h>
#include <string.h>
#include <ioLib.h>
#include <ioctl.h>
#include <netLib.h>

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

    // queue
};


#endif // TCPCONNECTION_H
