#include "Headers.h"
#include "Player.h"

/* Function: Player             
   Date Created: April 13, 2012                      
   Date Last Modified: April 13, 2012           
   Description: This is the constructor for the Player class.
   Input parameters: NONE
   Returns: NONE
   Preconditions: NONE.                              
   Postconditions: NONE.              
*/

Player::Player (){
	mLives = 3;
}

/* Function: ~Player             
   Date Created: April 13, 2012                      
   Date Last Modified: April 13, 2012           
   Description: This is the destructor for the Player class.
   Input parameters: NONE
   Returns: NONE
   Preconditions: NONE.                              
   Postconditions: NONE.              
*/

Player::~Player (){

}



/* Function: showLives             
   Date Created: April 16, 2012                      
   Date Last Modified: April 16, 2012           
   Description: This function will show the current amount of lives that are remaining for the player.
   Input parameters: NONE
   Returns: The string that contains the lives remaining.
   Preconditions: NONE.                              
   Postconditions: NONE.              
*/
string Player::showLives (){
	std::ostringstream strs;
	strs << mLives; //converts int mLives to a string type
	std::string str;

	str = "Lives: " + strs.str();
	return str;
}



/* Function: subtractLife             
   Date Created: April 16, 2012                      
   Date Last Modified: April 16, 2012           
   Description: This function will subtract 1 life from the player's total lives. It will also change the color of
				the text to yellow if 2 lives remain, or red, meaning critical, if 1 life remain.
   Input parameters: NONE
   Returns: NONE
   Preconditions: That a collision has occurred, which means a life has been lost.                              
   Postconditions: NONE.              
*/
void Player::subtractLife(){
	mLives--;
	if (mLives == 2)
		mTotalLives.SetColor(sf::Color::Yellow);
	else if (mLives == 1)
		mTotalLives.SetColor(sf::Color::Red);
}



/* Function: areLivesGone             
   Date Created: April 16, 2012                      
   Date Last Modified: April 16, 2012           
   Description: This function will tell if there are any more lives left.
   Input parameters: NONE
   Returns: Returns true if there are no more lives, or false if there are still lives remaining.
   Preconditions: NONE.                              
   Postconditions: NONE.              
*/
bool Player::areLivesGone (){
	if (this->mLives == 0)
		return true;
	else
		return false;
}