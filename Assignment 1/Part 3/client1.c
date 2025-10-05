
	/* Single server-client connection (pgs 246-247) */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUF_SIZE	1024            // Define buffer size constant for data transmission (1024 bytes)
#define	SERVER_IP	"130.127.24.92" // Define server IP address as string constant
#define SERVER_PORT	60000           // Define server port number for connection

int main(int argc, char *argv[])

{                                   
int			sock_send;          // Declare integer variable to store client socket descriptor
struct sockaddr_in	addr_send;  // Declare sockaddr_in structure to store server address information
int			i;                  // Declare integer variable for function return values
char			text[80],buf[BUF_SIZE]; // Declare character arrays for user input and transmission buffer
int			send_len,bytes_sent;    // Declare integers for message length and bytes sent count

	/* create socket for sending data */         
sock_send=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); // Create TCP socket using IPv4 protocol family
if (sock_send < 0)      // Check if socket creation failed
  {                     
  printf("socket() failed\n");  // Display error message for socket creation failure
  exit(0);              // Terminate program with exit code 0
  }                     

	/* create socket address structure to connect to */ 
memset(&addr_send, 0, sizeof (addr_send)); // Initialize address structure to zero
addr_send.sin_family = AF_INET; // Set address family to IPv4
addr_send.sin_addr.s_addr = inet_addr(SERVER_IP); // Convert IP string to binary format and assign
addr_send.sin_port = htons((unsigned short)SERVER_PORT); // Convert port number to network byte order

	/* connect to the server */   
i=connect(sock_send, (struct sockaddr *) &addr_send, sizeof (addr_send)); // Establish connection to server
if (i < 0)              // Check if connection attempt failed
  {                     
  printf("connect() failed\n"); // Display error message for connection failure
  exit(0);              // Terminate program with exit code 0
  }                     

while (1)               // Begin infinite loop for continuous message sending
  {                     
	/* send some data */
  printf("Send? ");     // Display prompt asking user for input message
  scanf("%s",text);     // Read user input string and store in text array
  if (strcmp(text,"quit") == 0) // Compare input string with "quit" to check for exit condition
    break;              // Exit the while loop if user entered "quit"

  strcpy(buf,text);     // Copy user input from text array to transmission buffer
  send_len=strlen(text); // Calculate length of message to be sent
  bytes_sent=send(sock_send,buf,send_len,0); // Send message through socket and store bytes sent count
  }                     

close(sock_send);       // Close the client socket to free system resources
}                      


