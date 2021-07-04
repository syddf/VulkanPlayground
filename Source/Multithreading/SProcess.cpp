#include "SProcess.h"

SWindowsThread* SWindowsProcess::CreateThread(SRunnable * Runnable, SString ThreadName)
{
	SWindowsThread* NewThread = new SWindowsThread();
	if (!NewThread->CreateInternal(Runnable, ThreadName))
	{
		delete NewThread;
		NewThread = nullptr;
	}
	return NewThread;
}
