#include "PromotionEvent.h"



PromotionEvent::PromotionEvent(int ts, int id, int ExMon) :Event(ts, id)
{
	TS = ts;
	ID = id;
	ExMoney = ExMon;
}

void PromotionEvent::Execute(Restaurant *pRest)
{
	/*if (pRest->PromoteOrder(ID) != nullptr)
	{
		Node<Order*>* temp = pRest->PromoteOrder(ID);
		Order* PromOrd = new Order(ID, TYPE_VIP, temp->getItem()->GetRegion(), temp->getItem()->GetDistance(), temp->getItem()->GetArrTime());
		PromOrd->AddMoney(temp->getItem()->GetMoney() + ExMoney);
		pRest->CancelOrder(ID);
		pRest->AddOrders(PromOrd);
	}*/
	pRest->PromoteOrder(ID,ExMoney);
}
