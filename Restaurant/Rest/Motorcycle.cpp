#include "Motorcycle.h"


Motorcycle::Motorcycle()
{
}

Motorcycle::Motorcycle(MC_TYPE tp, int sp, REGION r)
{
	sID++;
	ID = sID;
	type = tp;
	speed = sp;
	region = r;
	status = IDLE;
}

int Motorcycle::sID = 0;

void Motorcycle::SetSpeed(int s)
{
	speed = (s > 0) ? s : 1;
}

string Motorcycle::Get_Type() const
{
	if (type == Fast_MC)
		return "V";
	else if (type == NRM_MC)
		return "N";
	else
		return "F";
}

int Motorcycle::GetSpeed() const
{
	return speed;
}


int Motorcycle::GetID() const
{
	return ID;
}

void Motorcycle::SetAvailabilityTime(int t)
{
	availabilityTime = t;
}

int Motorcycle::GetAvailabilityTime() const
{
	return availabilityTime;
}

Motorcycle::~Motorcycle()
{
}
