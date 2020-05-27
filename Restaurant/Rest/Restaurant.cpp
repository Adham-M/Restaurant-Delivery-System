#include <cstdlib>
#include <time.h>
#include <iostream>
using namespace std;

#include "Restaurant.h"


Restaurant::Restaurant()
{
	pGUI = NULL;
	AutoLimit = 0;
	for(int i=0;i<4;i++)
	AutoPromotedCuss[i] = 0;
	//AutoPromotedCus_B = 0;
	//AutoPromotedCus_C = 0;
	//AutoPromotedCus_D = 0;
	AutoPromotedCus= 0;
}



void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();

	switch (mode)
	{
	case MODE_INTR:
	{
		Ineractive_Mode();
		break;
	}
	case MODE_STEP:
	{
		StepbyStep_Mode();
		break;
	}
	case MODE_SLNT:
	{
		Silent_Mode();
		break;
	}
	};
}



//////////////////////////////////  Event handling functions   /////////////////////////////
void Restaurant::AddEvent(Event* pE, int id)	//adds a new event to the queue of events
{
	EventsQueue.enqueue(pE, id);
}

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while (EventsQueue.peekFront(pE))	//as long as there are more events
	{
		if (pE->getEventTime() > CurrentTimeStep)	//no more events at current time
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}
}

void Restaurant::PromoteOrder(int id, int extramoney)
{
	for (int i = 0; i < 4; i++)
	{
		if (RA[i].SearchNormOrder(id) != nullptr)
		{
			Node<Order*>* temp = RA[i].SearchNormOrder(id);
			Order* PromOrd = new Order(temp->getItem()->GetID(), TYPE_VIP, temp->getItem()->GetRegion(), temp->getItem()->GetDistance(), temp->getItem()->GetArrTime());
			PromOrd->AddMoney(temp->getItem()->GetMoney() + extramoney);
			CancelOrder(temp->getItem()->GetID());
			AddOrders(PromOrd);
			break;
		}
	}
	/*else if (B.SearchNormOrder(id) != nullptr)
	{
		Node<Order*>* temp = B.SearchNormOrder(id);
		Order* PromOrd = new Order(temp->getItem()->GetID(), TYPE_VIP, temp->getItem()->GetRegion(), temp->getItem()->GetDistance(), temp->getItem()->GetArrTime());
		PromOrd->AddMoney(temp->getItem()->GetMoney() + extramoney);
		CancelOrder(temp->getItem()->GetID());
		AddOrders(PromOrd);
	}
	else if (C.SearchNormOrder(id) != nullptr)
	{
		Node<Order*>* temp = C.SearchNormOrder(id);
		Order* PromOrd = new Order(temp->getItem()->GetID(), TYPE_VIP, temp->getItem()->GetRegion(), temp->getItem()->GetDistance(), temp->getItem()->GetArrTime());
		PromOrd->AddMoney(temp->getItem()->GetMoney() + extramoney);
		CancelOrder(temp->getItem()->GetID());
		AddOrders(PromOrd);
	}
	else if (D.SearchNormOrder(id) != nullptr)
	{
		Node<Order*>* temp = D.SearchNormOrder(id);
		Order* PromOrd = new Order(temp->getItem()->GetID(), TYPE_VIP, temp->getItem()->GetRegion(), temp->getItem()->GetDistance(), temp->getItem()->GetArrTime());
		PromOrd->AddMoney(temp->getItem()->GetMoney() + extramoney);
		CancelOrder(temp->getItem()->GetID());
		AddOrders(PromOrd);
	}*/
}

