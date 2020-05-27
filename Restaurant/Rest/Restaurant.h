#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Events\Event.h"
#include "..\Events\ArrivalEvent.h"
#include "..\Events\CancellationEvent.h"
#include "..\PromotionEvent.h"
#include "Regions.h"
#include "Order.h"
#include <fstream>


// it is the maestro of the project
class Restaurant
{
private:
	GUI *pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file
	int AutoLimit;
	//Regions A, B, C, D;
	Regions RA[4];	//creating Regions array of 4 regions		/* = { A, B, C, D };*/
	/*int AutoPromotedCus_A, AutoPromotedCus_B, AutoPromotedCus_C, AutoPromotedCus_D, AutoPromotedCus;*/
	int AutoPromotedCus;
	int AutoPromotedCuss[4];/* = { AutoPromotedCus_A, AutoPromotedCus_B, AutoPromotedCus_C, AutoPromotedCus_D };*/

public:

	Restaurant();
	~Restaurant();
	void AddEvent(Event* pE, int id);	//adds a new event to the queue of events
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void AddOrders(Order* po);	//adds an order to the orders queue
	void CancelOrder(int id);
	string PrintSomeInfoMC() const;
	string PrintSomeInfoOD() const;
	string PrintSomeInfoSO();
	void PrintSomeInfoDO() const;
	void AssignOrder(int CurrentTimeStep);
	void ReciveMotorcycle(int CurrentTimeStep);
	void AutoPromote(int CurrentTimeStep);
	void PromoteOrder(int id, int extramoney);
	void GetSomeStatistics(int&, int&, int&, int&, int&, int&, int&, int&, double&, double&) const;
	bool StayOpen();

	void RunSimulation();
	void Ineractive_Mode();
	void StepbyStep_Mode();
	void Silent_Mode();


	void GenerateOutputFile();
	void LoadFunction();



	//
	// TODO: Add More Member Functions As Needed
	//

};

#endif