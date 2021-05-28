#include <iostream>
#include <ctime>
#include <stdio.h>
#include "VTime.h"
using namespace std;

int main()
{
	VTime first(45112);
	VTime second(52243);
	VTime diffenceBetween = second - first;

	VTime current;	
	current.setCurrentTime();

	cout << "The first time is " << first.getASCIITime() << endl;
	cout << "The second time is " << second.getASCIITime() << endl;
	cout << "The differenceBetween time is " << diffenceBetween.getASCIITime() << endl;
	cout << "The current time is: " << current.getASCIITime() << endl;
	
	return 0;
}