void Restaurant::PrintSomeInfoDO() const
{
	pGUI->PrintMultiMessage("Reg(A):   DoneVipOrders(" + to_string(RA[0].GetNo_DoneVipODs() - AutoPromotedCuss[0]) + ")   DoneFrozOrders(" + to_string(RA[0].GetNo_DoneFrzODs()) + ")    DoneNrmOrders(" + to_string(RA[0].GetNo_DoneNrmODs() + AutoPromotedCuss[0]) + ")" + "        Reg(B) : DoneVipOrders(" + to_string(RA[1].GetNo_DoneVipODs() - AutoPromotedCuss[1]) + ")   DoneFrozOrders(" + to_string(RA[1].GetNo_DoneFrzODs()) + ")    DoneNrmOrders(" + to_string(RA[1].GetNo_DoneNrmODs() + AutoPromotedCuss[1]) + ")", 4);
	pGUI->PrintMultiMessage("Reg(C):   DoneVipOrders(" + to_string(RA[2].GetNo_DoneVipODs() - AutoPromotedCuss[2]) + ")   DoneFrozOrders(" + to_string(RA[2].GetNo_DoneFrzODs()) + ")    DoneNrmOrders(" + to_string(RA[2].GetNo_DoneNrmODs() + AutoPromotedCuss[2]) + ")" + "       Reg(D):   DoneVipOrders(" + to_string(RA[3].GetNo_DoneVipODs() - AutoPromotedCuss[3]) + ")   DoneFrozOrders(" + to_string(RA[3].GetNo_DoneFrzODs()) + ")    DoneNrmOrders(" + to_string(RA[3].GetNo_DoneNrmODs() + AutoPromotedCuss[3]) + ")", 5);
}

void Restaurant::GenerateOutputFile()
{
	fstream OutputFile;
	OutputFile.open("OutputFile.txt", std::ofstream::out | std::ofstream::trunc);
	Queue<Order*> ODQ[4], MQ[4];
	//Queue<Order*> ODQA, ODQB, ODQC, ODQD;
	//ODQ[0] = ODQA;	ODQ[1] = ODQB;	ODQ[2] = ODQC;	ODQ[3] = ODQD;
	//Regions* RA;
	//RA[0] = A;	RA[1] = B;	RA[2] = C;	RA[3] = D;

	for (int i = 0; i < 4; i++)
		RA[i].GetServedODsQueue(ODQ[i]);

	int NOD, ON, OF, OV, MCN, MN, MF, MV;
	double AS, AW;
	GetSomeStatistics(NOD, ON, OF, OV, MCN, MN, MF, MV, AW, AS);
	Order *order, *order2, *order3;
	Motorcycle* motor;
	PriorityQueue<Order*> OQ[4], TempOQ[4];
	//PriorityQueue<Order*> OQ_A, OQ_B, OQ_C, OQ_D;
	//OQ[0] = OQ_A;	OQ[1] = OQ_B;	OQ[2] = OQ_C;	OQ[3] = OQ_D;
	int* ind[4] = { 0,0,0,0 };
	char ch[4] = { 'A','B','C','D' };

	for (int i = 0; i < 4; i++)
	{
		while (!ODQ[i].isEmpty())
		{
			ODQ[i].dequeue(order);
			OQ[i].enqueue(order, -order->GetFinishTime());
			ind[i]++;
		}
		while (OQ[i].dequeue(order))
		{
			TempOQ[i].enqueue(order, -order->GetServTime());
			if (OQ[i].peekFront(order2) )
				while (order->GetFinishTime() == order2->GetFinishTime())
				{
					OQ[i].dequeue(order3);
					TempOQ[i].enqueue(order3, -order3->GetServTime());
					OQ[i].peekFront(order2);
					if (!order2)
						break;
				}

			/*if (OQ[i].peekFront(order2))
			{
				if (order->GetFinishTime() == order2->GetFinishTime() && order->GetServTime() > order2->GetServTime())
				{
					OQ[i].dequeue(order2);
					TempOQ[i].enqueue(order2, -order2->GetFinishTime());
					OQ[i].enqueue(order, -order->GetFinishTime());
				}
				else
					TempOQ[i].enqueue(order, -order->GetFinishTime());
			}
			else
				TempOQ[i].enqueue(order, -order->GetFinishTime());*/
			while (TempOQ[i].dequeue(order3))
				MQ[i].enqueue(order3);
			cout << "Done\t";
		}


		if (ind[i])
			OutputFile << "FT" << "\t" << "ID" << "\t" << "AT" << "\t" << "WT" << "\t" << "ST" << "\t\n";

		while (MQ[i].dequeue(order))
			OutputFile << order->GetFinishTime() << "\t" << order->GetID() << "\t" << order->GetArrTime() << "\t" << order->GetWaitingTime() << "\t" << order->GetServTime() << "\t\n";

		OutputFile << "\nRegion " << ch[i] << ":\n";
		OutputFile << "\tOrders: " << RA[i].GetNoOfDoneOrds() << " [Norm:" << RA[i].GetNo_DoneNrmODs() + AutoPromotedCuss[i] << ", Froz:" << RA[i].GetNo_DoneFrzODs() << ", VIP:" << RA[i].GetNo_DoneVipODs() - AutoPromotedCuss[i] << "]\n";
		OutputFile << "\tMotorC: " << RA[i].Getfrz_Motorcycles_count() + RA[i].Getnorm_Motorcycles_count() + RA[i].Getvip_Motorcycles_count() << "  [Norm:" << RA[i].Getnorm_Motorcycles_count() << ", Froz:" << RA[i].Getfrz_Motorcycles_count() << ", VIP:" << RA[i].Getvip_Motorcycles_count() << "]\n";
		OutputFile << "\tAvg Wait = " << RA[i].GetAvgWaitTime() << ",  Avg Serv = " << RA[i].GetAvgServTime() << "\n";

		if (i != 3)
			OutputFile << "----------------------------------------------------------\n\n";
	}
	
	///
	OutputFile << "\n_________________________________________________________________________\n_________________________________________________________________________\n";

	OutputFile << "\nRestaurant:\n";
	OutputFile << "\tOrders: " << NOD << " [Norm:" << ON << ", Froz:" << OF << ", VIP:" << OV << "]\n";
	OutputFile << "\tMotorC: " << MCN << "  [Norm:" << MN << ", Froz:" << MF << ", VIP:" << MV << "]\n";
	OutputFile << "\tAvg Wait = " << AW << ",  Avg Serv = " << AS << "\n";

	OutputFile.close();
}

