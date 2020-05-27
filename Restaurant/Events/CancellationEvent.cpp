#include "CancellationEvent.h"

CancellationEvent::CancellationEvent(int ts, int id) :Event(ts, id)
{
}

void CancellationEvent::Execute(Restaurant *pRest)
{
	pRest->CancelOrder(OrderID);
}