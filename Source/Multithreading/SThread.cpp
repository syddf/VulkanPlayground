#include "SThread.h"

DWORD SWindowsThread::Run()
{
	DWORD ExitCode = 1;
	if (Runnable)
	{
		if (Runnable->Init())
		{
			ExitCode = Runnable->Run();
			Runnable->Exit();
		}
	}
	return ExitCode;
}