void Restaurant::GetSomeStatistics(int& NOD, int& ON, int& OF, int& OV, int& MCN, int& MN, int& MF, int& MV, double& AW, double& AS) const
{
	NOD = 0; ON = 0; OF = 0; OV = 0; MCN = 0; MN = 0; MF = 0; MV = 0; AW = 0; AS = 0;
	for (int i = 0; i < 4; i++)
	{
		NOD += RA[i].GetNoOfDoneOrds();
		OF += RA[i].GetNo_DoneFrzODs();
		MCN += RA[i].GetMCCount();
		MN += RA[i].Getnorm_Motorcycles_count();
		MF += RA[i].Getfrz_Motorcycles_count();
		MV += RA[i].Getvip_Motorcycles_count();
		AW += RA[i].GetAvgWaitTime();
		AS += RA[i].GetAvgServTime();
		ON += RA[i].GetNo_DoneNrmODs();
		OV += RA[i].GetNo_DoneVipODs();
	}

	AW /= 4;
	AS /= 4;
	ON += AutoPromotedCus;
	OV -= AutoPromotedCus;
}

void Restaurant::Ineractive_Mode()
{
	Order* pOrd;
	Event* pEv;

	LoadFunction();
	int EvTime = 0;

	pGUI->PrintMessage("Keep clicking to advance to the next time step");
	int CurrentTimeStep = 1;
	//as long as events queue is not empty yet
	while (!EventsQueue.isEmpty() || StayOpen())
	{
		pGUI->waitForClick();
		//print current timestep
		char timestep[10];
		itoa(CurrentTimeStep, timestep, 10);

		ReciveMotorcycle(CurrentTimeStep);

		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step
		//Each event add or remove orders from the GUI 

		AutoPromote(CurrentTimeStep);

		pGUI->PrintMessage(timestep);
		
		pGUI->PrintMultiMessage(PrintSomeInfoSO(), 6);

		AssignOrder(CurrentTimeStep);

		pGUI->PrintMultiMessage(PrintSomeInfoOD(), 2);
		pGUI->PrintMultiMessage(PrintSomeInfoMC(), 3);
		PrintSomeInfoDO();

		pGUI->UpdateInterface();

		CurrentTimeStep++;	//advance timestep
	}

	GenerateOutputFile();

	pGUI->PrintMessage("Generation done, click to END program");

	pGUI->PrintMultiMessage(PrintSomeInfoOD(), 2);
	pGUI->PrintMultiMessage(PrintSomeInfoMC(), 3);
	pGUI->PrintMultiMessage(PrintSomeInfoSO(), 6);
	PrintSomeInfoDO();
	pGUI->waitForClick();

}

