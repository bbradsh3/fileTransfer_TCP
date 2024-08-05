Getting the source code
=========================

We should have sent you the source code for the program. It is also on
the blanca server at
/home/landerse/Public/networks_class/project_1/TCP_framework/ on
blanca.

How to build
============

get the source code and open up the TCP_framework project folder.
After that run `make` to create the binary executables. You should
have "tcp_client" and "tcp_server" as the executables made. 

How to execute
=============

Open up two seperate terminals and navigate to the directory with the
tcp_client and tcp_server executables in them.

Run
$ ./tcp_server
on the first terminal. this must be done before you run the client

Run
$ ./tcp_client
on the second terminal. 

After that enter messages for the server to send to the client.

Statements
==========

Brandon Bradshaw
------------------
I have neither given nor received unauthorized assistance on this work

Through this project I was able to learn a lot about how to make a TCP connection 
in order to transmit data, in this case a simple message. When I first looked at 
this project I was a bit itimidated. Since in class we go in depth how the connections
are made, I thought initially that we would have to code all of it by hand. Luckily, 
since these protocols have been established for quite some time much of the code is 
available through various libraries such as the <netinet/in.h> library that is available
in C already. This made a lot of the heavy lifting easier since we were able to call prebuilt
methods and pass the relevant information on. I also learned that it was a bit easier to run
and establish the connection since both the server and the client were running on the same 
machine. One of the things that I found most interesting that I learned was an easy way to 
include a simple error check. On the client we called the "Connect" method which naturally 
returns the value of either 0 or -1. O meaning there were no errors when establishing the
connection between the client and the server, -1 if the connection was unable to be successfully
established. This made it very easy to use to determine if the connection was successful by
storing this value in a variable, which we called connection_status on the client which we then
passed through an if statement to print out error message in the event of unsuccessful connection.

Logan Andersen :
------------------
I have neither given nor received unauthorized assistance on this work

Description of what I've learned:

Brandon did most of the work on this project, I mainly read his source
code and comments. The thing I did was made it so the program looped to send
the messages multiple times. I learned that listening prepares the connection
but is non blocking, you have to call accept to accept the connection and that
blocks the program so you should do everything you need to do before calling
accept. The functions return a value of ssize_t type and a -1 means there was
an error. The recv function is basically like read but it can have flags. But
there is a difference because read will wait if the server sends an early
message whereas recv will give the message. recv returns 0 if the connection
closes naturally, an early version of the program I made did not check for 0
it only checked for -1 so I kept getting an infinite loop If I did ^C on the
server program with the client still open. If you close the client on a
server, then you can get a sigpipe signal, so if this program was more
complicated I would have to catch that signal. 

I learned how to use the functions by reading the manpages for them on
the Linux Programmer's Manual. I learned about the functions by
reading brandon's code. The Linux programmers manual is a set of
manpages on a lot of Linux systems. It is on my system I have at home
and it is on blanca. To read a function just do `man function` for
instance I did `man recv` to read the manpage for that. I also read
the book for more understanding of the primitive calls. 


