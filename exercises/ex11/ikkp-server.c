/* Code from Head First C.

Modified by Allen Downey.

*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

int listener_d = 0;

/* Print an error message and exit.
*/
void error(char *msg) {
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

/* Set up the signal catcher.
*/
int catch_signal(int sig, void (*handler)(int)) {
    struct sigaction action;
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    return sigaction(sig, &action, NULL);
}

/* Signal handler for SHUTDOWN
*/
void handle_shutdown(int sig) {
    if (listener_d)
        close(listener_d);

    fprintf(stderr, "Bye!\n");
    exit(EXIT_SUCCESS);
}

/* Create the listener socket.
*/
int open_listener_socket(void) {
    int s = socket(PF_INET, SOCK_STREAM, 0);
    if (s == -1)
    error("Can't open listener socket");
    return s;
}

/* Wait for clients to connect.
*/
int open_client_socket(void) {
    static struct sockaddr_storage client_address;
    static unsigned int address_size = sizeof(client_address);
    int s;

    if ((s = accept(listener_d, (struct sockaddr *)&client_address,
    &address_size)) == -1)
    error("Can't open client socket");

    return s;
}

/* Bind the socket to a port.
*/
void bind_to_port(int socket, int port) {
    struct sockaddr_in name;
    name.sin_family = PF_INET;
    name.sin_port = (in_port_t)htons(port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    int reuse = 1;

    int res = setsockopt(socket, SOL_SOCKET, SO_REUSEADDR,
                         (char *)&reuse, sizeof(int));
    if (res == -1)
        error("Can't set the 'reuse' option on the socket");

    res = bind(socket, (struct sockaddr *)&name, sizeof(name));
    if (res == -1)
        error("Can't bind to socket");
}

/* Send to the client.
*/
int say(int socket, char *s)
{
    int res = send(socket, s, strlen(s), 0);
    if (res == -1)
        error("Error talking to the client");
    return res;
}

/* Read from the client.

Returns: number of characters read.
*/
int read_in(int socket, char *buf, int len)
{
    /* treat the socket stream as a regular IO stream,
    so we can do character IO */
    FILE *fp = fdopen(socket, "r");
    int i = 0, ch;

    /* eat any leading whitespace */
    while (isspace(ch = fgetc(fp)) && ch != EOF) {
        // do nothing
    }

    if (ferror(fp))
        error("fgetc");

    while (ch != '\n' && ch != EOF) {
        if (i < len)
        buf[i++] = ch;
        ch = fgetc(fp);
    }
    if (ferror(fp))
        error("fgetc");

    /* terminate the string, eating any trailing whitespace */
    while (isspace(buf[--i])) {
        buf[i] = '\0';
    }

    return strlen(buf);
}

char intro_msg[] = "Internet Knock-Knock Protocol Server\nKnock, knock.\n";

int main(int argc, char *argv[])
{
    char buf[255];

    // set up the signal handler
    if (catch_signal(SIGINT, handle_shutdown) == -1)
        error("Setting interrupt handler");

    // create the listening socket
    int port = 30000;
    listener_d = open_listener_socket();
    bind_to_port(listener_d, port);

    if (listen(listener_d, 10) == -1)
        error("Can't listen");



    while (1) {
        printf("Waiting for connection on port %d\n", port);
        int connect_d = open_client_socket();

        if (say(connect_d, intro_msg) == -1) {
            close(connect_d);
            continue;
        }

        read_in(connect_d, buf, sizeof(buf));
        // TODO (optional): check to make sure they said "Who's there?"

        if (say(connect_d, "Surrealist giraffe.\n") == -1) {
            close(connect_d);
            continue;
        }

        read_in(connect_d, buf, sizeof(buf));
        // TODO (optional): check to make sure they said "Surrealist giraffe who?"

        if (say(connect_d, "Bathtub full of brightly-colored machine tools.\n") == -1) {
            close(connect_d);
            continue;
        }

        close(connect_d);
    }
    return 0;
}
