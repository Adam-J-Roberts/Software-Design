#include <iostream>
#include <ctime>
#include <string>
#include <stdio.h>
#include "VTime.h"

using namespace std;

// Adds a specified number of seconds onto the time.
void VTime::addSeconds(int a_seconds)
{
	secondsSinceMidnight += a_seconds;
}
void VTime::setCurrentTime()
{
	time_t current = time(0);
	tm* localTime = localtime(&current);
	secondsSinceMidnight = localTime->tm_hour*3600 + localTime->tm_min*60 + localTime->tm_sec;
}
VTime VTime::operator +(int a_seconds)
{
	VTime tmp(secondsSinceMidnight);
	tmp.addSeconds(a_seconds);
	return tmp;
}
int VTime::operator -(VTime x)
{
	return (secondsSinceMidnight - x.secondsSinceMidnight);
}
// Gets the time as an ASCII string
string VTime::getASCIITime()
{
	char buff[128];
	sprintf(buff, "%2.2d:%2.2d:%2.2d", getHours(), getMinutes(), getSeconds() );

	return buff;
}