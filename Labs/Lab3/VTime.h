//#pragma once
#include <string>
using namespace std;

class VTime
{
public:

	// Constructor for this class.  We allow the user to initially set the stime or it will be set to zero.
	VTime(int a_secondSinceMidnight = 0)
	{
		secondsSinceMidnight = a_secondSinceMidnight;
	}
	// Accessor functions.
	void setCurrentTime();
	int getHours()
	{
		return (secondsSinceMidnight/3600);
	}
	int getMinutes()
	{
		return ((secondsSinceMidnight%3600)/60);
	}
	int getSeconds()
	{
		return ((secondsSinceMidnight%3600)%60);
	}
	void setHours(int a_hours)
	{
		secondsSinceMidnight = a_hours*3600 + getMinutes()*60 + getSeconds();
	}
	void setMinutes(int a_minutes)
	{
		secondsSinceMidnight = getHours()*3600 + a_minutes*60 + getSeconds();
	}
	void setSeconds(int a_seconds)
	{
		secondsSinceMidnight = getHours()*3600 + getMinutes()*60 + a_seconds;
	}
	// A function to add a specified number of seconds to the time.
	void addSeconds(int a_seconds);

	// Plus operator to add seconds onto the time.
	VTime operator +(int a_seconds);

	// minus operator to subtract
	int operator -(VTime x);

	// Gets the time as an ASCII string.
	string getASCIITime();

private:

	int secondsSinceMidnight;

};