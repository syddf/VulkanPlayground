#pragma once
#include "Common.h"
#include <Windows.h>

struct SWindowsTime
{
	static double Init();
	static double SecondsPerCycle;
	static double Seconds();

	static SString GetSystemTimeString();
	static void SystemTime(int& Year, int& Month, int& DayOfWeek, int& Day, int& Hour, int& Min, int& Sec, int& MSec);
};

typedef SWindowsTime STime;