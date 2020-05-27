#ifndef __ARRIVAL_EVENT_H_
#define __ARRIVAL_EVENT_H_

#include "Event.h"


//class for the arrival event
class ArrivalEvent: public Event
{
	//info about the order ralted to arrival event
	int OrdDistance;	//order distance
	ORD_TYPE OrdType;		//order type: Normal, Frozen, VIP
	REGION OrdRegion;  //Region of this order	                
	double OrdMoney;	//Total order money
	int ArrivalTime;
public:
	ArrivalEvent(int eTime, int oID, ORD_TYPE oType, REGION reg, int dist,double money);
	ArrivalEvent(int eTime, int oID, ORD_TYPE oType, REGION reg);  //just for demo
	//Add more constructors if needed
	void SetMoney(double);
	double GetMoney() const;
	void SetDistance(int d);
	ORD_TYPE GetOrderType() const;
	REGION GetRegion() const;
	virtual void Execute(Restaurant *pRest);	//override execute function

};

#endif