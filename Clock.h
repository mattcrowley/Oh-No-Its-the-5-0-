/*  Name: Matt Crowley, Matthew Rotter, Gabe Heuton, Yuhong Bao
	Assignment: Programming Assignment #8
	Class: Computer Science 122
	Date Last Modified: April 22, 2012 
	Description: This is the Clock Class header file, which deals with resetting the time, and converting the time
				 to a value that can be displayed to the screen.
*/


#ifndef CLOCK_H
#define CLOCK_H

#include "Headers.h"

class Clock {
public:
	Clock ();
	~Clock ();

	string convertTime (int player);
	void addTime (double penalty, int player);
	void resetTime ();

private:
	sf::Clock mClock;
	double mTime;
	double mAddedTime;
};

#endif