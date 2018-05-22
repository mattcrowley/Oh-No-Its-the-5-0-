/*  Name: Matt Crowley, Matthew Rotter, Gabe Heuton, Yuhong Bao
	Assignment: Programming Assignment #8
	Class: Computer Science 122
	Date Last Modified: April 22, 2012 
	Description: This is the Car class header file. The Car class handles all functions dealing with the car,
				 and how the car moves.
*/


#ifndef CAR_H
#define CAR_H

#include "Headers.h"

class Car {
public:
	Car ();
	~Car ();

	bool setImage (string filename);
	bool changeImage (int lives);
	void moveCar (const sf::Input &input, int player); //maybe take in Event or Input?
	void moveUp ();
	void moveDown ();
	void moveLeft (double barrier);
	void moveRight (double barrier);

	sf::Sprite getSprite ();
	void setPosition (double x, double y);
	void setCarColor  (string filename);

private:
	sf::Image mCarImage;
	sf::Sprite mCarSprite;
	string mCarColor;

};

#endif