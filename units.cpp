// Written by Ilwoo Kim
// 10/14/2019
#include "units.hpp"
#include "patients.hpp"
#include "meds.hpp"

//Default Constructor
Units::Units(){
}

//String Parameterized Constructor
Units::Units(std::string name){
	this->unitName = name;
}

//String and Vector Parameterized Constructor
Units::Units(std::string name, std::vector<Patients> v){
	this->unitName = name;
	this->patientVector = v;
}

//= operator 
Units & Units::operator=(const Units & other){
	this->unitName = other.unitName;
	this->patientVector = other.patientVector;
	return *this;
}

//Returns the Unit Name
string Units::getUnitName(){
	return this->unitName;
}

//Returns a string of all the names of all patients in the units
string Units::printListOfPatients(){
	string toReturn = "List of Patients: \n";
	for (std::vector<Patients>::iterator it = this->patientVector.begin() ; it != this->patientVector.end(); ++it){
		toReturn = toReturn + (*it).getname() + ", "; 
	}
	toReturn += "\n";
	return toReturn;
}

//Returns a string of all of specified patient's medication names and their status
string Units::printPatientStatus(std::string patientName){
	int containsPatient = 0;
	string toReturn = "Status for " + patientName + ": \n";
	for (std::vector<Patients>::iterator it = this->patientVector.begin() ; it != this->patientVector.end(); ++it){
		if(patientName == (*it).getname()){
			toReturn += (*it).printListOfMeds();
			containsPatient = 1;
		}
	}
	if(containsPatient == 0){
		toReturn = "No Such Patient\n";
	}
	return toReturn;
}

//Changes the status of a given patients' medication to the provided status and returns the correct message
string Units::changeStatus(std::string patientName, std::string medicationName, std::string statusMessage){
	int containsPatient = 0;
	for (std::vector<Patients>::iterator it = this->patientVector.begin() ; it != this->patientVector.end(); ++it){
		if(patientName == (*it).getname()){
			return (*it).changeStatus(medicationName, statusMessage);
			containsPatient = 1;
			
		}
	}
	if(containsPatient == 0)
		return "No Such Patient\n" ;
}

//Returns whether or not given patient name is already in vector
bool Units::containsPatient(string patientName){
	for (std::vector<Patients>::iterator it = this->patientVector.begin() ; it != this->patientVector.end(); ++it){
		if(patientName == (*it).getname()){
			return true;		
		}
	}
	return false;
}

//Adds given patient to the patient vector and returns the correct message
string Units::addPatient(string newPatient){
	if(this->containsPatient(newPatient) == false){
		this->patientVector.push_back(Patients(newPatient));
		return "Added Patient: " + newPatient;		
	}
	return "Patient already exists";
}

//Adds a new medication to the given patient and returns the correct message
string Units::addPatientMed(string patientName, string newMed){
	int containsPatient = 0;
	for (std::vector<Patients>::iterator it = this->patientVector.begin() ; it != this->patientVector.end(); ++it){
		if(patientName == (*it).getname()){
			(*it).addMedication(Meds(newMed));
			containsPatient = 1;
			return "Added: " + newMed + " to Patient: " + patientName;
		}
	}
	if(containsPatient == 0)
		return "Unknown Patient!";
}

//Inserts this Unit's data into an input file
void Units::insertUnitData(std::ostream& input_file){
	for (std::vector<Patients>::iterator it = this->patientVector.begin() ; it != this->patientVector.end(); ++it){
		(*it).insertPatientData(input_file, this->unitName);
	}
}
