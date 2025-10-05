
	/* Single server-client connection; server can talk to only
	** one client at a time (pgs 244-246) */

#include <stdio.h>
#include <sys/types.h>	/* system type defintions */
#include <sys/socket.h>	/* network system functions */
#include <netinet/in.h>	/* protocol & struct definitions */

#define BUF_SIZE	1024    // Define buffer size constant for data reception (1024 bytes)
#define LISTEN_PORT	60000   // Define port number on which server will listen for connections

int main(int argc, char *argv[])

{                                   
int			sock_listen,sock_recv;  // Declare integers for listening socket and receiving socket descriptors
struct sockaddr_in	my_addr,recv_addr;  // Declare sockaddr_in structures for server and client addresses
int			i,addr_size,bytes_received; // Declare integers for return values, address size, and received byte count
fd_set			readfds;            // Declare file descriptor set for select() function
struct timeval		timeout={0,0};  // Declare timeout structure for select() function
int			incoming_len;           // Declare integer for incoming connection length 
struct sockaddr		remote_addr;    // Declare generic socket address structure
int			recv_msg_size;          // Declare integer for received message size
char			buf[BUF_SIZE];      // Declare character array buffer for storing received messages
int			select_ret;             // Declare integer for select() return value


        /* create socket for listening */ 
sock_listen=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); // Create TCP socket using IPv4 protocol family
if (sock_listen < 0)    // Check if socket creation failed
  {                     
  printf("socket() failed\n"); // Display error message for socket creation failure
  exit(0);              // Terminate program with exit code 0
  }                     
	/* make local address structure */     
memset(&my_addr, 0, sizeof (my_addr));	// Initialize address structure to zero
my_addr.sin_family = AF_INET;	        // Set address family to IPv4
my_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // Set IP address to accept connections from any interface
my_addr.sin_port = htons((unsigned short)LISTEN_PORT); // Convert port number to network byte order
	/* bind socket to the local address */    
i=bind(sock_listen, (struct sockaddr *) &my_addr, sizeof (my_addr)); // Bind socket to specified address and port
if (i < 0)              // Check if binding failed
  {                     // Begin error handling block
  printf("bind() failed\n"); // Display error message for binding failure
  exit(0);              // Terminate program with exit code 0
  }                     // End error handling block
	/* listen ... */      // Comment explaining listening state activation
i=listen(sock_listen, 5); // Set socket to listening mode with queue size of 5 pending connections
if (i < 0)              // Check if listen operation failed (returns negative value on error)
  {                     // Begin error handling block
  printf("listen() failed\n"); // Display error message for listen failure
  exit(0);              // Terminate program with exit code 0
  }                     // End error handling block

	/* get new socket to receive data on */ 
addr_size=sizeof(recv_addr); // Set size variable for client address structure
sock_recv=accept(sock_listen, (struct sockaddr *) &recv_addr, &addr_size); // Accept incoming client connection

while (1)               // Begin infinite loop for continuous message reception
  {                     
  bytes_received=recv(sock_recv,buf,BUF_SIZE,0); // Receive data from client through socket
  buf[bytes_received]=0; // Add null terminator to received data to create valid string
  printf("Received: %s\n",buf); // Display received message with "Received:" prefix
  if (strcmp(buf,"shutdown") == 0) // Compare received message with "shutdown" command
    break;              // Exit the while loop if "shutdown" command received
  }                    

close(sock_recv);       // Close the client communication socket to free resources
close(sock_listen);     // Close the listening socket to free resources
}                      


