/*  Name: Matt Crowley, Matthew Rotter, Gabe Heuton, Yuhong Bao
	Assignment: Programming Assignment #8
	Class: Computer Science 122
	Date Last Modified: April 22, 2012 
	Description: This is the Game class, it handles showing the menus, and playing the game. It declares two Player
				 objects, since two players are the ones playing the game.
*/


#ifndef GAME_H
#define GAME_H

#include "Headers.h"
#include "Track.h"
#include "Clock.h"
#include "Car.h"
#include "Player.h"

class Game {
public:
	Game ();
	~Game ();

	int initPlayers ();

	char showMenu ();
	void showSplashScreen ();
	char showMainMenu ();
	void showInstructionsScreen ();
	char showModeMenu ();
	void showCarSelectScreen ();

	int playGame ();
	int survivalMode ();
	int raceMode ();

	void showGameOverScreen ();
	int determineWinner ();

private:
	Player P1, P2;
	string p1CarChoice, p2CarChoice;
	double mTime;

};

#endif