// Written by Ilwoo Kim
// 10/14/2019
#include "patients.cpp"
#include "meds.cpp"
#include "units.cpp"

// Compile with: gcc tcpclient.c -o tcpclient

// Our standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Some types and unix operations
#include <sys/types.h>
#include <unistd.h>

// A sockets library and internet protocol library
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
	// Create a socket
	int client_socket;
	if((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("\n Socket creation error \n");
	}

	// Our client will connect to a server with the following address and port.
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET; // 32-bit IPV4 address
	server_address.sin_port = htons(8037); // convert to the appropriate port number using htons
	server_address.sin_addr.s_addr = htons(INADDR_ANY); // Our ip address, which is localhost using INADDR_ANY

	// Attempt to connect
	// Returns an integer as an error code (zero means everything worked)
	int connection_status;

	// Report back to user if our connection was successful
	if( (connection_status = connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address))) <0 ){
		printf("%d Connection unsuccessful\n", connection_status);
		close(client_socket);
		exit(0);	
	}else{
		printf("Connected successfully\n");
	}

	//After Connection
	//Server-Client Exchange
	///////////////////////////////////////////////////////////////////////////
	char server_response[256];

	recv(client_socket, &server_response, sizeof(server_response), 0);
	printf("%s\n",server_response);

	// Sends Unit name
	int quitInt = 0;
	while(1){
		//First receive message from server and print.
		recv(client_socket, &server_response, sizeof(server_response), 0);
		printf("%s",server_response);
		fgets(server_response, 256, stdin);

		//Concatenate the user response from the server to remove every space with "_"
		strtok(server_response, "\n");
		for(int i = 0; i <strlen(server_response); i++){
        	if(server_response[i] == ' '){
            	server_response[i] = '_';
        	}
    	}
		//Send the user response
		send(client_socket, server_response, sizeof(server_response), 0);

		//If server response is "quit", then quit program.
		if(strcmp(server_response, "quit") == 0){
			printf("Quit!\n");
			quitInt = 1;
			break;
		}
		//If server response is 1, successfully connected to existing Unit
		recv(client_socket, &server_response, sizeof(server_response), 0);
		if(strcmp(server_response, "1") == 0)
		{
			break;
		}
	}

	//Sends commands to Server on what to do with Units
	while(quitInt == 0){
		printf("client>");
		recv(client_socket, &server_response, sizeof(server_response), 0);
		//Receiving message from server
		if(strcmp(server_response, "-1") == 0){
			recv(client_socket, &server_response, sizeof(server_response), 0);
			printf("%s\n", server_response);
		}

		//Handling input to the client
		else{
			printf("%s\n", server_response);
			fgets(server_response, 256, stdin);
			strtok(server_response, "\n");
			
			//Concatenate the input 
			for(int i = 0; i < strlen(server_response); i++){
    		    if(server_response[i] == ' '){
           			 server_response[i] = '_';
				}
    		}

			//Check if input is "quit"
			if(strcmp(server_response, "quit") == 0){
				quitInt = 1;
			}
			send(client_socket, server_response, sizeof(server_response), 0);
		}
	}

	// Then close the socket
	close(client_socket);

	return 1;
}