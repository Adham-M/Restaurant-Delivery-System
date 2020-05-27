#include "Regions.h"

Regions::Regions(REGION RG, int NS, int FS, int VS, int NC, int FC, int VC)
{
	REG = RG;
	Mc_NormalSpeed = NS;
	Mc_FrozenSpeed = FS;
	Mc_FastSpeed = VS;
	Mc_NormalCount = NC;
	Mc_FrozenCount = FC;
	Mc_FastCount = VC;
	Norm_Count = 0;
	VIP_Count = 0;
	Froz_Count = 0;
	TotalSevTime = 0;
	TotalWaitingTime = 0;
	DoneNormOrd = 0;
	DoneFrozOrd = 0;
	DoneVipOrd = 0;
}

Regions::Regions()
{
	Norm_Count = 0;
	VIP_Count = 0;
	Froz_Count = 0;
	TotalSevTime = 0;
	TotalWaitingTime = 0;
	DoneNormOrd = 0;
	DoneFrozOrd = 0;
	DoneVipOrd = 0;
	TotalOrds = 0;
}

int Regions::GetNo_DoneVipODs() const
{
	return DoneVipOrd;
}

int Regions::GetNo_DoneFrzODs() const
{
	return DoneFrozOrd;
}

int Regions::GetNo_DoneNrmODs() const
{
	return DoneNormOrd;
}

int Regions::GetNormCount() const
{
	return Norm_Count;
}

int Regions::GetFrozCount() const
{
	return Froz_Count;
}

int Regions::GetVIPCount() const
{
	return VIP_Count;
}

void Regions::AddtoOrderQueue(Order *pOrd)
{
	if (pOrd->GetType() == TYPE_NRM)
	{
		NormalOrder_List.InsertEnd(pOrd, pOrd->GetID());
		Norm_Count++;
	}
	else if (pOrd->GetType() == TYPE_VIP)
	{
		VipOrder_Queue.enqueue(pOrd, pOrd->GetPriorityIndicator());
		VIP_Count++;
	}
	else
	{
		FrozenOrder_Queue.enqueue(pOrd);
		Froz_Count++;
	}
}

Order* Regions::GetNormOrdPeek()
{
	Order* temp = nullptr;
	NormalOrder_List.GetTop(temp);
	return temp;
}


void Regions::CreateMotorcycle_Queue()
{
	srand(time(0));
	for (int i = 0; i < Mc_NormalCount; i++)
	{
		Motorcycle* M;
		if (Mc_NormalSpeed > 1)
			M = new Motorcycle(NRM_MC, Mc_NormalSpeed + (rand() % 3) - 1, REG);
		else
			M = new Motorcycle(NRM_MC, Mc_NormalSpeed + (rand() % 2), REG);
		NormalMotorcycle_Queue.enqueue(M, M->GetSpeed());
	}
	for (int i = 0; i < Mc_FrozenCount; i++)
	{
		Motorcycle* M;
		if (Mc_FrozenSpeed > 1)
			M = new Motorcycle(FROZ_MC, Mc_FrozenSpeed + (rand() % 3) - 1, REG);
		else
			M = new Motorcycle(FROZ_MC, Mc_FrozenSpeed + (rand() % 2), REG);
		FrozenMotorcycle_Queue.enqueue(M, M->GetSpeed());
	}
	for (int i = 0; i < Mc_FastCount; i++)
	{
		Motorcycle* M;
		if (Mc_FrozenSpeed > 1)
			M = new Motorcycle(Fast_MC, Mc_FastSpeed + (rand() % 4) - 1, REG);
		else
			M = new Motorcycle(Fast_MC, Mc_FastSpeed + (rand() % 3), REG);
		VIPMotorcycle_Queue.enqueue(M, M->GetSpeed());
	}
}

void Regions::CancelOrder(int id)
{
	if (NormalOrder_List.Delete(NormalOrder_List.SearchID(id)) == true)
		Norm_Count--;
}

bool Regions::IsNormal(int id)
{
	if (NormalOrder_List.SearchID(id) == nullptr)
		return false;
	return true;
}

void Regions::Set_Motorcycles_Speed(int vip, int frz, int nrm)
{
	Mc_FastSpeed = vip;
	Mc_FrozenSpeed = frz;
	Mc_NormalSpeed = nrm;
}

void Regions::Set_Motorcycles_count(int vip, int frz, int nrm)
{
	Mc_FastCount = vip;
	Mc_FrozenCount = frz;
	Mc_NormalCount = nrm;
	CreateMotorcycle_Queue();
}

int Regions::Getvip_Motorcycles_count() const
{
	return Mc_FastCount;
}

int Regions::Getfrz_Motorcycles_count() const
{
	return Mc_FrozenCount;
}

