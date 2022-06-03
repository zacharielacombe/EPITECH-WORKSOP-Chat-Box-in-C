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
Bind the socket to a address struct sockaddr_in
## I.b : Accept a connection
## I.c : Receive data from the client
## I.d : Accept multiple connections
## I.e : Receive data from multiple clients
## I.f : Send some data to everybody

# Step II : Client
## II.a : Initialisation
## II.b : Connect to the server
## II.c : Get the client input without
## II.e : Send the input to the server
## II.f : Receive the data from the server

# Bonus
Be creative try to improve your chat box by adding usernames, login, error handling server-side.
