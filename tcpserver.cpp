// Written by Ilwoo Kim
// 10/14/2019
#include "patients.cpp"
#include "meds.cpp"
#include "units.cpp"

// Compile with: gcc tcpserver.c -o tcpserver
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
#include <vector>

#include <iostream>
#include <fstream>

int main(){

	//Vector containing the Units. 
	std::vector<Units> unitVector;
	unitVector.push_back(Units("ICU"));
	unitVector.push_back(Units("CCU"));
	unitVector.push_back(Units("PICU"));
	unitVector.push_back(Units("PEDI"));
	unitVector.push_back(Units("ER1"));
	unitVector.push_back(Units("ER2"));
	Units curUnit;

	// Create the server socket
	int server_socket;
	
	if((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("\n Socket creation error \n");
	}

	// define the server address format
	struct sockaddr_in server_address;

	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(8037); // 8037 is choosen arbitrarily. Try other ports if this does not work
	server_address.sin_addr.s_addr = htons(INADDR_ANY);
	
	bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
	printf("Server bind()\n");

	listen(server_socket, 1);
 
 	// Integer to hold a potential client socket
	int client_socket;
	client_socket = accept(server_socket, NULL, NULL);

	//After connction established
	//Read in data from txtfile
	//////////////////////////////////////////////////////////////////////////////////
	// Object to read in file 
    fstream file_obj; 
  
    file_obj.open("Data.txt");

    string word;
    string unitName;
    string patientName;
    string medName;
    string medStatus;
    int count = 0;
    bool hasUnit = false;
    int pos = 0;
	
	//Read in data from textfile
    while(file_obj >> word) 
    {
        if(word.compare("$s") == 0){
            count = -1;
        }
        else if(count == 0){
            unitName = word;
            for(std::vector<Units>::size_type i = 0; i != unitVector.size(); i++) {
                if(unitName == unitVector[i].getUnitName().c_str()){
                    hasUnit = true;
                    pos = i;
                    break;
                }
            }
            if(hasUnit == false){
                unitVector.push_back(Units(unitName));
                pos = unitVector.size()-1;
            }
        }
        else if(count == 1){
            patientName = word;
            unitVector[pos].addPatient(patientName);
        }
        else if(count % 2 == 0){
            medName = word; 
            unitVector[pos].addPatientMed(patientName, medName);
        }
        else{
            medStatus = word;
            unitVector[pos].changeStatus(patientName, medName, medStatus);
        }
        count++;

    } 

    file_obj.close();

	//Server-Client exchange
	//////////////////////////////////////////////////////////////////////////////////

	// send a message from the server
	printf("Client has joined: %d\n", server_socket);

	char server_message[256];
	string patient_name, med_name, med_status, message;
	
	send(client_socket, "You have reached the server", 256, 0);	

	// Gets Unit Name.
	int quitInt = 0;
	int containsUnit = 0;
	while(1){
		send(client_socket, "What is your unit name:\n", sizeof(server_message), 0);
		recv(client_socket, &server_message, sizeof(server_message), 0);
		//Check if client wants to "quit"
		if(strcmp(server_message, "quit") == 0){
			printf("Quit!\n");
			quitInt = 1;
			break;
		}
		//Iterate through vector, see if Unit with given name exists.
		for (std::vector<Units>::iterator it = unitVector.begin() ; it != unitVector.end(); ++it){
			if(strcmp(server_message, (*it).getUnitName().c_str()) == 0)
			{
				curUnit = *it;
				containsUnit = 1;
				send(client_socket, "1", 256, 0);	
				printf("Unit: %s has joined!\n", server_message);
				break;
			}
		}
		if(containsUnit == 1)
			break;
		//Keep on receiving response from client
		if(containsUnit == 0){
			send(client_socket, "0", 256, 0);	
		}
	
	}	

	//Client Sends Server on what functions it wants on the Units.
	while(quitInt == 0){
		send(client_socket, "Choose your Option\n   1: Print List Of Patient\n   2: Get Patient Status\n   3: Change Status\n   4: Add Patient\n   5: Add Patient Med \n", 256, 0);
		recv(client_socket, &server_message, 256, 0);
		if(strcmp(server_message, "quit") == 0){
			break;
		}
		//Print List of Patient
		if(strcmp(server_message, "1") == 0){
			send(client_socket, "-1", 256, 0);
			send(client_socket, curUnit.printListOfPatients().c_str(), 256, 0);
		}
		//Get Patient Status
		else if(strcmp(server_message, "2") == 0){
			send(client_socket, "Please Enter Patient Name\n", 256, 0);
			recv(client_socket, &server_message, 256, 0);
			patient_name = server_message;
			send(client_socket, "-1", 256, 0);
			send(client_socket, curUnit.printPatientStatus(patient_name).c_str(), 256, 0);
		}
		//Change Status
		else if(strcmp(server_message, "3") == 0){
			send(client_socket, "Please Enter Patient Name\n", 256, 0);
			recv(client_socket, &server_message, 256, 0);
			patient_name = server_message;
			send(client_socket, "Please Enter Medication Name\n", 256, 0);
			recv(client_socket, &server_message, 256, 0);
			med_name = server_message;
			send(client_socket, "Please Enter Medication Status\n", 256, 0);
			recv(client_socket, &server_message, 256, 0);
			message = curUnit.changeStatus(patient_name, med_name, server_message);
			send(client_socket, "-1", 256, 0);
			send(client_socket, message.c_str(), 256, 0);
			std::cout << message << std::endl;
		}
		//Add Patient
		else if(strcmp(server_message, "4") == 0){
			send(client_socket, "Please Enter Patient Name\n", 256, 0);
			recv(client_socket, &server_message, 256, 0);
			send(client_socket, "-1", 256, 0);
			message = curUnit.addPatient(server_message);
			send(client_socket, message.c_str(), 256, 0);
			std::cout << message << std::endl;
		}
		//Add Patient Med
		else if(strcmp(server_message, "5") == 0){
			send(client_socket, "Please Enter Patient Name\n", 256, 0);
			recv(client_socket, &server_message, 256, 0);
			patient_name = server_message;
			send(client_socket, "Please Enter Medication Name\n", 256, 0);
			recv(client_socket, &server_message, 256, 0);		
			message = curUnit.addPatientMed(patient_name, server_message);
			send(client_socket, "-1", 256, 0);
			send(client_socket, message.c_str(), 256, 0);
			std::cout << message << std::endl;
		}
	}

	// Object to write in file 
    ofstream file_obj2; 
  
    file_obj2.open("Data.txt");

	//Insert data into textfile
    for (std::vector<Units>::iterator it = unitVector.begin() ; it != unitVector.end(); ++it){
       (*it).insertUnitData(file_obj2);
	}
	curUnit.insertUnitData(file_obj2);

	file_obj2.close();


	// Close the socket
	close(server_socket);
	return 1;
}
