# *UDP* Client/Server Echo Chat in *C*

A simple [UDP](https://en.wikipedia.org/wiki/User_Datagram_Protocol) echo chat client/server program. While this does not implement [RFC 862](https://en.wikipedia.org/wiki/Echo_Protocol), it is the same idea.
This was an assignment for [LAN-375](https://montcs.bloomu.edu/375/) at Bloomsburg University.
This course was taught by [Professor Robert Montante](https://montcs.bloomu.edu/).

# Installation

Compile and run the server:

`gcc -o server process.c udp_server.c && ./server 3669`

Compile and run the client:

`gcc -o client udp_client.c && ./client 127.0.0.1 3669`

Messages sent by the client will be 'echoed' back to the client by the server.

# Credits
[*ultasun*](https://github.com/ultasun) is the sole author of this work, it was a homework assignment. 
The assignment was completed fall semester of 2011.

Thanks for reading!
