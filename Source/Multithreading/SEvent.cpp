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
