#include "MyClock.h"

void MyClock::resetClock()
{
	start = steady_clock::now();
}

int MyClock::getClock()
{
	end = steady_clock::now();

	return duration_cast<duration<int>>(end - start).count();
}

