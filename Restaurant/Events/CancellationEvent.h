#pragma once
#include "Event.h"
#include "..\Rest\Order.h"
#include "..\Generic_DS\Queue.h"
#include "..\Rest\Restaurant.h"

class CancellationEvent:public Event
{
public:
	CancellationEvent(int ts,int id);
	//void CancelOrder(Queue<Order*> NormalOrderQue,const int& ID);
	virtual void Execute(Restaurant *pRest);

};

