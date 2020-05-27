#ifndef __ORDER_H_
#define __ORDER_H_

#include "..\Defs.h"
#include <string>
using namespace std;

class Order
{
protected:
	ORD_TYPE type;  //order type: Normal, Frozen, VIP
	REGION Region;  //Region of this order
	int Distance;	//The distance (in meters) between the order location and the resturant 
	int ID;  //Each order has a unique ID (from 1 --> 999 )
	float PriorityIndicator;
	double totalMoney;	//Total order money
	int ArrTime, ServTime, WaitingTime, FinishTime;	//arrival, service start, waiting time, and finish times

	
	//
	// TODO: Add More Data Members As Needed
	//

public:
	Order(int ID, ORD_TYPE r_Type, REGION r_region, int dist, int ArrivalTime);
	virtual ~Order();
	void SetID(int);
	int GetID();
	int GetType() const;
	REGION GetRegion() const;
	string Get_Region() const;
	string Get_Type() const;
	float GetPriorityIndicator() const;
	void SetPriorityIndicator(float PI);
	void SetServTime(int);
	void SetWaitingTime(int);
	int GetArrTime() const;
	int GetServTime() const;
	int GetWaitingTime() const;
	int GetFinishTime() const;
	int GetDistance() const;
	double GetMoney() const;
	void AddMoney(double);

	//
	// TODO: Add More Member Functions As Needed
	//

};

#endif