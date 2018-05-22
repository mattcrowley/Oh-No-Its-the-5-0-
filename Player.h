/*  Name: Matt Crowley, Matthew Rotter, Gabe Heuton, Yuhong Bao
	Assignment: Programming Assignment #8
	Class: Computer Science 122
	Date Last Modified: April 22, 2012 
	Description: This is the Player.h file. This class handles all the functions related to the player,
				 such as showing lives, as well as declaring objects of the other classes.
*/

#ifndef PLAYER_H
#define PLAYER_H

#include "Headers.h"
#include "Car.h"
#include "Clock.h"
#include "Track.h"

class Player {
public:
	Player ();
	~Player ();

	string showLives ();
	void subtractLife();
	bool areLivesGone ();

	Car mCar;
	Clock mClock;
	Track mTrack;
	sf::String mTimer;
	int mLives;
	sf::String mTotalLives;

};

#endif