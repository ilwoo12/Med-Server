// Written by Ilwoo Kim
// 10/14/2019
#ifndef units_hpp
#define units_hpp

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <iostream>
#include <vector>
#include "patients.hpp"

class Units{
private: 
	std::string unitName;
	std::vector<Patients> patientVector;
public:
	//Default Constructor
	Units();

	//String Parameterized Constructor
	Units(std::string name);

	//String and Vector Parameterized Constructor
	Units(std::string name, std::vector<Patients> v);

	//= operator 
    Units & operator=(const Units & other);

	//Returns the Unit Name
	string getUnitName();

	//Returns a string of all the names of all patients in the units
	string printListOfPatients();

	//Returns a string of all of specified patient's medication names and their status
	string printPatientStatus(std::string patientName);

	//Returns whether or not given patient name is already in vector
	bool containsPatient(string patientName);

	//Changes the status of a given patients' medication to the provided status and returns the correct message
	string changeStatus(std::string patientName, std::string medicationName, std::string statusMessage);

	//Adds given patient to the patient vector and returns the correct message
	string addPatient(string newPatient);

	//Adds a new medication to the given patient and returns the correct message
	string addPatientMed(string patientName, string newMed);

	//Inserts this Unit's data into an input file
	void insertUnitData(std::ostream& input_file);
};

#endif
