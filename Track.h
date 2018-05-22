/*  Name: Matt Crowley, Matthew Rotter, Gabe Heuton, Yuhong Bao
	Assignment: Programming Assignment #8
	Class: Computer Science 122
	Date Last Modified: April 22, 2012 
	Description: This is the Track Class header file, the Track class handles the obstacles that the player is supposed
				 to avoid. 
*/


#ifndef TRACK_H
#define TRACK_H

#include "Headers.h"
#include "Car.h"

class Track {
public:
	Track ();
	~Track ();

	bool loadImage (string smallImage, string largeImage);
	void genRandomTrack (double divider);
	bool checkCollisionWithTrack (Car player);
	void checkOutOfBounds (double divider);
	double getMinimumYValue ();
	void setTrackRandomRow (int spriteNum, double divider);
	void determineXandYObstacles (double &x, double &y, double divider, int spriteNum, int ranObstacleConfig);
	void drawObstacles (sf::RenderWindow &App);
	void moveObstacles ();

private:
	//something here to store created track
	sf::Image mSmall, mLarge;
	sf::Sprite mTrackSprite[8]; //max number of tracks on screen at once.
	bool mTrackEnds; //false if survival mode, true if racing mode

};

#endif