void Restaurant::StepbyStep_Mode()
{
	Order* pOrd;
	Event* pEv;

	LoadFunction();
	int EvTime = 0;

	int CurrentTimeStep = 1;
	//as long as events queue is not empty yet
	while (!EventsQueue.isEmpty() || StayOpen())
	{
		//print current timestep
		char timestep[10];
		itoa(CurrentTimeStep, timestep, 10);

		ReciveMotorcycle(CurrentTimeStep);


		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step
										//Each event add or remove orders from the GUI 


		AutoPromote(CurrentTimeStep);

		pGUI->PrintMessage(timestep);
		pGUI->PrintMultiMessage(PrintSomeInfoSO(), 6);

		AssignOrder(CurrentTimeStep);

		pGUI->PrintMultiMessage(PrintSomeInfoOD(), 2);
		pGUI->PrintMultiMessage(PrintSomeInfoMC(), 3);
		PrintSomeInfoDO();

		pGUI->UpdateInterface();

		Sleep(500);
		CurrentTimeStep++;	//advance timestep
	}

	GenerateOutputFile();

	pGUI->PrintMessage("Generation done, click to END program");

	pGUI->PrintMultiMessage(PrintSomeInfoOD(), 2);
	pGUI->PrintMultiMessage(PrintSomeInfoMC(), 3);
	pGUI->PrintMultiMessage(PrintSomeInfoSO(), 6);
	PrintSomeInfoDO();
	pGUI->waitForClick();
}

void Restaurant::Silent_Mode()
{
	Order* pOrd;
	Event* pEv;

	LoadFunction();
	int EvTime = 0;

	int CurrentTimeStep = 1;
	//as long as events queue is not empty yet
	while (!EventsQueue.isEmpty() /*|| !StayOpen()*/ || !RA[0].IsEmpty() || !RA[1].IsEmpty() || !RA[2].IsEmpty() || !RA[3].IsEmpty())
	{

		ReciveMotorcycle(CurrentTimeStep);

		ExecuteEvents(CurrentTimeStep);

		AutoPromote(CurrentTimeStep);

		AssignOrder(CurrentTimeStep);

		CurrentTimeStep++;	//advance timestep
	}
	GenerateOutputFile();
}
////////////////

