/* include unph */
/* Our own header.  Tabs are set for 4 spaces, not 8 */

#ifndef	__unp_h
#define	__unp_h

#include	<sys/types.h>	/* basic system data types */
#include	<sys/socket.h>	/* basic socket definitions */
#include	<sys/time.h>	/* timeval{} for select() */
#include	<time.h>		/* timespec{} for pselect() */
#include	<netinet/in.h>	/* sockaddr_in{} and other Internet defns */
#include	<arpa/inet.h>	/* inet(3) functions */
#include	<errno.h>
#include	<fcntl.h>		/* for nonblocking */
#include	<netdb.h>
#include	<signal.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<sys/stat.h>	/* for S_xxx file mode constants */
#include	<sys/uio.h>		/* for iovec{} and readv/writev */
#include	<unistd.h>
#include	<sys/wait.h>
#include	<sys/un.h>		/* for Unix domain sockets */
#include	<sys/ioctl.h>

/* Following could be derived from SOMAXCONN in <sys/socket.h>, but many
   kernels still #define it as 5, while actually supporting many more */
#define	LISTENQ		1024	/* 2nd argument to listen() */

/* Miscellaneous constants */
#define	MAXLINE		4096	/* max text line length */
#define	MAXSOCKADDR  128	/* max socket address structure size */
#define	BUFFSIZE	8192	/* buffer size for reads and writes */

/* Define some port number that can be used for client-servers */
#define	SERV_PORT		 9877			/* TCP and UDP client-servers */
#define	SERV_PORT_STR	"9877"			/* TCP and UDP client-servers */
#define	UNIXSTR_PATH	"/tmp/unix.str"	/* Unix domain stream cli-serv */
#define	UNIXDG_PATH		"/tmp/unix.dg"	/* Unix domain datagram cli-serv */
/* $$.ix [LISTENQ]~constant,~definition~of$$ */
/* $$.ix [MAXLINE]~constant,~definition~of$$ */
/* $$.ix [MAXSOCKADDR]~constant,~definition~of$$ */
/* $$.ix [BUFFSIZE]~constant,~definition~of$$ */
/* $$.ix [SERV_PORT]~constant,~definition~of$$ */
/* $$.ix [UNIXSTR_PATH]~constant,~definition~of$$ */
/* $$.ix [UNIXDG_PATH]~constant,~definition~of$$ */

/* Following shortens all the type casts of pointer arguments */
#define	SA	struct sockaddr

#define	FILE_MODE	(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
					/* default file access permissions for new files */
#define	DIR_MODE	(FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)
					/* default permissions for new directories */

typedef	void	Sigfunc(int);	/* for signal handlers */

#define	min(a,b)	((a) < (b) ? (a) : (b))
#define	max(a,b)	((a) > (b) ? (a) : (b))

			/* prototypes for our own library functions */
int		 connect_nonb(int, const SA *, socklen_t, int);
int		 connect_timeo(int, const SA *, socklen_t, int);
void	 daemon_init(const char *, int);
void	 daemon_inetd(const char *, int);
void	 dg_cli(FILE *, int, const SA *, socklen_t);
void	 dg_echo(int, SA *, socklen_t);
char	*gf_time(void);
void	 heartbeat_cli(int, int, int);
void	 heartbeat_serv(int, int, int);
struct addrinfo *host_serv(const char *, const char *, int, int);
int		 inet_srcrt_add(char *, int);
u_char  *inet_srcrt_init(void);
void	 inet_srcrt_print(u_char *, int);
char   **my_addrs(int *);
int		 readable_timeo(int, int);
ssize_t	 readline(int, void *, size_t);
ssize_t	 readn(int, void *, size_t);
ssize_t	 read_fd(int, void *, size_t, int *);
ssize_t	 recvfrom_flags(int, void *, size_t, int *, SA *, socklen_t *,
		 struct in_pktinfo *);
Sigfunc *signal_intr(int, Sigfunc *);
int		 sock_bind_wild(int, int);
int		 sock_cmp_addr(const SA *, const SA *, socklen_t);
int		 sock_cmp_port(const SA *, const SA *, socklen_t);
int		 sock_get_port(const SA *, socklen_t);
void	 sock_set_addr(SA *, socklen_t, const void *);
void	 sock_set_port(SA *, socklen_t, int);
void	 sock_set_wild(SA *, socklen_t);
char	*sock_ntop(const SA *, socklen_t);
char	*sock_ntop_host(const SA *, socklen_t);
int		 sockfd_to_family(int);
void	 str_echo(int);
void	 str_cli(FILE *, int);
int		 tcp_connect(const char *, const char *);
int		 tcp_listen(const char *, const char *, socklen_t *);
void	 tv_sub(struct timeval *, struct timeval *);
int		 udp_client(const char *, const char *, void **, socklen_t *);
int		 udp_connect(const char *, const char *);
int		 udp_server(const char *, const char *, socklen_t *);
int		 writable_timeo(int, int);
ssize_t	 writen(int, const void *, size_t);
ssize_t	 write_fd(int, void *, size_t, int);

			/* prototypes for our own library wrapper functions */
