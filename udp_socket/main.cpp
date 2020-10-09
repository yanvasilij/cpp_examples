#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFSIZE 1024

int main( )
{
    std::cout << "Socket creation" << std::endl;
    auto socketh = socket (AF_INET, SOCK_DGRAM, 0);
    if (socketh < 0)
    {
        perror("Socket creation error : ");
        return -1;
    }

    /* setsockopt: Handy debugging trick that lets
     * us rerun the server immediately after we kill it;
     * otherwise we have to wait about 20 secs.
     * Eliminates "ERROR on binding: Address already in use" error.
     */
    auto optval = 1;
    setsockopt(socketh, SOL_SOCKET, SO_REUSEADDR,
               (const void *)&optval , sizeof(int));

    /* build the server's Internet address */
    struct sockaddr_in serveraddr{}; /* server's addr */
    in_port_t portno{6670};

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons((unsigned short)portno);

    /* bind: associate the parent socket with a port */
    if (bind(socketh, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0)
    {
        perror("ERROR on binding : ");
        return -1;
    }

    /* main loop: wait for a datagram, then echo it */
    struct sockaddr_in clientaddr; /* client addr */
    auto clientlen = sizeof(clientaddr);

    while (1)
    {
        char buf[BUFSIZE] {}; /* message buf */
        /* recvfrom: receive a UDP datagram from a client */
        auto n = recvfrom(socketh, buf, BUFSIZE, 0, (struct sockaddr *) &clientaddr, &clientlen);
        if (n < 0)
        {
            perror("ERROR in recvfrom : ");
            return -1;
        }

        std::cout << "I got something" << std::endl;



        /* gethostbyaddr: determine who sent the datagram */
//        auto hostp = gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr,
//                             sizeof(clientaddr.sin_addr.s_addr), AF_INET);
//       if (hostp == NULL)
//           error("ERROR on gethostbyaddr");
//       hostaddrp = inet_ntoa(clientaddr.sin_addr);
//       if (hostaddrp == NULL)
//           error("ERROR on inet_ntoa\n");
//       printf("server received datagram from %s (%s)\n",
//              hostp->h_name, hostaddrp);
//       printf("server received %d/%d bytes: %s\n", strlen(buf), n, buf);

        /*
         * sendto: echo the input back to the client
         */
        n = sendto(socketh, buf, strlen(buf), 0, (struct sockaddr *) &clientaddr, clientlen);
        if (n < 0)
        {
            perror("ERROR in sendto");
            return -1;
        }
    }

    return 0;
}
