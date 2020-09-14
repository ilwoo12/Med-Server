// Written by Ilwoo Kim
// 10/14/2019
#ifndef patients_hpp
#define patients_hpp
#include "meds.hpp"

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <iostream>
#include <vector>

class Patients{
private: 
	std::string name;
	std::vector<Meds> medicationVector;

public:
	//String Parameterized Constructor
	Patients(std::string name);

	//String and Vector Parameterized Constructor
	Patients(std::string name, std::vector<Meds> v);

	//Returns the name of the patient's name
	string getname();

	//Returns all of the prescribed medication for patient
	string printListOfMeds();

	//Returns whether or not the given patient is prescribed the medication
	bool containsMedication(std::string name);

	//Returns the status for the provided medication
	string getMedStatus(std::string name);

	//Adds a medication to the patient's vector of medication
	void addMedication(Meds medication);

	//Changes the status of a given medication name to the provided status and returns the correct message
	string changeStatus(std::string name, std::string status);

	//Inserts this Patient's data into an input file
	void insertPatientData(std::ostream& input_file, std::string unitName);
};

#endif
