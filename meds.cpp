// Written by Ilwoo Kim
// 10/14/2019
#include "meds.hpp"
using namespace std;

//String Parameterized Constructor
Meds::Meds(std::string medName){
	this->medName = medName;
	this->deliveryStatus = "new_order";
}

//String Parameterized Constructor with givem medication name and status.
Meds::Meds(std::string medName, std::string medStatus){
	this->medName = medName;
	this->deliveryStatus = medStatus;
}

//Returns the medication name
string Meds::getMedName(){
	return this->medName;
}

//Returns the medication status
string Meds::getStatus(){
	return this->deliveryStatus;
}

//Changes the medication status to the provided status
void Meds::changeStatus(std::string status){
	this->deliveryStatus = status;
}