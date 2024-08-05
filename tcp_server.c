#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

void chomp_newline(char string[]) ;

int main() {

	char server_message[256] = "You have reached the server!";
	
	//create the server socket
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	//define the server address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;

	//bind the socket to our specified IF and port
	bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
	
	//first is the socket as defined above
	//second is backlog of how many connections can be waiting for connection to socket 
	listen(server_socket, 5);

	// Inform the user that the connection will be blocked until client is run
	puts("Waiting for client to connect") ; 
	
	int client_socket;
	//first parameter is socket accepting parameters on - server socket
	//second parameter is structure for address for client connection
	//third parameter is size for address of the client
	client_socket = accept(server_socket, NULL, NULL);
	

	ssize_t send_error = 0 ;
	do {
		// We can get a sigpipe here, I am not catching it

		printf("%s","Enter the message to be sent (type exit to leave): ");
		fgets(server_message,sizeof(server_message),stdin);
		chomp_newline(server_message);
		
		//first parameter is socket that we are sending data on
		//the message that is being sent
		//size of message
		//optional flags parameter***
		send_error = send(client_socket, server_message, sizeof(server_message), 0);
	}  while (strcmp(server_message,"exit") != 0 && send_error >= 0 ) ;

	//close the socket
	close(server_socket);

	return 0;
}

void chomp_newline(char string[])
{
	size_t i ;
	for (i = 0 ; string[i] != '\0' ; i++)
	{
		if (string[i] == '\n') 
		{
			string[i] = '\0' ;
		}
	}
}


