#include "tcpconnection.h"

TCPConnection::TCPConnection()
{
    addr.port = 3499;
    addr.a = 10;
    addr.b = 34;
    addr.c = 99;
    addr.d = 5;

    runnableState = true;

    ad.sin_family = AF_INET;
    ad.sin_len = (u_char) sizeof(sockaddr_in);
    ad.sin_port = htons (addr.port);
    ad.sin_addr.s_addr = htonl (addr.addr);

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == ERROR) {
        ;;// hur dur... da... itsa... problem...
        runnableState = false;

        // Schedule a retry
        return;
    }


    int optval = 1;  // Turn on no delay
    setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, &optval, sizeof(optval));

    // Set to non-blocking
    if(!setNonBlocking(true)){
        // Output FAILED setting noblocking
        runnableState = false;
    }

    // Bind to the socket
    if(bind(sock, ad, sizeof(sockaddr_in)) == ERROR){
        // Schedule for retry. again.
    }

    // We only need to hear for a max of 5 incoming connections.
    // This sets the socket to accpet incoming connections (with max 5)
    listen(sock, 5);

    //int send(descriptor, const char *buf, buflen, int flags);

    //int recv(descriptor, char *buf, buflen, flags);

    // Schedule a function to accept incoming connections

    // Schedule a listen/send event
}

TCPConnection::~TCPConnection(){
    close(sock);
}


// Scheduled accepter
bool TCPConnection::connect(){
    // This IS blocking! need to fix!
    sockaddr_in *addr;
    int *addrlen;
    int descriptor = accept(sock, addr, addrlen);
}

bool setNonBlocking(bool noBlockEh){
    int flags;

    if (noBlockEh){ /* Set socket to non-blocking */
        if ((flags = fcntl(sock_descriptor, F_GETFL, 0)) < 0) return false;
        if (fcntl(socket_descriptor, F_SETFL, flags | O_NONBLOCK) < 0) return false;
    } else {        /* Set socket to blocking */
        if ((flags = fcntl(sock_descriptor, F_GETFL, 0)) < 0) return false;
        if (fcntl(socket_descriptor, F_SETFL, flags & (~O_NONBLOCK)) < 0) return false;
    }
}
