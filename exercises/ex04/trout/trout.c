#include "trout.h"

/* variables we might want to configure */
int max_ttl = 30;
int nprobes = 2;

/* other global variables */

int seq = 0;

char recvbuf[BUFSIZE];
char sendbuf[BUFSIZE];
Rec *rec = (Rec *) sendbuf;

int sendfd, recvfd;
int pipefd[2];              /* the pipe for the alarm handler */


socklen_t salen;                    /* length of a socket address */
int datalen = sizeof (Rec);         /* length of the data in a datagram */

u_short sport;                      /* source UDP port # */
u_short dport = 32768 + 668;        /* destination port -- hopefully unused */
                                    /* 668 = the neighbor of the beast */
Timeval sendtv[1];
Timeval recvtv[1];
Timeval difftv[1];

/* NOTES: system calls beginning with a capital letter are Stevens's
   wrapper functions.  Each one invokes the method and checks the
   return value.  If the call fails, it invokes err_sys, which prints
   the error message and quits.

   Types that begin with a capital letter are usually typedefs
   that I added because (1) I hate seeing the word struct all over
   the place, and (2) it lets me pretend I am writing Java. */

/* sig_alrm: alarm handler sends a message to the process through
   a pipe, causing select to return */

void sig_alrm (int signo)
{
  Write (pipefd[1], "", 1);  /* write 1 null byte to pipe */
  return;
}

/* process_ip: extracts all the info from an incoming ICMP packet

     Just for kicks, I changed the BSD-style names of the ICMP
     errors to Linux-style names, mostly so that they will be
     consistent with the changes I made in the kernel and so my
     head won't explode. */

int process_ip (struct ip *ip, int len)
{
  int hlen1, hlen2, icmplen;
  struct icmp *icmp;
  struct ip *hip;
  struct udphdr *udp;

  hlen1 = ip->ip_hl << 2;                        /* length of IP header */
  icmp = (struct icmp *) (recvbuf + hlen1);
  icmplen = len - hlen1;

  if (icmplen < 8 + 20 + 8) return 0;

  if (icmp->icmp_type != ICMP_TIME_EXCEEDED &&
      icmp->icmp_type != ICMP_DEST_UNREACH)
    return 0;

  /* hip is the header of the enclosed IP packets, supposedly
     the header of the packet that caused the error */

  hip = (struct ip *) (recvbuf + hlen1 + 8);
  if (hip->ip_p != IPPROTO_UDP) return 0;

  hlen2 = hip->ip_hl << 2;
  udp = (struct udphdr *) (recvbuf + hlen1 + 8 + hlen2);

  if (udp->source != htons (sport)) return 0;
  if (udp->dest != htons (dport + seq)) return 0;

  /* now we know it's an ICMP packet caused by a UDP
     datagram sent by us and sent to the port we happen to
     be sending to.  It's probably one of ours. */

  if (icmp->icmp_type == ICMP_TIME_EXCEEDED) {
    if (icmp->icmp_code == ICMP_EXC_TTL) {
      return -2;
    } else {
      return 0;
    }
  }

  if (icmp->icmp_type == ICMP_DEST_UNREACH) {
    if (icmp->icmp_code == ICMP_PORT_UNREACH) {
      return -1;
    } else {
      return 0;
    }
  }
  return 0;
}

/* recv_dgram: reads all incoming datagrams and checks for
   returning ICMP packets.
   returns -3 on timeout,
           -2 on ICMP time exceeded in transit (we reached a router)
	   -1 on ICMP port unreachable (we reached the destination)
	    0 on ICMP that has nothing to do with us  */

  /* as Stevens points out in Section 18.5 of Unix Network Programming,
     many programs with alarms have a race condition, which is that
     the alarm might go off before we get to the recvfrom, in which
     case it does nothing and the recvfrom might wait indefinitely.

     In earlier versions of this code, this problem seemed to pop
     up occasionally (although I am not positive about that).

     The use of select here solves that problem.  When the alarm
     goes off, the alarm handler sends a message through the pipe,
     which is one of the things select waits for.

     When select returns, we know that we have received a datagram
     OR the alarm has gone off OR both.  We then use rset to find
     out which, and deal with it.

     According to the specification of select, it should not be possible
     to get to the recvfrom unless there is a datagram waiting, and
     therefore the recvfrom should never block.  Nevertheless, it sometimes
     does, which is why, when we opened it, we set the NONBLOCK flag
     and why, if it fails (errno = EAGAIN) we just go on. */

