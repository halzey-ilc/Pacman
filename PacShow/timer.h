#pragma once
// by Timmbaland
#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include <map>

//#include <windows.h>

using namespace std;

template<class SenderClass   >
class Timer
{

public:
	SenderClass* senderClass;

	Timer()
	{
		cout << "Timer class created" << endl;
		instCounter++;
		thisId = instCounter;
	   // timerThread =thread( [this]() { startThread(); } );
	}

	//---
	~Timer()
	{
		//print("Timer class destroy");

	}


	//template< class F>	
	void onTick(SenderClass *_instance, void  (SenderClass::* callback)(int))
	{
		senderClass = _instance;
		callbackArr[thisId] = callback;
	}


	void setInterval(int intrv)
	{		
		if (intrv <= 0) { intrv = 0; }
		tInterval = intrv;
	}

	//---
	int getInterval()
	{
		return tInterval;
	}

	bool isEnable()
	{
		return enable;
	}

	void start()
	{
		if (enable) { return; }
		enable = true;
		timerThread = thread([this]() { startThread(); });
		
		//timerThread = new thread([this]() {startThread(); });
	}

	void stop()
	{
		enable = false;
		tickCounter = 0;
		timerThread.detach();
	 
		//delete timerThread;
	}


private:
	static int instCounter;
	static map<int, void  (SenderClass::*)(int)> callbackArr;
	static map<int, string> callbackArrString;
	thread timerThread;
	int tickCounter = 0;
	int tInterval = 1000; // default 1 sec
	bool enable = false;
	int thisId = 0;

	//---
	void startThread()
	{
		while (enable)
		{			 
			this_thread::sleep_for(chrono::milliseconds(tInterval));
			tickCounter++;
			(senderClass ->*(callbackArr[thisId])) (tickCounter);			
		}
	}




};

template <class C>
int Timer<C>::instCounter = 0;

template<class C>
map<int, void  (C::*)(int)> Timer<C>::callbackArr;

