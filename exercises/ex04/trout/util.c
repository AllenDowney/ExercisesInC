#include "util.h"

void err_doit (int errnoflag, int level, char *fmt, va_list ap)
{
  int errno_save, n;
  char buf[MAXLINE];

  errno_save = errno;             /* value caller might want printed */
  vsnprintf (buf, sizeof(buf), fmt, ap);
  n = strlen (buf);
  if (errnoflag)
    snprintf (buf+n, sizeof(buf) - n, ": %s", strerror(errno_save));
  strcat (buf, "\n");

  fflush (stdout);
  fputs (buf, stderr);
  fflush (stderr);
}

void err_sys (char *fmt, ...)
{
  va_list ap;
  va_start (ap, fmt);
  err_doit (1, LOG_ERR, fmt, ap);
  va_end(ap);
  exit(1);
}

void err_quit (char *fmt, ...)
{
  va_list ap;
  va_start (ap, fmt);
  err_doit (0, LOG_ERR, fmt, ap);
  va_end(ap);
  exit(1);
}



char *sock_ntop_host(const struct sockaddr *sa, socklen_t salen)
{
  static char str[128];

  switch (sa->sa_family) {
  case AF_INET: {
    struct sockaddr_in      *sin = (struct sockaddr_in *) sa;

    if (inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)) == NULL) {
      return NULL;
    } else {
      return str;
    }
  }
  case AF_UNIX: {
    struct sockaddr_un      *unp = (struct sockaddr_un *) sa;

    /* OK to have no pathname bound to the socket: happens on
       every connect() unless client calls bind() first. */
    if (unp->sun_path[0] == 0)
      strcpy(str, "(no pathname bound)");
    else
      snprintf(str, sizeof(str), "%s", unp->sun_path);
    return str;
  }
  default:
    snprintf(str, sizeof(str), "sock_ntop_host: unknown AF_xxx: %d, len %d",
	     sa->sa_family, salen);
    return str;
  }
  return NULL;
}

char *Sock_ntop_host(const struct sockaddr *sa, socklen_t salen)
{
  char *ptr;

  if ( (ptr = sock_ntop_host(sa, salen)) == NULL)
    err_sys("sock_ntop_host error");        /* inet_ntop() sets errno */
  return(ptr);
}

void sock_set_port(struct sockaddr *sa, socklen_t salen, int port)
{
  switch (sa->sa_family) {
    case AF_INET: {
      struct sockaddr_in	*sin = (struct sockaddr_in *) sa;

      sin->sin_port = port;
      return;
    }
    return;
  }
}

int sock_cmp_addr(const struct sockaddr *sa1, const struct sockaddr *sa2,
		  socklen_t salen)
{
  if (sa1->sa_family != sa2->sa_family)
    return(-1);

  switch (sa1->sa_family) {
    case AF_INET: {
      return(memcmp( &((struct sockaddr_in *) sa1)->sin_addr,
		     &((struct sockaddr_in *) sa2)->sin_addr,
		     sizeof(struct in_addr)));
    }

    case AF_UNIX: {
      return(strcmp( ((struct sockaddr_un *) sa1)->sun_path,
		     ((struct sockaddr_un *) sa2)->sun_path));
    }
  }
  return -1;
}

void tv_sub (struct timeval *out, struct timeval *in)
{
  if ( (out->tv_usec -= in->tv_usec) < 0) {     /* out -= in */
    --out->tv_sec;
    out->tv_usec += 1000000;
  }
  out->tv_sec -= in->tv_sec;
}

char *icmpcode_v4(int code)
{
  switch (code) {
    case  0: return("network unreachable");
    case  1: return("host unreachable");
    case  2: return("protocol unreachable");
    case  3: return("port unreachable");
    case  4: return("fragmentation required but DF bit set");
    case  5: return("source route failed");
    case  6: return("destination network unknown");
    case  7: return("destination host unknown");
    case  8: return("source host isolated (obsolete)");
    case  9: return("destination network administratively prohibited");
    case 10: return("destination host administratively prohibited");
    case 11: return("network unreachable for TOS");
    case 12: return("host unreachable for TOS");
    case 13: return("communication administratively prohibited by filtering");
    case 14: return("host recedence violation");
    case 15: return("precedence cutoff in effect");
    default: return("[unknown code]");
  }
}

