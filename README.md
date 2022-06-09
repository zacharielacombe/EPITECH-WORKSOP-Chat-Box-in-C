# Chat-Box-in-C
Hello everyone here is a little workshop about network programming in C. You will realise a simple non-local chat box using select.

💡 If you don't understand anything about select dont worry, a simple explanation will be provided in the README. Also don't forget to ask one of the manager of the workshop


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
# 💡 Before starting anything...
Everything written in the following steps is not what you should absolutely do, you are free to try different ways of achieving the same goal.

There are just one mandatory : you have to use select to communicate with your clients. That's it.

Also, a Makefile is provided, use it to compile your program just add your files there.
# Step I : Server
Basically, you have to make a server that can get multiple connections and if a message is sent by one of the client, every clients should get the message.
## I.a : Initialisation
Go in the ```init_server()``` function.

Create a socket with IPv4 addressing and a TCP communication using the ```socket()``` function (man socket).
Bind the socket to the following address using ```bind()``` (man bind) : 
```c
struct sockaddr_in addr_server;
addr_server.sin_family = AF_INET;
addr_server.sin_port = htons(port);
addr_server.sin_addr.s_addr = inet_addr(ip_address);
```
Then, use the listen function (man listen) to mark the socket of the server referred to "sockfd" as a passive socket that can accept incoming connections.
## I.b : Accept a connection
Using the function ```accept()``` (man accept) accept a new connection to your server. You can use Telnet to test if your server is accepting connections properly.
## I.c : Receive data from the client
You can now receive data from your client by using the socket given by the accept function and asking it to receive data from this file descriptor.

With the ```recv()``` function (man recv) you can receive data from any file descriptor.
## I.d : Accept multiple connections
Lets start the hard part, the select part.
Here is some documentation : https://pubs.opengroup.org/onlinepubs/7908799/xsh/select.html#:~:text=The%20select()%20function%20tests,descriptors%20are%20ready%20to%20read.

You will use the three structures, ```fd_set fds```, ```fd_set wfds``` and ```fd_set rfds``` located in the ```server_t``` structure in the server.h include for the select function.
### In the init_server.c file
```c
fd_set fds;
fd_set rfds;
fd_set wfds;
```
```fd_set``` is a structure that can contain any file descriptor, it look like that :
```c
typedef struct fd_set {
  unsigned int fd_count;       /* how many are set */
  int  fd_array[FD_SETSIZE];   /* an array of fd */
} fd_set;
```
So we will use the variable ```fds``` in our ```server_t``` structure to contain all of our new clients.
First of all we have to give our server socket so we can accept new connections using ```fds```.

Use the macro ```FD_SET``` (man select) to give a new file descriptor to the structure. Next to all of that, you have to keep track of all our file descriptors. To do that, using the ```int *fd_array``` variable in the ```server_t``` structure, you will add every new socket or delete if a connection is closed.

The ```fds``` structure is here to collect every new client. The ```rfds``` and ```wfds``` is used to copy the data from ```fds``` and to get filtered by select.

## ```select()``` simple explanation for smooth brains :
Basically, ```select()``` is a function that filter ```readfds```, ```writefds``` and ```exceptfds``` (we will not use the third fds).

It removes the file descriptors in the array of file descriptors of ```readfds``` if the read action is blocking and do the same for the ```writefds``` if the write action is blocking.

### If you want a little example :
This is your array of file descriptors inside the ```fd_set``` structure : ```fd_array[] = [3, 5, 7, 8, 12]```.

You will give the address of the structure to select and it will remove the blocking file descriptors.

So if the select have removed some file descriptors you will get that after the function have finised : ```fd_array[] = [5, 8, 12]```.

So when the ```select()``` function have finished to check every file descriptor and remove the blocking ones, it will return the total number of non blocking file descriptors and you will have your ```fd_set``` filtered. That's where you will use the macro ```FD_ISSET``` (man select) to check if a file descriptor still exists in your fd_set.

If you have a very smooth brain, don't worry you can ask help at any moment.

### In the run_server.c file :
Create a server_loop function where you copy fds to rfds and write fds. With thoses,y our select get the readable and writable file descriptors and can return you the available file descriptors.

To get new connection you just have to know if your server socket is readable by using the ```FD_ISSET``` macro, example :
```c
if (FD_ISSET(server_socket, &rfds))
{
  // accept new connection
}
```
If the server socket is readable it means that a new connection is available. Now set the new client socket to fds using FD_SET.

Don't forget to use your array of client to store each new client.
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
So yeah, there is a problem, how should I get the input of the keyboard without blocking the all program and without using a thread ?

It's quit simple, by giving the standard input to select, he can know when the standard input is readable. ```ian a dan le ciboulo hein ?```
### In the init_client.c file
Using ```FD_SET``` add the stdin file descriptor to your fds.
### In the run_client.c file
Get the input of the client without blocking anything.
## II.d : Send the input to the server
Using the macro ```FD_ISSET``` check if your client socket is writable and send the data to the server.
## II.e : Receive the data from the server
Using same macro as before, check if the client is readable and receive the data from the server.

# Bonus
Be creative try to improve your chat box by adding usernames, login, error handling (server-side only), colors, the ability of the server to send message from his standard input to the clients, or even shell embebed games (yeah it not that difficult, you just have to get the input of the client and send him the output of the game. It's like cloud gaming.).
