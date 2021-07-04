#pragma once
#include "Common.h"
#include <Windows.h>
#include "SThread.h"

struct SWindowsProcess
{
	static SWindowsThread* CreateThread(SRunnable* Runable, SString ThreadName);
};