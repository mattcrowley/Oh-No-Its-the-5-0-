#include "Car.h"
#include "Headers.h"


/* Function: Car              
   Date Created: April 13, 2012                      
   Date Last Modified: April 13, 2012           
   Description: This is the constructor for the Car class.
   Input parameters: NONE
   Returns: NONE
   Preconditions: NONE.                              
   Postconditions: NONE.              
*/

Car::Car (){

}




/* Function: ~Car            
   Date Created: April 13, 2012                      
   Date Last Modified: April 13, 2012           
   Description: This is the destructor for the Car class.
   Input parameters: NONE
   Returns: NONE
   Preconditions: NONE.                              
   Postconditions: NONE.              
*/
Car::~Car (){

}




/* Function: setImage             
   Date Created: April 13, 2012                      
   Date Last Modified: April 22, 2012           
   Description: This function will load the car's image from a file that was passed in. If the file could not be loaded,
				then it will return false, otherwise it will set the sprite to that image.
   Input parameters: The filename for the image to load.
   Returns: Returns false if setting the image failed, or true if it was successful.
   Preconditions: NONE.                              
   Postconditions: NONE.              
*/
bool Car::setImage (string filename){
	if (!mCarImage.LoadFromFile(filename))
		return false;
	else{
		mCarSprite.SetImage (mCarImage);
		setCarColor (filename); //sets the color of the car
		return true;
	}

}


/* Function: changeImage            
   Date Created: April 22, 2012                      
   Date Last Modified: April 22, 2012           
   Description: This function will change the image of the car according to how many lives are left, showing the damage
				to the car.
   Input parameters: Number of lives for the player.
   Returns: Returns whether the image changing was a success or not.
   Preconditions: That a collision occurred to change the image.                              
   Postconditions: NONE.              
*/
bool Car::changeImage (int lives){
	if (lives == 2){ //2 lives left
		if (mCarColor == "Red")
			return setImage ("racing sprites/red/resized/red dam 2_47x80.PNG");
		else if (mCarColor == "Blue")
			return setImage ("racing sprites/blue/resized/blue dam 2_47x80.PNG");
		else if (mCarColor == "Yellow")
			return setImage ("racing sprites/yellow/resized/yellow dam 2_47x80.PNG");
		else if (mCarColor == "Green")
			return setImage ("racing sprites/green/resized/green dam 2_47x80.PNG");

	}
	else if (lives == 1){ //1 life left
		if (mCarColor == "Red")
			return setImage ("racing sprites/red/resized/red dam 3_47x80.PNG");
		else if (mCarColor == "Blue")
			return setImage ("racing sprites/blue/resized/blue dam 3_46x80.PNG");
		else if (mCarColor == "Yellow")
			return setImage ("racing sprites/yellow/resized/yellow dam 3_47x80.PNG");
		else if (mCarColor == "Green")
			return setImage ("racing sprites/green/resized/green dam 3_46x80.PNG");

	}
	else if (lives == 0){ //no lives left...
		if (mCarColor == "Red")
			return setImage ("racing sprites/red/resized/red splode_50x80.PNG");
		else if (mCarColor == "Blue")
			return setImage ("racing sprites/blue/resized/blue splode_51x80.PNG");
		else if (mCarColor == "Yellow")
			return setImage ("racing sprites/yellow/resized/yellow splode_50x80.PNG");
		else if (mCarColor == "Green")
			return setImage ("racing sprites/green/resized/green splode_50x80.PNG");

	}

	return true;
}


/* Function: moveCar             
   Date Created: April 13, 2012                      
   Date Last Modified: April 13, 2012           
   Description: This function will handle both cars moving. It will call the proper functions in order to move the car
				according to what key was pressed.
   Input parameters: Takes in the input that the user entered, and which player was the one who called this function,
					 since the two players have different keys they need to press.
   Returns: NONE
   Preconditions: NONE.                              
   Postconditions: NONE.              
*/
void Car::moveCar (const sf::Input &input, int player){ 
	if (player == 1 && input.IsKeyDown(sf::Key::W))
		moveUp();
	if (player == 1 && input.IsKeyDown(sf::Key::S))
		moveDown();
	if (player == 1 && input.IsKeyDown(sf::Key::A))
		moveLeft(0.0);
	if (player == 1 && input.IsKeyDown(sf::Key::D))
		moveRight(395.0 - mCarSprite.GetSize().x);
	
	if (player == 2 && input.IsKeyDown(sf::Key::Up))
		moveUp();
	if (player == 2 && input.IsKeyDown(sf::Key::Down))
		moveDown();
	if (player == 2 && input.IsKeyDown(sf::Key::Left))
		moveLeft(395.0);
	if (player == 2 && input.IsKeyDown(sf::Key::Right))
		moveRight(0.0);
}



