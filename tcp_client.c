#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>



int main() {

	//creating the socket by initializing int that holds socket descriptor
	int network_socket;

	/* calling socket function
	*  domain of socket is first parameter
	*  second -- type of socket -- "  SOCK_STREAM  " is for TCP
	*  third -- protocol --- 0 for default
	*/
	network_socket = socket(AF_INET, SOCK_STREAM, 0);

	// specifying address for the socket
	struct sockaddr_in server_address;
	//sets address
	server_address.sin_family = AF_INET;
	//htons() function converts port number to correct data format
	server_address.sin_port = htons(9002);
	/* "  server_address  " is a structure holding info about the address
	*  "  .sin_addr.s_addr  "  is also a structure contains a field holding the address 
	*  itself that you are tring to connect to
	*  "  INADDR_ANY   " is where you would put the IP for the "server" you are connecting to 
	*  	-specifically this designates any open port on the local machine same as calling 0.0.0.0
	*
	*/
	server_address.sin_addr.s_addr = INADDR_ANY;
	
	/*
	 *  connect function that takes actual socket as first parameter
	 *  second parameter casts server address to right structure type since in struct above is "  sockaddr_in  "
	 *  	casts pointer to struct for sockaddr
	 *  third parameter is the size of the address using sizeof() function
	 *
	 *  connect method returns an int an can be used for primative error handling
	 *              "0" == no errors
	 *              "-1" == error with connection
	 */
	int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));

	/*
	 *	check for error with the connection
	 */
	if (connection_status == -1){
		printf("There was an error making a connection to the remote socket \n\n");
	} else { 
		//string to hold data that might be received from server
		char server_response[256];
		ssize_t recieve_status;
		
		do {
			
			/*
			 *  receive function
			 *  socket as first parameter
			 *  second parameter is address of the server response
			 *  third parameter is the size of the info that we receive from socket
			 *  fourth parameter is optional flags parameter
			 */
			recieve_status = recv(network_socket, &server_response, sizeof(server_response), 0);
			//print out the server's response
			if ( recieve_status > 0 )
			{
				printf("The server sent the data : %s\n", server_response);
			}
			// recieve status is zero if the server shuts
			// off, recieve status is -1 if there was an
			// error
		} while (strcmp("exit",server_response) != 0 && recieve_status > 0 ) ;

		if (recieve_status == 0) {
			puts("The server exited without saying exit");
		} else if ( recieve_status == -1 ){
			puts("There was an error");
		} else {
			puts("Server exited by saying exit");
		}
	}

	//close the socket -- close method w/ socket passed
	close(network_socket);


	
	return 0; 
}