void Restaurant::LoadFunction()
{
	pGUI->PrintMessage("Enter input file name: ");
	ifstream inputFile(pGUI->GetString());
	int SN, SF, SV;
	int NA[4];// = { 0, 0, 0, 0 };
	int FA[4];// = { 0, 0, 0, 0 };
	int VA[4];// = { 0, 0, 0, 0 };
	//int NB, FB, VB;
	//int NC, FC, VC;
	//int ND, FD, VD;
	int Auto_Limit;
	int EventsNumber;
	char EventType;
	int TS;
	char TYP;
	int ID;
	int Dist;
	double Money;
	char Region;
	int ExMon;
	//while (!inputFile.is_open())
	//{
	//	pGUI->PrintMessage("This file name doesn't exist, try again: ");
	//	inputFile = "InputFile.txt";
	//}
	inputFile >> SN >> SF >> SV;
	for (int i = 0; i < 4; i++)
		inputFile >> NA[i] >> FA[i] >> VA[i];
	inputFile >> Auto_Limit >> EventsNumber;
	for (int i = 0; i < 4; i++)
	{
		RA[i].Set_Motorcycles_Speed(SV, SF, SN);
		RA[i].Set_Motorcycles_count(VA[i], FA[i], NA[i]);
	}
	//A.Set_Motorcycles_Speed(SV, SF, SN);
	//B.Set_Motorcycles_Speed(SV, SF, SN);
	//C.Set_Motorcycles_Speed(SV, SF, SN);
	//D.Set_Motorcycles_Speed(SV, SF, SN);
	//A.Set_Motorcycles_count(VA, FA, NA);
	//B.Set_Motorcycles_count(VB, FB, NB);
	//C.Set_Motorcycles_count(VC, FC, NC);
	//D.Set_Motorcycles_count(VD, FD, ND);
	AutoLimit = Auto_Limit;
	for (int i = 0; i < EventsNumber; i++)
	{
		inputFile >> EventType;
		if (EventType == 'R')
		{
			inputFile >> TS >> TYP >> ID >> Dist >> Money >> Region;
			ORD_TYPE OT;
			REGION REG;
			if (TYP == 'N')
				OT = TYPE_NRM;
			else if (TYP == 'F')
				OT = TYPE_FROZ;
			else if (TYP == 'V')
				OT = TYPE_VIP;

			if (Region == 'A')
				REG = A_REG;
			else if (Region == 'B')
				REG = B_REG;
			else if (Region == 'C')
				REG = C_REG;
			else if (Region == 'D')
				REG = D_REG;

			Event* AE = new ArrivalEvent(TS, ID, OT, REG, Dist, Money);
			AddEvent(AE, ID);
		}
		else if (EventType == 'X')
		{
			inputFile >> TS >> ID;
			Event* AE = new CancellationEvent(TS, ID);
			AddEvent(AE, ID);
		}
		else if (EventType == 'P')
		{
			inputFile >> TS >> ID >> ExMon;
			Event* AE = new PromotionEvent(TS, ID, ExMon);
			AddEvent(AE, ID);
		}
	}
}

bool Restaurant::StayOpen()
{
	bool b = true;
	for (int i = 0; i < 4; i++)
		b = b * RA[i].IsEmpty() * RA[i].AllMotorcyclesAvalible();
	return !b;
}

void Restaurant::AddOrders(Order *pOrd)
{
	for (int i = 0; i < 4; i++)
		if (pOrd->GetRegion() == i)	
			RA[i].AddtoOrderQueue(pOrd);

	//if (pOrd->GetRegion() == A_REG)
	//	A.AddtoOrderQueue(pOrd);
	//else if (pOrd->GetRegion() == B_REG)
	//	B.AddtoOrderQueue(pOrd);
	//else if (pOrd->GetRegion() == C_REG)
	//	C.AddtoOrderQueue(pOrd);
	//else if (pOrd->GetRegion() == D_REG)
	//	D.AddtoOrderQueue(pOrd);

	pGUI->AddOrderForDrawing(pOrd);	//Add order to GUI
}


