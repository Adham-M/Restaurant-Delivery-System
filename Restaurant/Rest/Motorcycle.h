#ifndef __MOTORCYCLE_H_
#define __MOTORCYCLE_H_
#include "..\Defs.h"
#include <string>
using namespace std;
#pragma once
class Motorcycle	
{
	static int sID;
	int ID;
	MC_TYPE type;	//for each order type there is a corresponding motorcycle type 
	int speed;		//meters it can move in one clock tick (in one timestep)
	REGION	region;	//region of the motorcycle
	STATUS	status;	//idle or in-service
	int availabilityTime;

public:
	Motorcycle();
	Motorcycle(MC_TYPE tp, int sp, REGION r);
	void SetSpeed(int);
	int GetSpeed() const;
	int GetID() const;
	string Get_Type() const;
	void SetAvailabilityTime(int);
	int GetAvailabilityTime() const;
	virtual ~Motorcycle();
};

#endif