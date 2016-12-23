/* Code from Head First C.

 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

int listener_d = 0;

void error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

int catch_signal(int sig, void (*handler)(int))
{
  struct sigaction action;
  action.sa_handler = handler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;
  return sigaction(sig, &action, NULL);
}

void handle_shutdown(int sig)
{
    if (listener_d)
	close(listener_d);

    fprintf(stderr, "Bye!\n");
    exit(EXIT_SUCCESS);
}

int open_listener_socket(void)
{
    int s = socket(PF_INET, SOCK_STREAM, 0);
    if (s == -1)
	error("Can't open listener socket");
    return s;
}

int open_client_socket(void)
{
    static struct sockaddr_storage client_address;
    static unsigned int address_size = sizeof(client_address);
    int s;
    
    if ((s = accept(listener_d, (struct sockaddr *)&client_address, 
		    &address_size)) == -1)
	error("Can't open client socket");
    
    return s;
}

void bind_to_port(int socket, int port)
{
    struct sockaddr_in name;
    name.sin_family = PF_INET;
    name.sin_port = (in_port_t)htons(port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    int reuse = 1;
    
    if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, 
		   (char *)&reuse, sizeof(int)) == -1)
	error("Can't set the 'reuse' option on the socket");
    
    if (bind(socket, (struct sockaddr *)&name, sizeof(name)) == -1)
	error("Can't bind to socket");
}

int say(int socket, char *s)
{
    int result = send(socket, s, strlen(s), 0);
    if (result == -1)
	fprintf(stderr, "%s: %s\n", 
		"Error talking to the client", strerror(errno));
    return result;
}

int read_in(int socket, char *buf, int len)
{
    /* treat the socket stream as a regular IO stream, 
       so we can do character IO */
    FILE *fp = fdopen(socket, "r");
    int i = 0, ch;
    
    /* eat any leading whitespace */
    while (isspace(ch = fgetc(fp)) && ch != EOF)
	;
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

int main(int argc, char *argv[])
{
    int connect_d = 0, rc = 0;
    char intro_msg[] = "Internet Knock-Knock Protocol Server\nKnock, knock.\n";
    
    if (catch_signal(SIGINT, handle_shutdown) == -1)
	error("Setting interrupt handler");
  
    int port = 30000;
    listener_d = open_listener_socket();
    bind_to_port(listener_d, port);
    
    if (listen(listener_d, 10) == -1)
	error("Can't listen");

    printf("Waiting for connection on port %d\n", port);

    char buf[255];

    while (1) {
	connect_d = open_client_socket();

	if (say(connect_d, intro_msg) == -1) {
	    close(connect_d);
	    continue;
	}

	read_in(connect_d, buf, sizeof(buf));
	// check to make sure they said "Who's there?"
	
	if (say(connect_d, "Surrealist giraffe.\n") == -1) {
	    close(connect_d);
	    continue;
	}

	read_in(connect_d, buf, sizeof(buf));
	// check to make sure they said "Surrealist giraffe who?"

 
	if (say(connect_d, "Bathtub full of brightly-colored machine tools.\n") == -1) {
	    close(connect_d);
	    continue;
	}

	close(connect_d);
    }
    return 0;
}
