#include "Clock.h"
#include "Headers.h"


/* Function: Clock             
   Date Created: April 13, 2012                      
   Date Last Modified: April 13, 2012           
   Description: The constructor for the Clock class.
   Input parameters: NONE
   Returns: NONE
   Preconditions: NONE.                              
   Postconditions: NONE.              
*/

Clock::Clock (){
	mTime = 0.0;
	mAddedTime = 0.0;
}



/* Function: ~Clock            
   Date Created: April 13, 2012                      
   Date Last Modified: April 13, 2012           
   Description: The destructor for the Clock class.
   Input parameters: NONE
   Returns: NONE
   Preconditions: NONE.                              
   Postconditions: NONE.              
*/
Clock::~Clock (){

}



/* Function: convertTime             
   Date Created: April 13, 2012                      
   Date Last Modified: April 13, 2012           
   Description: This function will convert the elapsed time to a string, so that it can print it to the screen later.
				Also includes the added time to the time, which gets added as you hit more objects.
   Input parameters: Takes in the player number, so that the text can be specially set for each player.
   Returns: A string type, containing Player (some number): time elapsed.
   Preconditions: NONE.                              
   Postconditions: NONE.              
*/
string Clock::convertTime (int player){
	mTime = mClock.GetElapsedTime() + mAddedTime; //gets the current time
	
	//converts the double time to a string to print to the screen...
	std::ostringstream strs;
	strs << mTime;
	std::string str;
	if (player == 1)
		str = "Player 1: " + strs.str();
	else
		str = "Player 2: " + strs.str();

	return str;
}



/* Function: addTime             
   Date Created: April 13, 2012                      
   Date Last Modified: April 13, 2012           
   Description: This function adds time to the clock, according to the penalty amount passed in.
   Input parameters: Takes in the penalty in seconds and the player who gets the penalty. Then it prints it
					 to the command prompt.
   Returns: NONE
   Preconditions: That a player has hit an obstacle in their way.                              
   Postconditions: Time has been added.              
*/
void Clock::addTime (double penalty, int player){
	mAddedTime += penalty;
	cout << penalty << " seconds has been added to player " << player << "'s time.\n";
}


/* Function: resetTime             
   Date Created: April 13, 2012                      
   Date Last Modified: April 20, 2012           
   Description: This function resets the time to 0.
   Input parameters: NONE
   Returns: NONE
   Preconditions: NONE                             
   Postconditions: NONE.              
*/

void Clock::resetTime (){
	mClock.Reset();
	mTime = 0.0;
	mAddedTime = 0.0;
}