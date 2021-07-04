#include "SEvent.h"

void SWindowsEvent::Create(bool bManualReset)
{
	Event = CreateEvent(NULL, bManualReset, 0, nullptr);
}

void SWindowsEvent::Trigger()
{
	SetEvent(Event);
}

void SWindowsEvent::Reset()
{
	ResetEvent(Event);
}

bool SWindowsEvent::Wait()
{
	return WaitForSingleObject(Event, INFINITE) == WAIT_OBJECT_0;
}

template<bool bManualReset>
SRecyclableWindowsEvent* SWindowsEventPool<bManualReset>::GetEventFromPool()
{
	SEvent* InnerEvent = nullptr;
	QueueMutex.lock();
	if (!EventQueue.empty())
	{
		InnerEvent = EventQueue.front();
		EventQueue.pop();
	}
	QueueMutex.unlock();
	if (InnerEvent == nullptr)
	{
		InnerEvent = new SWindowsEvent();
		InnerEvent->Create(bManualReset);
	}
	SRecyclableWindowsEvent* ResultEvent = new SRecyclableWindowsEvent(InnerEvent);
	assert(ResultEvent != 0);
	return ResultEvent;
}

template<bool bManualReset>
void SWindowsEventPool<bManualReset>::ReturnEventToPool(SEvent * Event)
{
	SRecyclableWindowsEvent* RecyclableEvent = dynamic_cast<SRecyclableWindowsEvent*>(Event);
	assert(RecyclableEvent != nullptr);
	SEvent* InnerEvent = RecyclableEvent->InnerEvent;
	delete RecyclableEvent;
	RecyclableEvent = 0;
	QueueMutex.lock();
	EventQueue.push(InnerEvent);
	QueueMutex.unlock();
}