string Restaurant::PrintSomeInfoMC() const
{
	const char ch[4] = { 'A','B','C','D' };
	string msg = "";
	for (int i = 0; i < 4; i++)
	{
		msg += "Reg " + to_string(ch[i]) + ": MV(" + to_string(RA[i].Getvip_Motorcycles_count()) + ") MF(" + to_string(RA[i].Getfrz_Motorcycles_count()) + ") MN(" + to_string(RA[i].Getnorm_Motorcycles_count()) + ")";
		if (i != 3)
			msg += ",      ";
	}
	//	"     Reg B: MV(" + to_string(B.Getvip_Motorcycles_count()) + ") MF(" + to_string(B.Getfrz_Motorcycles_count()) + ") MN(" + to_string(B.Getnorm_Motorcycles_count()) + "), " +
	//	"     Reg C: MV(" + to_string(C.Getvip_Motorcycles_count()) + ") MF(" + to_string(C.Getfrz_Motorcycles_count()) + ") MN(" + to_string(C.Getnorm_Motorcycles_count()) + "), " +
	//	"     Reg D: MV(" + to_string(D.Getvip_Motorcycles_count()) + ") MF(" + to_string(D.Getfrz_Motorcycles_count()) + ") MN(" + to_string(D.Getnorm_Motorcycles_count()) + ") ";
	return msg;
}

string Restaurant::PrintSomeInfoOD() const
{
	const char ch[4] = { 'A','B','C','D' };
	string msg = "";
	for (int i = 0; i < 4; i++)
	{
		msg = "Reg " + to_string(ch[i]) + ": OV(" + to_string(RA[i].GetVIPCount()) + ") OF(" + to_string(RA[i].GetFrozCount()) + ") ON(" + to_string(RA[i].GetNormCount()) + ")";
		if (i != 3)
			msg += ", ";
	}
		//	"     Reg B: OV(" + to_string(B.GetVIPCount()) + ") OF(" + to_string(B.GetFrozCount()) + ") ON(" + to_string(B.GetNormCount()) + "), " +
		//"     Reg C: OV(" + to_string(C.GetVIPCount()) + ") OF(" + to_string(C.GetFrozCount()) + ") ON(" + to_string(C.GetNormCount()) + "), " +
		//"     Reg D: OV(" + to_string(D.GetVIPCount()) + ") OF(" + to_string(D.GetFrozCount()) + ") ON(" + to_string(D.GetNormCount()) + ")";
	return msg;
}

string Restaurant::PrintSomeInfoSO()
{
	Queue<Motorcycle*>* MCQ;/*, MCQB, MCQC, MCQD;*/
	Queue<Order*> ODQ[4]/*, ODQ[1], ODQ[2], ODQ[3]*/;/* , ODQB, ODQC, ODQD;*/
	for (int i = 0; i < 4; i++)
	{
		RA[i].GetRecentlyAssignedMCsQueue(MCQ[i]);
		RA[i].GetRecentlyServedODsQueue(ODQ[i]);
	}
	/*A.GetRecentlyAssignedMCsQueue(MCQA);
	A.GetRecentlyServedODsQueue(ODQA);
	B.GetRecentlyAssignedMCsQueue(MCQB);
	B.GetRecentlyServedODsQueue(ODQB);
	C.GetRecentlyAssignedMCsQueue(MCQC);
	C.GetRecentlyServedODsQueue(ODQC);
	D.GetRecentlyAssignedMCsQueue(MCQD);
	D.GetRecentlyServedODsQueue(ODQD);*/
	string msg = "";
	Order* order;
	Motorcycle* motor;

	for (int i = 0; i < 4; i++)
	{
		while (!ODQ[i].isEmpty() && !MCQ[i].isEmpty())
		{
			MCQ[i].dequeue(motor);
			ODQ[i].dequeue(order);
			msg += "R(" + order->Get_Region() + ") " + motor->Get_Type() + to_string(motor->GetID()) + "(" + order->Get_Type() + to_string(order->GetID()) + ")  ";
		}
	}
	/*while (!ODQB.isEmpty() && !MCQB.isEmpty())
	{
		ODQB.dequeue(order);
		MCQB.dequeue(motor);
		msg = msg + "R(" + order->Get_Region() + ") " + motor->Get_Type() + to_string(motor->GetID()) + "(" + order->Get_Type() + to_string(order->GetID()) + ")  ";
	}
	while (!ODQC.isEmpty() && !MCQC.isEmpty())
	{
		ODQC.dequeue(order);
		MCQC.dequeue(motor);
		msg = msg + "R(" + order->Get_Region() + ") " + motor->Get_Type() + to_string(motor->GetID()) + "(" + order->Get_Type() + to_string(order->GetID()) + ")  ";
	}
	while (!ODQD.isEmpty() && !MCQD.isEmpty())
	{
		ODQD.dequeue(order);
		MCQD.dequeue(motor);
		msg = msg + "R(" + order->Get_Region() + ") " + motor->Get_Type() + to_string(motor->GetID()) + "(" + order->Get_Type() + to_string(order->GetID()) + ")  ";
	}*/
	return msg;
}

