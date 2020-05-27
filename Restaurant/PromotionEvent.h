#pragma once
#include "Events/Event.h"
#include "Rest/Restaurant.h"

class PromotionEvent : public Event
{
	int ExMoney;
	int ID;
	int TS;
public:
	PromotionEvent(int ts, int id, int ExMoney);
	virtual void Execute(Restaurant* pRest);
};