int Regions::Getnorm_Motorcycles_count() const
{
	return Mc_NormalCount;
}

void Regions::AssignQueuedOrder(int CurrentTimeStep, GUI* pGUI)
{
	srand(time(0));
	int TrafficTime = rand() % 3;   //For traffic and damage of motorcycle purposes.
	int DamageTime = rand() % 2;
	Order* temp;
	Motorcycle* motor;
	int time;
	/////////////
	while (!VipOrder_Queue.isEmpty())
	{
		if (!VIPMotorcycle_Queue.isEmpty() || !NormalMotorcycle_Queue.isEmpty() || !FrozenMotorcycle_Queue.isEmpty())
		{
			VipOrder_Queue.dequeue(temp);
			RecentlyServedODsQueue.enqueue(temp);
			ServedODsQueue.enqueue(temp);
			OrdersTobeDeleted.Add(temp);

			if (!VIPMotorcycle_Queue.isEmpty())
			{
				VIPMotorcycle_Queue.dequeue(motor);
				time = CurrentTimeStep + (temp->GetDistance() / motor->GetSpeed()) * 2;
				RecentlyAssignedMCsQueue.enqueue(motor);
				AssignedMCsQueue.enqueue(motor);
				AssignedVIPMotorcycleQueue.enqueue(motor, -time);
				Mc_FastCount--;
			}
			else if (!NormalMotorcycle_Queue.isEmpty())
			{
				NormalMotorcycle_Queue.dequeue(motor);
				time = CurrentTimeStep + (temp->GetDistance() / motor->GetSpeed()) * 2;
				RecentlyAssignedMCsQueue.enqueue(motor);
				AssignedMCsQueue.enqueue(motor);
				AssignedNormalMotorcycleQueue.enqueue(motor, -time);
				Mc_NormalCount--;
			}
			else if (!FrozenMotorcycle_Queue.isEmpty())
			{
				FrozenMotorcycle_Queue.dequeue(motor);
				time = CurrentTimeStep + (temp->GetDistance() / motor->GetSpeed()) * 2;
				RecentlyAssignedMCsQueue.enqueue(motor);
				AssignedMCsQueue.enqueue(motor);
				AssignedFrozenMotorcycleQueue.enqueue(motor, -time);
				Mc_FrozenCount--;
			}
		}
		else
			break;
		motor->SetAvailabilityTime(time + TrafficTime + DamageTime);
		temp->SetWaitingTime(CurrentTimeStep - temp->GetArrTime());
		temp->SetServTime((temp->GetDistance() / motor->GetSpeed()) + TrafficTime + DamageTime);
		TotalSevTime += temp->GetServTime();
		TotalWaitingTime += temp->GetWaitingTime();
		VIP_Count--;
		DoneVipOrd++;
		TotalOrds++;
		pGUI->DeleteOrder(temp);
	}
	////
	while (!NormalOrder_List.IsEmpty())
	{

		if (!NormalMotorcycle_Queue.isEmpty() || !VIPMotorcycle_Queue.isEmpty())
		{
			NormalOrder_List.RemoveFirst(temp);
			RecentlyServedODsQueue.enqueue(temp);
			ServedODsQueue.enqueue(temp);
			OrdersTobeDeleted.Add(temp);

			if (!NormalMotorcycle_Queue.isEmpty())
			{
				NormalMotorcycle_Queue.dequeue(motor);
				time = CurrentTimeStep + (temp->GetDistance() / motor->GetSpeed()) * 2;
				RecentlyAssignedMCsQueue.enqueue(motor);
				AssignedMCsQueue.enqueue(motor);
				AssignedNormalMotorcycleQueue.enqueue(motor, -time);
				Mc_NormalCount--;
			}
			else if (!VIPMotorcycle_Queue.isEmpty())
			{
				VIPMotorcycle_Queue.dequeue(motor);
				time = CurrentTimeStep + (temp->GetDistance() / motor->GetSpeed()) * 2;
				RecentlyAssignedMCsQueue.enqueue(motor);
				AssignedMCsQueue.enqueue(motor);
				AssignedVIPMotorcycleQueue.enqueue(motor, -time);
				Mc_FastCount--;
			}
		}
		else
			break;

		motor->SetAvailabilityTime(time + TrafficTime + DamageTime);
		temp->SetWaitingTime(CurrentTimeStep - temp->GetArrTime());
		temp->SetServTime((temp->GetDistance() / motor->GetSpeed()) + TrafficTime + DamageTime);
		TotalSevTime += temp->GetServTime();
		TotalWaitingTime += temp->GetWaitingTime();
		Norm_Count--;
		DoneNormOrd++;
		TotalOrds++;
		pGUI->DeleteOrder(temp);
	}
	////
	
	while (!FrozenOrder_Queue.isEmpty() && !FrozenMotorcycle_Queue.isEmpty())
	{
		FrozenOrder_Queue.dequeue(temp);
		RecentlyServedODsQueue.enqueue(temp);
		ServedODsQueue.enqueue(temp);
		OrdersTobeDeleted.Add(temp);
		FrozenMotorcycle_Queue.dequeue(motor);
		RecentlyAssignedMCsQueue.enqueue(motor);
		AssignedMCsQueue.enqueue(motor);
		time = CurrentTimeStep + (temp->GetDistance() / motor->GetSpeed()) * 2;
		motor->SetAvailabilityTime(time + TrafficTime + DamageTime);
		AssignedFrozenMotorcycleQueue.enqueue(motor, -time);
		temp->SetWaitingTime(CurrentTimeStep - temp->GetArrTime());
		temp->SetServTime((temp->GetDistance() / motor->GetSpeed()) + TrafficTime + DamageTime);
		TotalSevTime += temp->GetServTime();
		TotalWaitingTime += temp->GetWaitingTime();
		Froz_Count--;
		Mc_FrozenCount--;
		DoneFrozOrd++;
		TotalOrds++;
		pGUI->DeleteOrder(temp);
	}
}

