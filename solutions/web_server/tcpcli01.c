#include	"unp.h"

int main(int argc, char **argv)
{
    int	sockfd;
    struct sockaddr_in servaddr;

    if (argc != 2)
	    err_quit("usage: tcpcli <IPaddress>");

    sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(80);
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    
    Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

    send_get(sockfd);
	
    exit(0);
}

void send_get(int sockfd)
{
    int n;
    char recvline[MAXLINE];
    char *sendline = "GET /MCXI HTTP/1.1\r\n";

    Writen(sockfd, sendline, strlen(sendline));
    printf("Sent %s\n", sendline);

    while (1) {
	    n = Readline(sockfd, recvline, MAXLINE);
	    if (n == 0) break;

	    Fputs(recvline, stdout);
    }
}
