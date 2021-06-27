#pragma once
#include "Common.h"
#include <Windows.h>

class SEvent
{
public:
	virtual void Create(bool bManualReset) = 0;
	virtual void Trigger() = 0;
	virtual void Reset() = 0;
	virtual bool Wait() = 0;
	virtual bool IsManualReset() = 0;
};

class SWindowsEvent : public SEvent
{
public:
	SWindowsEvent()
	{
		Event = NULL;
	}

	~SWindowsEvent()
	{
		if (Event != NULL)
			CloseHandle(Event);
	}

	void Create(bool bManualReset);
	void Trigger();
	void Reset();
	bool Wait();
	bool IsManualReset() { return ManualReset; }

private:
	HANDLE Event;
	bool ManualReset;
};

class SRecyclableWindowsEvent : public SEvent
{
public:
	SRecyclableWindowsEvent(SEvent* InInnerEvent)
	{
		InnerEvent = InInnerEvent;
	}

	~SRecyclableWindowsEvent()
	{
		InnerEvent = nullptr;
	}

	void Create(bool bManualReset) 
	{
		InnerEvent->Create(bManualReset);
	}

	void Trigger()
	{
		InnerEvent->Trigger();
	}

	virtual void Reset()
	{
		InnerEvent->Reset();
	}

	virtual bool Wait()
	{
		InnerEvent->Wait();
	}

	virtual bool IsManualReset()
	{
		return InnerEvent->IsManualReset();
	}

private:
	SEvent* InnerEvent;
};

class SWindowsEventPool
{

};