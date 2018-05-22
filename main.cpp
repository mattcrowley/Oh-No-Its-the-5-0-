/*  Name: Matt Crowley, Matthew Rotter, Gabe Heuton, Yuhong Bao
	Assignment: Programming Assignment #8
	Class: Computer Science 122
	Date Last Modified: April 22, 2012 
	Description: This is the main.cpp file. It declares a Game object, and then calls the main calling function,
				 eventually returning whether the termination was a success or failure.
*/

#include "Headers.h"
#include "Game.h"

int main (){
	srand ((unsigned) time(NULL));

	Game g;
	int exit;

	exit = g.playGame();

	return exit;
}

