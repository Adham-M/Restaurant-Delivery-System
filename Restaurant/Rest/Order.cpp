#include "Order.h"

Order::Order(int id, ORD_TYPE r_Type, REGION r_region, int dist, int arrivalTime)
{
	SetID(id);
	type = r_Type;
	Region = r_region;
	Distance = dist;
	ArrTime = arrivalTime;
	PriorityIndicator = 1;
	totalMoney = 0;
}

Order::~Order()
{
}

string Order::Get_Region() const
{
	if (Region == A_REG)
		return "A";
	else if (Region == B_REG)
		return "B";
	else if (Region == C_REG)
		return "C";
	else
		return "D";
}

string Order::Get_Type() const
{
	if (type == TYPE_VIP)
		return "V";
	else if (type == TYPE_NRM)
		return "N";
	else
		return "F";
}

void Order::SetID(int id)
{
	ID = (id > 0 && id < 1000) ? id : 0;	//1<ID<999
}

int Order::GetID()
{
	return ID;
}

int Order::GetType() const
{
	return type;
}

REGION Order::GetRegion() const
{
	return Region;
}

float Order::GetPriorityIndicator() const
{
	return PriorityIndicator;
}

void Order::SetPriorityIndicator(float PI)
{
	PriorityIndicator = PI;
}

int Order::GetDistance() const
{
	return Distance;
}

double Order::GetMoney() const
{
	return totalMoney;
}

void Order::AddMoney(double AM)
{
	totalMoney = (AM > 0) ? totalMoney + AM : totalMoney;
}


void Order::SetWaitingTime(int wt)
{
	WaitingTime = wt;
}
void Order::SetServTime(int st)
{
	ServTime = st;
	FinishTime = ArrTime + ServTime + WaitingTime;
}
int Order::GetArrTime() const
{
	return ArrTime;
}
int Order::GetWaitingTime() const
{
	return WaitingTime;
}
int Order::GetServTime() const
{
	return ServTime;
}
int Order::GetFinishTime() const
{
	return FinishTime;
}