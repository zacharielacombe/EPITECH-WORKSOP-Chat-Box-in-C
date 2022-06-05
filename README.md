# Chat-Box-in-C
Hello everyone here is a little workshop about network programming in C. You will realise a simple non-local chat box using select.

💡If you don't understand anything about select dont forget to ask one of the manager of the workshop


# Prerequisit
For the first step you will not write the client yet so to test your server you could use Telnet.

Here is how to install it :

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
Basically, you have to make a server that can get multiple connections and if a message is sent by one of the client, every clients should get the message.
## I.a : Initialisation
Go in the ```init_server()``` function.

Create a socket with IPv4 addressing and a TCP communication using the ```sucket()``` function (man socket).
Bind the socket to the following address using ```bind()``` (man bind) : 
```c
struct sockaddr_in addr_server;
addr_server.sin_family = AF_INET;
addr_server.sin_port = htons(port);
addr_server.sin_addr.s_addr = inet_addr(ip_address);
```
Then, use the listen function (man listen) to mark the socket of the server referred to "sockfd" as a passive socket that can accept incoming connections.
## I.b : Accept a connection
Using the function accept (man accept) accept a new connection to your server. You can use Telnet to test if your server is accepting connections properly.
## I.c : Receive data from the client
You can now receive data from your client by using the socket given by the accept function and asking it to receive data from this file descriptor.

With the recv function (man recv) you can receive data from any file descriptor.
## I.d : Accept multiple connections
Lets start the hard part, the select part.
Here is some documentation : https://pubs.opengroup.org/onlinepubs/7908799/xsh/select.html#:~:text=The%20select()%20function%20tests,descriptors%20are%20ready%20to%20read.
### In the init_server.c file
With the three structures ```fd_set``` located in the ```server_t``` structure and set them to 0 in the ```init_server()``` function.
```c
fd_set fds;
fd_set rfds;
fd_set wfds;
```
```fd_set``` is a structure that can contain any file descriptor, so we will use the varaible ```fds``` in our ```server_t``` structure to contain all of our new clients.
First of all we have to give our server socket so we can accept new connections using ```fds```.

Use the macro ```FD_SET``` (man select) to give a nex file descriptor to the structure.

The fds structure is here to collect every new client. The rfds and wfds is used to copy the data from fds and to get filtred by select.

### In the run_server.c file :
Create a server_loop function where you copy fds to rfds and write fds. With thoses,y our select get the readable and writable file descriptors and can return you the available file descriptors.

To get new connection you just have to know if your server socket is readable by using the ```FD_ISSET``` (man select) macro, example :
```c
if (FD_ISSET(server_socket, &rfds))
{
  // accept new connection
}
```
If the server socket is readable it means that a new connection is available. Now set the new client socket to fds using FD_SET.

the ```fd_set``` structure will store your client, but to handle them, create a array of file descriptors to store each new client.
## I.e : Receive data from multiple clients
Using the array of client you created in the last step, go through the entire array and ask if every socket is readable using the ```FD_ISSET``` macro, and use the ```recv()``` function to receive new data.
## I.f : Send some data to everybody
Using the same logic from the last step, go through the array of client and using the ```send()``` function (man send), send to each client who is writable the given data.

# Step II : Client
## II.a : Initialisation
### In the init_client.c file
Create a socket with IPv4 addressing and a TCP communication using the ```socket()``` function (man socket).
Then initialise the address of the client.
```c
struct sockaddr_in addr_server;
addr.sin_family = AF_INET;
addr.sin_port = htons(port);
addr.sin_addr.s_addr = inet_addr(ip_address);
```
## II.b : Connect to the server
With the address you have initialise use the ```connect()``` function (man connect) and give it the client socket and the client address.
## II.c : Get the client input without getline
### In the init_client.c file
Using ```FD_SET``` add the stdin file descriptor to your fds.
### In the run_client.c file
Using the ```select()``` you can know get the input from the terminal without blocking anything.
## II.d : Send the input to the server
Using the macro ```FD_ISSET``` check if your client socket is writable and send the data to the server.
## II.e : Receive the data from the server
Using same macro as before, check if the client is readable and receive the data from the server.

# Bonus
Be creative try to improve your chat box by adding usernames, login, error handling (server-side only), colors, even shell embebed games (yeah it not that difficult, you just have to get the input of the client and send him the output of the game).
