/* Code from Head First C.

Modified by Tim Camper.

Downloaded from https://github.com/twcamper/head-first-c/tree/master/11

Modified by Allen Downey.

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

char *advice[] = {
    "\nTake smaller bites.\r\n",
    "\nOne word: inappropriate\r\n",
    "\nI really couldn't advise you on such a matter!\r\n",
    "\nJust for today, be honest: tell the boss what you *really* think.\r\n",
    "\nYou might want to rethink that haircut.\r\n"
};


int main()
{
    // create the listening socket
    int listener_d = socket(PF_INET, SOCK_STREAM, 0);
    if (listener_d == -1)
        error("socket failed.");

    struct sockaddr_in name;
    name.sin_family = PF_INET;
    name.sin_port = (in_port_t)htons(30000);
    name.sin_addr.s_addr = htonl(INADDR_ANY);

    // set socket options
    int reuse = 1;
    int res = setsockopt(listener_d,
                   SOL_SOCKET,
                   SO_REUSEADDR,
                   (char *)&reuse,
                   sizeof(int));
    if (res == -1)
        error("Can't set the 'reuse' option on the socket.");

    // bind the socket to a port
    res = bind(listener_d,  (struct sockaddr *) &name, sizeof(name));
    if (res == -1)
        error("Can't bind the port");

    // Confusingly, `listen` just sets the socket to be
    // a listening socket (and sets the queue length).
    // It doesn't actually wait for connections (accept does that)
    res = listen(listener_d, 10);
    if (res == -1)
        error("listen failed.");


    while (1) {
        puts("waiting for a connection");

        // wait for a connection
        struct sockaddr_storage client_addr;
        unsigned int address_size = sizeof(client_addr);

        int connect_d = accept(listener_d,
                               (struct sockaddr *)&client_addr,
                               &address_size);

        // when accept returns, connect_d is a
        // new socket
        char *msg = advice[rand() % 5 ];
        res = send(connect_d, msg, strlen(msg), 0);
        if (res == -1)
            error("send failed.");

        close(connect_d);
    }

    return 0;
}
