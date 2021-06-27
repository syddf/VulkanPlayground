#include "STime.h"
#include <iostream>
using namespace std;

int main()
{
	STime::Init();
	auto Str = STime::GetSystemTimeString();
	double Time = STime::Seconds();
	for (int i = 0; i < 1e9; i++);
	double Time2 = STime::Seconds();
	double TimeInterval = Time2 - Time;
	return 0;
}