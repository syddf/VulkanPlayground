#include "STime.h"
#include "SProcess.h"
#include <iostream>
#include <mutex>
using namespace std;

std::mutex mut;
class SSimpleRunnable : public SRunnable
{
public:
	SSimpleRunnable(SString InName)
	{
		Name = InName;
	}

	SString Name;
	virtual bool Init() { return true; }
	virtual UINT32 Run()
	{
		for (int i = 0; i < 100; i++)
		{
			mut.lock();
			cout << "[SimpleRunnable] " << Name << " count : " << std::to_string(i)<< endl;
			mut.unlock();
		}
		return 0;
	}
	virtual void Stop()
	{

	}
	virtual void Exit()
	{
		mut.lock();
		cout << "[SimpleRunnable] " << Name << " Exit." << endl;
		mut.unlock();
	}
};

int main()
{
	/*
	  --  Test Time
	STime::Init();
	auto Str = STime::GetSystemTimeString();
	double Time = STime::Seconds();
	for (int i = 0; i < 1e9; i++);
	double Time2 = STime::Seconds();
	double TimeInterval = Time2 - Time;
	*/
	SSimpleRunnable* Runnable1 = new SSimpleRunnable("Runnable1");
	SSimpleRunnable* Runnable2 = new SSimpleRunnable("Runnable2");

	auto* Thread1 = SWindowsProcess::CreateThread(Runnable1, "Thread1");
	auto* Thread2 = SWindowsProcess::CreateThread(Runnable2, "Thread2");
	delete Thread1;
	delete Thread2;
	return 0;
}