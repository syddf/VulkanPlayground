#include "STime.h"

double SWindowsTime::SecondsPerCycle = 0.0;

double SWindowsTime::Init()
{
	LARGE_INTEGER Frequency;
	QueryPerformanceFrequency(&Frequency);
	SecondsPerCycle = 1.0 / Frequency.QuadPart;
	return 0.0;
}

double SWindowsTime::Seconds()
{
	LARGE_INTEGER Time;
	QueryPerformanceCounter(&Time);
	return Time.QuadPart * SecondsPerCycle;
}

SString SWindowsTime::GetSystemTimeString()
{
	SString Res = TEXT("  :  :  ");
	char* Data = (char*)Res.c_str();

	int Year;
	int Month;
	int DayOfWeek;
	int Day;
	int Hour;
	int Min;
	int Sec;
	int MSec;
	SystemTime(Year, Month, DayOfWeek, Day, Hour, Min, Sec, MSec);
	sprintf(Data, TEXT("%02d:%02d:%02d"), Hour, Min, Sec);
	return Res;
}

void SWindowsTime::SystemTime(int & Year, int & Month, int & DayOfWeek, int & Day, int & Hour, int & Min, int & Sec, int & MSec)
{
	SYSTEMTIME st;
	GetLocalTime(&st);

	Year = st.wYear;
	Month = st.wMonth;
	DayOfWeek = st.wDayOfWeek;
	Day = st.wDay;
	Hour = st.wHour;
	Min = st.wMinute;
	Sec = st.wSecond;
	MSec = st.wMilliseconds;
}