double Regions::GetAvgServTime() const
{
	if (!TotalOrds)
		return 0;
	return (double)TotalSevTime / TotalOrds;
}

double Regions::GetAvgWaitTime() const
{
	if (!TotalOrds)
		return 0;
	return (double)TotalWaitingTime / TotalOrds;
}

int Regions::GetNoOfDoneOrds() const
{
	return TotalOrds;
}

int Regions::GetMCCount() const
{
	return Getfrz_Motorcycles_count() + Getnorm_Motorcycles_count() + Getvip_Motorcycles_count();
}

bool Regions::IsEmpty()
{
	if (VipOrder_Queue.isEmpty() && FrozenOrder_Queue.isEmpty() && NormalOrder_List.IsEmpty())
		return true;
	return false;
}

bool Regions::AllMotorcyclesAvalible()
{
	if (AssignedNormalMotorcycleQueue.isEmpty() && AssignedFrozenMotorcycleQueue.isEmpty() && AssignedVIPMotorcycleQueue.isEmpty())
		return true;
	return false;
}

void Regions::ReciveMotorcycle(int cs)
{
	Motorcycle* motor;
	while (AssignedNormalMotorcycleQueue.peekFront(motor))
	{
		if (motor->GetAvailabilityTime() <= cs)
		{
			AssignedNormalMotorcycleQueue.dequeue(motor);
			NormalMotorcycle_Queue.enqueue(motor, motor->GetSpeed());
			Mc_NormalCount++;
		}
		else
			break;
	}
	while (AssignedFrozenMotorcycleQueue.peekFront(motor))
	{
		if (motor->GetAvailabilityTime() <= cs)
		{
			AssignedFrozenMotorcycleQueue.dequeue(motor);
			FrozenMotorcycle_Queue.enqueue(motor, motor->GetSpeed());
			Mc_FrozenCount++;
		}
		else
			break;
	}
	while (AssignedVIPMotorcycleQueue.peekFront(motor))
	{
		if (motor->GetAvailabilityTime() <= cs)
		{
			AssignedVIPMotorcycleQueue.dequeue(motor);
			VIPMotorcycle_Queue.enqueue(motor, motor->GetSpeed());
			Mc_FastCount++;
		}
		else
			break;
	}
}

Node<Order*>* Regions::SearchNormOrder(int id)
{
	return NormalOrder_List.SearchID(id);
}

void Regions::GetRecentlyAssignedMCsQueue(Queue<Motorcycle*>& QM)
{
	Motorcycle* MC;
	while (RecentlyAssignedMCsQueue.dequeue(MC)) 
		QM.enqueue(MC);
}

void Regions::GetRecentlyServedODsQueue(Queue<Order*>& QO)
{
	Order* OD;
	while (RecentlyServedODsQueue.dequeue(OD))
		QO.enqueue(OD);
}

void Regions::GetAssignedMCsQueue(Queue<Motorcycle*>& QM)
{
	Motorcycle* MC;
	while (AssignedMCsQueue.dequeue(MC))
		QM.enqueue(MC);
}

void Regions::GetServedODsQueue(Queue<Order*>& QO)
{
	Order* OD;
	while (ServedODsQueue.dequeue(OD))
		QO.enqueue(OD);
}

Regions::~Regions()
{
	Motorcycle *temp;
	while (NormalMotorcycle_Queue.dequeue(temp))
		delete temp;

	while (FrozenMotorcycle_Queue.dequeue(temp))
		delete temp;

	while (VIPMotorcycle_Queue.dequeue(temp))
		delete temp;

	OrdersTobeDeleted.Clear();
}