void Restaurant::CancelOrder(int id)
{
	for (int i = 0; i < 4; i++)
	{
		if (RA[i].IsNormal(id))
		{
			RA[i].CancelOrder(id);
			pGUI->DeleteOrder(id);
			break;
		}
	}
	/*else if (B.IsNormal(id))
	{
		B.CancelOrder(id);
		pGUI->DeleteOrder(id);
	}
	else if (C.IsNormal(id))
	{
		C.CancelOrder(id);
		pGUI->DeleteOrder(id);
	}
	else if (D.IsNormal(id))
	{
		D.CancelOrder(id);
		pGUI->DeleteOrder(id);
	}*/
}

void Restaurant::AssignOrder(int CurrentTimeStep)
{
	for (int i = 0; i < 4; i++)
		RA[i].AssignQueuedOrder(CurrentTimeStep, pGUI);
	//B.AssignQueuedOrder(CurrentTimeStep, pGUI);
	//C.AssignQueuedOrder(CurrentTimeStep, pGUI);
	//D.AssignQueuedOrder(CurrentTimeStep, pGUI);
}

void Restaurant::ReciveMotorcycle(int CurrentTimeStep)
{
	for (int i = 0; i < 4; i++)
		RA[i].ReciveMotorcycle(CurrentTimeStep);
	//B.ReciveMotorcycle(CurrentTimeStep);
	//C.ReciveMotorcycle(CurrentTimeStep);
	//D.ReciveMotorcycle(CurrentTimeStep);
}

void Restaurant::AutoPromote(int CurrentTimeStep)
{
	for (int i = 0; i < 4; i++) 
	{
		while (RA[i].GetNormOrdPeek())
		{
			if ((CurrentTimeStep - (RA[i].GetNormOrdPeek()->GetArrTime())) >= AutoLimit)
			{
				PromoteOrder(RA[i].GetNormOrdPeek()->GetID(), 0);
				AutoPromotedCuss[i]++;
				AutoPromotedCus++;
			}
			else
				break;
		}
	}
	/*while (B.GetNormOrdPeek())
		if ((CurrentTimeStep - (B.GetNormOrdPeek()->GetArrTime())) >= AutoLimit)
		{
			PromoteOrder(B.GetNormOrdPeek()->GetID(), 0);
			AutoPromotedCus_B++;
			AutoPromotedCus++;
		}
		else
			break;

	while (C.GetNormOrdPeek())
		if ((CurrentTimeStep - (C.GetNormOrdPeek()->GetArrTime())) >= AutoLimit)
		{
			PromoteOrder(C.GetNormOrdPeek()->GetID(), 0);
			AutoPromotedCus_C++;
			AutoPromotedCus++;
		}
		else
			break;

	while (D.GetNormOrdPeek())
		if ((CurrentTimeStep - (D.GetNormOrdPeek()->GetArrTime())) >= AutoLimit)
		{
			PromoteOrder(D.GetNormOrdPeek()->GetID(), 0);
			AutoPromotedCus_D++;
			AutoPromotedCus++;
		}
		else
			break;*/
}


Restaurant::~Restaurant()
{
	delete pGUI;
}