void	 Connect_timeo(int, const SA *, socklen_t, int);
struct addrinfo *Host_serv(const char *, const char *, int, int);
const char		*Inet_ntop(int, const void *, char *, size_t);
void			 Inet_pton(int, const char *, void *);
char			*If_indextoname(unsigned int, char *);
unsigned int		 If_nametoindex(const char *);
struct if_nameindex	*If_nameindex(void);
char   **My_addrs(int *);
ssize_t	 Read_fd(int, void *, size_t, int *);
int		 Readable_timeo(int, int);
ssize_t	 Recvfrom_flags(int, void *, size_t, int *, SA *, socklen_t *,
		 struct in_pktinfo *);
Sigfunc *Signal(int, Sigfunc *);
Sigfunc *Signal_intr(int, Sigfunc *);
int		 Sock_bind_wild(int, int);
char	*Sock_ntop(const SA *, socklen_t);
char	*Sock_ntop_host(const SA *, socklen_t);
int		 Sockfd_to_family(int);
int		 Tcp_connect(const char *, const char *);
int		 Tcp_listen(const char *, const char *, socklen_t *);
int		 Udp_client(const char *, const char *, void **, socklen_t *);
int		 Udp_connect(const char *, const char *);
int		 Udp_server(const char *, const char *, socklen_t *);
ssize_t	 Write_fd(int, void *, size_t, int);
int		 Writable_timeo(int, int);

			/* prototypes for our Unix wrapper functions: see {Sec errors} */
void	*Calloc(size_t, size_t);
void	 Close(int);
void	 Dup2(int, int);
int		 Fcntl(int, int, int);
void	 Gettimeofday(struct timeval *, void *);
int		 Ioctl(int, int, void *);
pid_t	 Fork(void);
void	*Malloc(size_t);
void	*Mmap(void *, size_t, int, int, int, off_t);
int		 Open(const char *, int, mode_t);
void	 Pipe(int *fds);
ssize_t	 Read(int, void *, size_t);
void	 Sigaddset(sigset_t *, int);
void	 Sigdelset(sigset_t *, int);
void	 Sigemptyset(sigset_t *);
void	 Sigfillset(sigset_t *);
int		 Sigismember(const sigset_t *, int);
void	 Sigpending(sigset_t *);
void	 Sigprocmask(int, const sigset_t *, sigset_t *);
char	*Strdup(const char *);
long	 Sysconf(int);
void	 Sysctl(int *, u_int, void *, size_t *, void *, size_t);
void	 Unlink(const char *);
pid_t	 Wait(int *);
pid_t	 Waitpid(pid_t, int *, int);
void	 Write(int, void *, size_t);

			/* prototypes for our stdio wrapper functions: see {Sec errors} */
void	 Fclose(FILE *);
FILE	*Fdopen(int, const char *);
char	*Fgets(char *, int, FILE *);
FILE	*Fopen(const char *, const char *);
void	 Fputs(const char *, FILE *);

			/* prototypes for our socket wrapper functions: see {Sec errors} */
int		 Accept(int, SA *, socklen_t *);
void	 Bind(int, const SA *, socklen_t);
void	 Connect(int, const SA *, socklen_t);
void	 Getpeername(int, SA *, socklen_t *);
void	 Getsockname(int, SA *, socklen_t *);
void	 Getsockopt(int, int, int, void *, socklen_t *);
int		 Isfdtype(int, int);
void	 Listen(int, int);
#ifdef	HAVE_POLL
int		 Poll(struct pollfd *, unsigned long, int);
#endif
ssize_t	 Readline(int, void *, size_t);
ssize_t	 Readn(int, void *, size_t);
ssize_t	 Recv(int, void *, size_t, int);
ssize_t	 Recvfrom(int, void *, size_t, int, SA *, socklen_t *);
ssize_t	 Recvmsg(int, struct msghdr *, int);
int		 Select(int, fd_set *, fd_set *, fd_set *, struct timeval *);
void	 Send(int, const void *, size_t, int);
void	 Sendto(int, const void *, size_t, int, const SA *, socklen_t);
void	 Sendmsg(int, const struct msghdr *, int);
void	 Setsockopt(int, int, int, const void *, socklen_t);
void	 Shutdown(int, int);
int		 Sockatmark(int);
int		 Socket(int, int, int);
void	 Socketpair(int, int, int, int *);
void	 Writen(int, void *, size_t);

void	 err_dump(const char *, ...);
void	 err_msg(const char *, ...);
void	 err_quit(const char *, ...);
void	 err_ret(const char *, ...);
void	 err_sys(const char *, ...);

#endif	/* __unp_h */