Sigfunc *signal(int signo, Sigfunc *func)
{
  struct sigaction act, oact;

  act.sa_handler = func;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;
  if (signo == SIGALRM) {
    act.sa_flags |= SA_INTERRUPT;     /* SunOS 4.x (and Linux, apparently) */
  }
  if (sigaction(signo, &act, &oact) < 0)
    return(SIG_ERR);
  return(oact.sa_handler);
}

Sigfunc *Signal(int signo, Sigfunc *func)	/* for our signal() function */
{
  Sigfunc *sigfunc;

  if ( (sigfunc = signal(signo, func)) == SIG_ERR)
    err_sys("signal error");
  return(sigfunc);
}

void *Malloc(size_t size)
{
  void	*ptr;

  if ( (ptr = malloc(size)) == NULL)
    err_sys("malloc error");
  return(ptr);
}

void *Calloc(size_t n, size_t size)
{
  void	*ptr;

  if ( (ptr = calloc(n, size)) == NULL)
    err_sys("calloc error");
  return(ptr);
}

void Gettimeofday(struct timeval *tv, void *foo)
{
  if (gettimeofday(tv, foo) == -1)
    err_sys("gettimeofday error");
  return;
}

void Pipe(int *fds)
{
  if (pipe(fds) < 0)
    err_sys("pipe error");
}

void Bind(int fd, const struct sockaddr *sa, socklen_t salen)
{
  if (bind(fd, sa, salen) < 0)
    err_sys("bind error");
}

void Setsockopt(int fd, int level, int optname, const void *optval,
		socklen_t optlen)
{
  if (setsockopt(fd, level, optname, optval, optlen) < 0)
    err_sys("setsockopt error");
}

struct addrinfo *
host_serv (char *host, char *serv, int family, int socktype)
{
  int n;
  struct addrinfo hints, *res;

  bzero (&hints, sizeof(struct addrinfo));
  hints.ai_flags = AI_CANONNAME;           /* return canonical name */
  hints.ai_family = family;
  hints.ai_socktype = socktype;

  n = getaddrinfo (host, serv, &hints, &res);
  if (n != 0) {
    return NULL;
  } else {
    return res;     /* return pointer to first on linked list */
  }
}

/*
 * There is no easy way to pass back the integer return code from
 * getaddrinfo() in the function above, short of adding another argument
 * that is a pointer, so the easiest way to provide the wrapper function
 * is just to duplicate the simple function as we do here.
 */

struct addrinfo *
Host_serv(const char *host, const char *serv, int family, int socktype)
{
  int n;
  struct addrinfo hints, *res;

  bzero(&hints, sizeof(struct addrinfo));
  hints.ai_flags = AI_CANONNAME;  /* always return canonical name */
  hints.ai_family = family;               /* 0, AF_INET, AF_INET6, etc. */
  hints.ai_socktype = socktype;   /* 0, SOCK_STREAM, SOCK_DGRAM, etc. */

  if ( (n = getaddrinfo(host, serv, &hints, &res)) != 0)
    err_quit("host_serv error for %s, %s: %s",
	     (host == NULL) ? "(no hostname)" : host,
	     (serv == NULL) ? "(no service name)" : serv,
	     gai_strerror(n));

  return(res);    /* return pointer to first on linked list */
}


ssize_t Read(int fd, void *ptr, size_t nbytes)
{
  ssize_t n;

  if ( (n = read(fd, ptr, nbytes)) == -1)
    err_sys("read error");
  return(n);
}

void Write(int fd, void *ptr, size_t nbytes)
{
  if (write(fd, ptr, nbytes) != nbytes)
    err_sys("write error");
}

ssize_t Recvfrom(int fd, void *ptr, size_t nbytes, int flags,
		 struct sockaddr *sa, socklen_t *salenptr)
{
  ssize_t n;

  n = recvfrom(fd, ptr, nbytes, flags, sa, salenptr);
  if (n < 0)
    err_sys("recvfrom error");
  return(n);
}
