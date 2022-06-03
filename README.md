# Chat-Box-in-C
Hello everyone here is a little worshop about network programming in C. You will realise a simple non-local chat box using select.

💡If you don't understand anything about select dont forget to ask one of the manager of the workshop


# Prerequisit
For the first step you will not write the client yet so to test your server you could use Telnet.

Here is the install :

Ubuntu :
```shell
sudo apt install telnetd -y
```
Fedora :
```shell
sudo dnf install dnf-plugins-core -y
sudo dnf install telnet telnet-server
```
# Step I : Server
Basically you have to make a server that can get multiple connections and if a message is sent by one the client, every client should get the message.
## I.a : Initialisation
Create a socket with IPv4 addressing and a TCP communication (man socket).
Bind the socket to the following address : 
```c
struct sockaddr_in addr_server;
addr_server.sin_family = AF_INET;
addr_server.sin_port = htons(port);
addr_server.sin_addr.s_addr = inet_addr(ip_address);
```
Then, use the listen function (man listen) to marks the socket of the server referred to by "sockfd" as a passive socket taht can accept incoming connections.
## I.b : Accept a connection
Using the function accept (man accept) accept a new connection to your server. You can use Telnet to test if your server is accepting connections properly.
## I.c : Receive data from the client
You can now receive data from your client by using the socket given by the accept function and asking it to receive data from this file descriptor.

With the recv function (man recv) you can receive data from any file descriptor.
## I.d : Accept multiple connections
Lets start the hard part, the select part.
Here is some documentation : https://pubs.opengroup.org/onlinepubs/7908799/xsh/select.html#:~:text=The%20select()%20function%20tests,descriptors%20are%20ready%20to%20read.
Create three structures and set them to 0.
```c
fd_set fds;
fd_set rfds;
fd_set wfds;
```
The fds structure is here to collect every new client. The rfds and wfds is used to copy the data from fds and to get filtred by select.

Create a server_loop function where your select get the readable and writable file descriptors.
To get new connection you just have to know if your socket server is readable by using the FD_ISSET macro, example :
```c
if (FD_ISSET(server_socket, &rfds))
{
  // accept new connection
}
```
If the server socket is readable it means that a new connection is available. Now set the new client socket to fds using FD_SET.
## I.e : Receive data from multiple clients
Using the array of client you created in the last step, go through the entire array and ask if every socket is readable using the FD_ISSET macro.
## I.f : Send some data to everybody
Using the same logic from the last step, go through the array of client and using the send function (man send) send to each client who is writable the given data.

# Step II : Client
## II.a : Initialisation
Create a socket with IPv4 addressing and a TCP communication (man socket).
## II.b : Connect to the server
With the same address as the server use the connect function (man connect) and give it the client socket and the client address.
```c
struct sockaddr_in addr_server;
addr_client.sin_family = AF_INET;
addr_client.sin_port = htons(port);
addr_client.sin_addr.s_addr = inet_addr(ip_address);
```
## II.c : Get the client input without
Using the select function (man select) give your client socket and stdin, the standard input. By doing so you can know get the input from the terminal without blocking anything.
## II.d : Send the input to the server
Using the macro FD_ISSET check if your client socket is writable and send the data to the server.
## II.e : Receive the data from the server
Using same macro as before check if the client is readable and receive the data from the server.

# Bonus
Be creative try to improve your chat box by adding usernames, login, error handling server-side.
