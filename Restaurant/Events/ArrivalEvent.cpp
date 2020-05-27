#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"


ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType, REGION reg, int dist, double money) :Event(eTime, oID)
{
	OrdType = oType;
	OrdRegion = reg;
	SetDistance(dist);
	SetMoney(money);
	ArrivalTime = eTime;
}

ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType, REGION reg) :Event(eTime, oID)
{
	OrdType = oType;
	OrdRegion = reg;
	ArrivalTime = eTime;
}

void ArrivalEvent::SetDistance(int d)
{
	OrdDistance = d > 0 ? d : 0;
}

void ArrivalEvent::SetMoney(double M)
{
	OrdMoney = (M > 0) ? M : 0;
}

double ArrivalEvent::GetMoney() const
{
	return OrdMoney;
}

ORD_TYPE ArrivalEvent::GetOrderType() const
{
	return OrdType;
}

REGION ArrivalEvent::GetRegion() const
{
	return OrdRegion;
}

void ArrivalEvent::Execute(Restaurant* pRest)
{
	//This function should create an order and fills its data 
	// Then adds it to normal, frozen, or VIP order lists that you will create in phase1
	//Order


	Order* pOrd = new Order(OrderID, OrdType, OrdRegion, OrdDistance, ArrivalTime);
	if (OrdType == TYPE_VIP)
	{
		float PI = OrdMoney - OrdDistance * 2 - ArrivalTime * 10;
		pOrd->SetPriorityIndicator(PI);
	}
	pOrd->AddMoney(OrdMoney);
	pRest->AddOrders(pOrd);

}
