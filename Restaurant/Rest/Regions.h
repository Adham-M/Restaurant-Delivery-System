#pragma once
#include "Order.h"
#include "Motorcycle.h"
#include "..\Generic_DS\Queue.h"
#include "..\PriorityQueue.h"
#include "..\LinkedList.h"
#include "..\GUI\GUI.h"
#include <time.h> 

class Regions
{
private:
	REGION REG;
	int Norm_Count;
	int Froz_Count;
	int VIP_Count;
	int TotalWaitingTime;
	int TotalSevTime;
	int DoneNormOrd, DoneFrozOrd, DoneVipOrd,TotalOrds;
	Queue<Order*> FrozenOrder_Queue;
	PriorityQueue<Order*> VipOrder_Queue;
	LinkedList<Order*> NormalOrder_List;
	int Mc_FastCount, Mc_FrozenCount, Mc_NormalCount;
	int MC_Count;
	int Mc_FastSpeed, Mc_FrozenSpeed, Mc_NormalSpeed;
	PriorityQueue<Motorcycle*> FrozenMotorcycle_Queue;
	PriorityQueue<Motorcycle*> VIPMotorcycle_Queue;
	PriorityQueue<Motorcycle*> NormalMotorcycle_Queue;
	PriorityQueue<Motorcycle*> AssignedNormalMotorcycleQueue;
	PriorityQueue<Motorcycle*> AssignedFrozenMotorcycleQueue;
	PriorityQueue<Motorcycle*> AssignedVIPMotorcycleQueue;
	Queue<Motorcycle*> RecentlyAssignedMCsQueue;
	Queue<Order*> RecentlyServedODsQueue;
	Queue<Motorcycle*> AssignedMCsQueue;
	Queue<Order*> ServedODsQueue;
	LinkedList<Order*> OrdersTobeDeleted;
public:
	Regions(REGION RG, int NS, int FS, int VS, int NC, int FC, int VC);
	Regions();
	int GetNormCount() const;
	int GetFrozCount() const;
	int GetVIPCount() const;
	void AddtoOrderQueue(Order *pOrd);
	void CancelOrder(int id);
	void CreateMotorcycle_Queue();
	void Set_Motorcycles_Speed(int vip, int frz, int nrm);
	void Set_Motorcycles_count(int vip, int frz, int nrm);
	int Getnorm_Motorcycles_count() const;
	int Getfrz_Motorcycles_count() const;
	int Getvip_Motorcycles_count() const;
	void AssignQueuedOrder(int,GUI*);
	bool IsEmpty();
	bool IsNormal(int id);
	bool AllMotorcyclesAvalible();
	void ReciveMotorcycle(int);
	Node<Order*>* SearchNormOrder(int id);
	Order* GetNormOrdPeek();
	void GetRecentlyAssignedMCsQueue(Queue<Motorcycle*>& QM);
	void GetRecentlyServedODsQueue(Queue<Order*>& QO) ;
	void GetAssignedMCsQueue(Queue<Motorcycle*>& QM);
	void GetServedODsQueue(Queue<Order*>& QO);
	int GetNo_DoneVipODs() const;
	int GetNo_DoneNrmODs() const;
	int GetNo_DoneFrzODs() const;
	int GetNoOfDoneOrds() const;
	double GetAvgWaitTime() const;
	double GetAvgServTime() const;
	int GetMCCount() const;
	~Regions();
};

