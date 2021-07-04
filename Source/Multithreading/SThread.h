#pragma once
#include "Common.h"
#include <Windows.h>

class SRunnable
{
public:
	virtual bool Init() { return true; }
	virtual UINT32 Run() = 0;
	virtual void Stop() = 0;
	virtual void Exit() = 0;
};

class SWindowsThread
{
public:
	SWindowsThread() { ThreadHandle = 0; Runnable = 0; };
	~SWindowsThread()
	{
		if (ThreadHandle != 0)
		{
			Kill();
		}
	}

public:
	DWORD Run();

	bool CreateInternal(SRunnable* InRunnable, SString InThreadName)
	{
		Runnable = InRunnable;
		ThreadName = InThreadName;
		ThreadHandle = CreateThread(0, 0, __ThreadProc, this, STACK_SIZE_PARAM_IS_A_RESERVATION | CREATE_SUSPENDED, &ThreadID);
		if (ThreadHandle != NULL)
			ResumeThread(ThreadHandle);
		return ThreadHandle != NULL;
	}

	static DWORD __ThreadProc(LPVOID pThis)
	{
		auto* Thread = (SWindowsThread*)pThis;
		return Thread->Run();
	}

private:
	void Kill()
	{
		if (Runnable)
		{
			Runnable->Stop();
		}
		WaitForSingleObject(ThreadHandle, INFINITE);
		CloseHandle(ThreadHandle);
		ThreadHandle = 0;
	}

private:
	HANDLE ThreadHandle;
	SRunnable* Runnable;
	SString ThreadName;
	DWORD ThreadID;
};