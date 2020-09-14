// Written by Ilwoo Kim
// 10/14/2019
#ifndef meds_hpp
#define meds_hpp

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <iostream>
using namespace std;

class Meds{
private: 
	std::string medName;
	std::string deliveryStatus;

public:
	//String Parameterized Constructor with given medication name.
	Meds(std::string medName);

	//String Parameterized Constructor with givem medication name and status.
	Meds(std::string medName, std::string medStatus);

	//Returns the medication name
	string getMedName();

	//Returns the medication status
	string getStatus();

	//Changes the medication status to the provided status
	void changeStatus(std::string status);
};

#endif
