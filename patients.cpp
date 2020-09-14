// Written by Ilwoo Kim
// 10/14/2019
#include "patients.hpp"
#include "meds.hpp"
using namespace std;
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <iostream>
#include <vector>

//String Parameterized Constructor
Patients::Patients(std::string name){
	this->name = name; 
}

//String and Vector Parameterized Constructor
Patients::Patients(std::string name, std::vector<Meds> v){
	this->name = name;
	this->medicationVector = v;
}

//Returns the name of the patient's name
string Patients::getname(){
	return this->name;
}

//Returns all of the prescribed medication for patient
string Patients::printListOfMeds(){
	string toReturn = "";
	for (std::vector<Meds>::iterator it = this->medicationVector.begin() ; it != this->medicationVector.end(); ++it){
		toReturn += "     " + (*it).getMedName() + ": " + (*it).getStatus() + "\n";
	}
	return toReturn;
}

//Returns whether or not the given patient is prescribed the medication
bool Patients::containsMedication(std::string name){
	for (std::vector<Meds>::iterator it = this->medicationVector.begin() ; it != this->medicationVector.end(); ++it){
		if(name == (*it).getMedName())
			return true;
	}
	return false; 
}

//Returns the status for the provided medication
string Patients::getMedStatus(std::string name){
	if(this->containsMedication(name) == false){
		return "Patient Is Not Prescribed: " + name + "\n";
	}
	else{
		for (std::vector<Meds>::iterator it = this->medicationVector.begin() ; it != this->medicationVector.end(); ++it){
			if(name == (*it).getMedName())
				return "Patient " + this->name + "'s Status for " + name  + "is: " + (*it).getStatus() + "\n";
		}
	}
}

//Adds a medication to the patient's vector of medication
void Patients::addMedication(Meds medication){
	if(this->containsMedication(medication.getMedName()) == false)
		this->medicationVector.push_back(medication);
}

//Changes the status of a given medication name to the provided status and returns the correct message
string Patients::changeStatus(std::string name, std::string status){
	if(this->containsMedication(name) == false){
		return "Does not contain " + name;
	}
	else{
		for (std::vector<Meds>::iterator it = this->medicationVector.begin() ; it != this->medicationVector.end(); ++it){
			if(name == (*it).getMedName())
				(*it).changeStatus(status);
				return "Changed " + name + " to: " + status;
		}
	}
}

//Inserts this Patient's data into an input file
void Patients::insertPatientData(std::ostream& input_file, std::string unitName){
	input_file << unitName + " " + this->name;
	for (std::vector<Meds>::iterator it = this->medicationVector.begin() ; it != this->medicationVector.end(); ++it){
		input_file << " " + (*it).getMedName() + " " + (*it).getStatus();
	}
	input_file << " $s\n";
}

