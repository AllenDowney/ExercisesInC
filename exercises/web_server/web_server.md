# Web Server Exercise

Reading: Chapter 11 of *Head First C*.

1) This directory contains code from Stevens's *UNIX Network
Programming* (UNP), modified by Allen Downey.  The files are:

* `tcpcli01.c`: A simple TCP client.

* `tcpserv01.c`: A simple TCP server.

* `str_cli08.c`: Provides a simple TCP client that reads from the
  command line, sends a query to the server, and prints the response.

* `str_echo08.c`: Modified version of Stevens's echo sever that
implements a super basic arithmetic server.

* `unp.h`: Header file with declaration for the functions in the UNP library.

* `error.c`: Functions for reporting errors.

* `wraplib.c`: Wrappers for functions in the UNP library.

* `wrapsock.c`: Wrappers for functions related to sockets.

* `wrapstdio.c`: Wrappers for functions in stdio.h

* `wrapunix.c`: Wrappers for various UNIX functions.

* `readline.c`: Wrapper functions for reading from file descriptors.

* `writen.c`: Wrapper functions for writing to file descriptors.


2) Run the server in one window:

    ./tcpserv01

In another window, connect to it:

    ./tcpcli01 127.0.0.1

Type a mathematical expression like 1+2.  The reply should be 3.

3) Find a partner, and try to connect to each other's servers.  You
can get your IP address by running ipconfig.  If you are running a
firewall, you might find that you cannot connect.

One way to get around firewalls is to make every new service look like
web traffic.  Modify the server and client to use port 80 and see if
that gets through (see `SERV_PORT` in `unp.h`).

4) Modify the server code to implement a minimal web
server.  You should be able to handle some kind of GET request, and
send back some kind of legal HTTP reply.  One option is to write a
service that converts Roman numerals to Arabic numerals.  For example, if
you receive

    GET /MCXI HTTP/1.1

You should generate a reply that includes a minimal HTTP header and a
minimal web page containing the number 1111, like this:

    HTTP/1.0 200 OK
    <body>1111</body>

Modify the server to use port 80, then connect to your
server with a browser.  You would use a URL like this:

    http://127.0.0.1/MCXI

You should see a web page with the number 1111.