int recv_dgram ()
{
  int err;
  socklen_t len;
  ssize_t n;
  struct ip *ip;
  int maxfdp1 = max (recvfd, pipefd[0]) + 1;
  fd_set rset[1];
  FD_ZERO (rset);

  alarm(3);       /* set the timeout alarm to handle dropped packets */

  while (1) {
    FD_SET (recvfd, rset);
    FD_SET (pipefd[0], rset);

    n = select (maxfdp1, rset, NULL, NULL, NULL);
    if (n < 0 && errno != EINTR) {
      err_sys ("select error");
    }

    if (FD_ISSET (recvfd, rset)) {
      len = salen;
      n = recvfrom (recvfd, recvbuf, sizeof(recvbuf), 0, sarecv, &len);
      err = errno;
      Gettimeofday (recvtv, NULL);   /* get time of packet arrival */
      if (n < 0 && err != EAGAIN) {
	err_sys ("recvfrom error");
      }
    }

    if (FD_ISSET (pipefd[0], rset)) {
      Read (pipefd[0], &n, 1);
      return -3;                 /* timeout */
    }

    ip = (struct ip *) recvbuf;
    return process_ip (ip, n);
  }
}

/* sub_tv: subtract minus from plus and put the result in res */

void sub_tv (Timeval *plus, Timeval *minus, Timeval *res)
{
  res->tv_sec = plus->tv_sec - minus->tv_sec;
  res->tv_usec = plus->tv_usec - minus->tv_usec;

  if (res->tv_usec < 0) {
    res->tv_sec--;
    res->tv_usec += 1000000;
  }
}

/* time_to_double: convert a Timeval to a double.  This only
   works with Timevals that are small (like the difference between
   two real Timevals) */

double time_to_double (Timeval *time)
{
  return time->tv_sec * 1000.0 + time->tv_usec / 1000.0;
}

/* print_report: prints all the information about a successful round trip */

void print_report ()
{
  int stat;
  char str[NI_MAXHOST];

  stat = sock_cmp_addr (sarecv, salast, salen);

  /* if this reply comes from source different from the previous
     one, print the full host information */

  if (stat != 0) {
    stat = getnameinfo (sarecv, salen, str, sizeof(str), NULL, 0, 0);
    if (stat == 0) {
      printf (" %s (%s)", str, Sock_ntop_host (sarecv, salen));
    } else {
      printf (" %s", Sock_ntop_host (sarecv, salen));
    }
    memcpy (salast, sarecv, salen);
  }

  /* calculate and print the round trip time using user-level timestamps */

  sub_tv (recvtv, sendtv, difftv);
  rtt = time_to_double (difftv);

  printf ("  %.3f", time_to_double (difftv));
}

/* send_dgram: generate an outgoing UDP packet */

    /* the second effort send is a kludge to handle a funny
       thing, which is that the last host seems to refuse the
       second or third connection consistently, which might
       might mean that something breaks when we get the
       ICMP_DEST_UNREACH error.  The second attempt seems
       to succeed consistently. */

void send_dgram (int ttl)
{
  int n;

  rec->seq = seq++;
  sock_set_port (sasend, salen, htons(dport+seq));

  Gettimeofday (sendtv, NULL);
  n = sendto(sendfd, sendbuf, datalen, 0, sasend, salen);

  if (n==-1 && errno == ECONNREFUSED) {
    Gettimeofday (sendtv, NULL);
    n = sendto(sendfd, sendbuf, datalen, 0, sasend, salen);
  }

  if (n != datalen) {
    err_sys("sendto error");
  }
}

/* send_probes: sends a set of probes with the given ttl and
   then waits for the replies.  The weird TOS options are there
   as a signal to the kernel to identify clink packets so it can
   fill in the timestamps.  I am assuming that they don't have
   any actual effect. */

int send_probes (int ttl)
{
  int probe, code, done;

  Setsockopt (sendfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(int));
  bzero (salast, salen);

  printf ("%2d  ", ttl);
  fflush (stdout);

  done = 0; /* count the number of probes that generate an ICMP_DEST_UNREACH */

  for (probe = 0; probe < nprobes; probe++) {
    send_dgram (ttl);
    code = recv_dgram ();

    if (code == -3) {
      printf (" *");
    } else {
      print_report ();
    }

    if (code == -1) done++;
    fflush (stdout);
  }
  printf ("ms\n");
  return done;
}

/* loop_ttl: starting with ttl=1, gradually increase ttl until
   we start getting ICMP_DEST_UNREACH instead of ICMP_TIME_EXCEEDED */

void loop_ttl ()
{
  int ttl, done;

  Pipe (pipefd);     /* the pipe for the alarm handler */

  recvfd = socket (sasend->sa_family, SOCK_RAW, IPPROTO_ICMP);
  if (recvfd == -1) {
    if (errno == EPERM) {
      printf ("\nclink was unable to open a raw socket.  The most\n");
      printf ("likely cause is that you are not running it as root.\n");
      exit (1);
    } else {
      err_sys ("opening raw socket in clink");
    }
  }

  fcntl (recvfd, F_SETFL, O_NONBLOCK);
  setuid (getuid ());

  sendfd = socket (sasend->sa_family, SOCK_DGRAM, 0);

  sabind->sa_family = sasend->sa_family;
  sport = (getpid() & 0xffff) | 0x8000;       /* source UDP port # */
  sock_set_port (sabind, salen, htons(sport));
  Bind (sendfd, sabind, salen);

  Signal (SIGALRM, sig_alrm);

  for (ttl = 1; ttl <= max_ttl; ttl++) {
    done = send_probes (ttl);
    if (done > 0) break;
  }
}