/* Function: moveUp             
   Date Created: April 13, 2012                      
   Date Last Modified: April 13, 2012           
   Description: This function will move the car up, if the player entered the correct key.
   Input parameters: NONE
   Returns: NONE
   Preconditions: That Up/W was pressed.                              
   Postconditions: NONE.              
*/
void Car::moveUp (){
	sf::Vector2f test = mCarSprite.GetPosition();
	
	if (test.y > 0){
		mCarSprite.Move(0, -1);
		test.y += -1;
		mCarSprite.SetY(test.y);
	}
}



/* Function: moveDown             
   Date Created: April 13, 2012                      
   Date Last Modified: April 13, 2012           
   Description: This function will move the car down, and tests for the boundaries of the screen.
   Input parameters: NONE
   Returns: NONE
   Preconditions: That Down/S was pressed.                              
   Postconditions: NONE.              
*/
void Car::moveDown (){
	sf::Vector2f test = mCarSprite.GetPosition();
	sf::Vector2f size = mCarSprite.GetSize();
	
	if (test.y < (600 - size.y)){
		mCarSprite.Move(0, 1);
		test.y += 1;
		mCarSprite.SetY(test.y);
	}
}



/* Function: moveLeft             
   Date Created: April 13, 2012                      
   Date Last Modified: April 13, 2012           
   Description: This function will move the car to the left.
   Input parameters: Takes in the barrier, since the barriers change depending on whether the first or second player's car
					 was the one that moved left.
   Returns: NONE
   Preconditions: That Left/A was pressed.                              
   Postconditions: NONE.              
*/
void Car::moveLeft (double barrier){
	sf::Vector2f test = mCarSprite.GetPosition();
	
	if (test.x > barrier){
		mCarSprite.Move(-1, 0);
		test.x += -1;
		mCarSprite.SetX(test.x);
	}	
}



/* Function: moveRight             
   Date Created: April 13, 2012                      
   Date Last Modified: April 13, 2012           
   Description: This function will move the car to the right.
   Input parameters: Takes in a double value for the x-location of the barrier. The cars have different barriers to their
					 respective rights.
   Returns: NONE
   Preconditions: That Right/D was pressed.                              
   Postconditions: NONE.              
*/
void Car::moveRight (double barrier){
	sf::Vector2f test = mCarSprite.GetPosition();
	sf::Vector2f size = mCarSprite.GetSize();
	
	if (barrier == 0.0) //fixes issues with player2's car
		barrier = 800 - size.x;

	if (test.x < barrier){
		mCarSprite.Move(1, 0);
		test.x += 1;
		mCarSprite.SetX(test.x);
	}
}




/* Function: getSprite             
   Date Created: April 13, 2012                      
   Date Last Modified: April 13, 2012           
   Description: This function will return the car sprite, in order to draw it to the screen.
   Input parameters: NONE
   Returns: The car sprite.
   Preconditions: NONE.                              
   Postconditions: NONE.              
*/
sf::Sprite Car::getSprite (){
	return mCarSprite;
}



/* Function: setPosition            
   Date Created: April 13, 2012                      
   Date Last Modified: April 13, 2012           
   Description: This function will set the position of the car to the passed in values of x and y.
   Input parameters: The x and y position
   Returns: NONE
   Preconditions: NONE.                              
   Postconditions: NONE.              
*/
void Car::setPosition (double x, double y){
	mCarSprite.SetX(x);
	mCarSprite.SetY(y);
}


/* Function: setCarColor             
   Date Created: April 22, 2012                      
   Date Last Modified: April 22, 2012           
   Description: This function will set the private car color variable of the Car class to a certain color depending on 
				the filename passed in. This will later help change the image of the car in other functions.
   Input parameters: The filename that was used to initialize the car.
   Returns: NONE
   Preconditions: That the car image was loaded successfully.                              
   Postconditions: mCarColor has been set to red, blue, yellow, or green.              
*/

void Car::setCarColor  (string filename){
	if (filename == "racing sprites/red/resized/red, no dam_47x80.PNG")
		mCarColor = "Red";
	else if (filename == "racing sprites/blue/resized/blue, no dam_47x80.PNG")
		mCarColor = "Blue";
	else if (filename == "racing sprites/yellow/resized/yellow no dam_47x80.PNG")
		mCarColor = "Yellow";
	else if (filename == "racing sprites/green/resized/green no dam_47x80.PNG")
		mCarColor = "Green";
}
