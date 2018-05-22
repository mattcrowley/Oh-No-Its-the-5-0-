#include "Headers.h"
#include "Track.h"
#include "Collision.h"


/* Function: Track             
   Date Created: April 13, 2012                      
   Date Last Modified: April 13, 2012           
   Description: This is the constructor for the Track class.
   Input parameters: NONE
   Returns: NONE
   Preconditions: NONE.                              
   Postconditions: NONE.              
*/

Track::Track (){

}



/* Function: ~Track             
   Date Created: April 13, 2012                      
   Date Last Modified: April 13, 2012           
   Description: This is the destructor for the Track class.
   Input parameters: NONE
   Returns: NONE
   Preconditions: NONE.                              
   Postconditions: NONE.              
*/
Track::~Track (){
}



/* Function: loadImage             
   Date Created: April 13, 2012                      
   Date Last Modified: April 21, 2012           
   Description: This function will load the two image filenames for the track obstacles. Barrel is the large image,
				cones are the small image.
   Input parameters: Takes in two string filenames, corresponding to the different obstacles.
   Returns: True if the loading was a success, false if could not load the files.
   Preconditions: NONE.                              
   Postconditions: NONE.              
*/
bool Track::loadImage (string smallImage, string largeImage){
	if (!mSmall.LoadFromFile(smallImage) || !mLarge.LoadFromFile(largeImage))
		return false;
	else{
		mSmall.SetSmooth(false);
		mLarge.SetSmooth(false);
		return true;
	}
}



/* Function: genRandomTrack             
   Date Created: April 13, 2012                      
   Date Last Modified: April 21, 2012           
   Description: This function will call another function to generate the random track row of obstacles.
   Input parameters: The divider to pass into another function.
   Returns: NONE
   Preconditions: NONE.                              
   Postconditions: NONE.              
*/
void Track::genRandomTrack (double divider){
	int i = 0, j = 0;

	//now generate random positions for each of the objects...
	for (i = 0, j = 0; i < 4; i++, j+=2){ //4 rows of obstacles...
		//call rand function...
		setTrackRandomRow (j, divider);
	}

}



/* Function: checkCollisionWithTrack             
   Date Created: April 13, 2012                      
   Date Last Modified: April 21, 2012           
   Description: This function will check to see if there was a collision with an obstacle, and if there was,
				then it will send that obstacle out of bounds.
   Input parameters: The car that might have hit an object.
   Returns: True if there was a collision, false if no collision.
   Preconditions: NONE.                              
   Postconditions: NONE.              
*/
bool Track::checkCollisionWithTrack (Car player){ //this should send the obstacle to a new location, out of bounds
	for (int i = 0; i < 8; i++){
		if (Collision::PixelPerfectTest(player.getSprite(), mTrackSprite[i])){ //calls collision checking function
			mTrackSprite[i].SetPosition(mTrackSprite[i].GetPosition().x, 700);
			return true;
		}
	}

	return false;
}



/* Function: checkOutOfBounds             
   Date Created: April 13, 2012                      
   Date Last Modified: April 21, 2012           
   Description: This function will check to see if both images are out of bounds, and if so, will reset their images to
				be a new configuration of obstacles and positions.
   Input parameters: The divider to pass into another function
   Returns: NONE
   Preconditions: NONE.                              
   Postconditions: NONE.              
*/
void Track::checkOutOfBounds (double divider){
	for (int i = 0; i < 8; i++){
		if (i % 2 == 0){
			if (mTrackSprite[i].GetPosition().y > 800 && mTrackSprite[i+1].GetPosition().y > 800){
				setTrackRandomRow (i, divider);
				
				mTrackSprite[i].SetY(getMinimumYValue() - 100); //sets y values to not collide with other objects
				mTrackSprite[i+1].SetY(getMinimumYValue() - 100); //sets y values to not collide with other objects
				
				//converts coordinates to global, instead of local in the open window, so the images do not appear immediately.
				mTrackSprite[i].SetPosition(mTrackSprite[i].GetPosition().x, mTrackSprite[i].TransformToGlobal(mTrackSprite[i].GetPosition()).y);
				mTrackSprite[i+1].SetPosition(mTrackSprite[i+1].GetPosition().x, mTrackSprite[i+1].TransformToGlobal(mTrackSprite[i+1].GetPosition()).y);
			}
		}
	}
}



/* Function: getMinimumYValue             
   Date Created: April 23, 2012                      
   Date Last Modified: April 23, 2012           
   Description: This function checks for the smallest y-value out of all the sprites currently on screen, then returns
				the double y value. Helper function to make sure the obstacles do not display on top of each other.
   Input parameters: NONE.
   Returns: Returns the lowest y-value.
   Preconditions: NONE.                              
   Postconditions: NONE.              
*/
double Track::getMinimumYValue (){
	double minY = mTrackSprite[0].GetSize().y;
	
	for (int i = 0; i < 8; i++){
		if (minY > mTrackSprite[i].GetSize().y) //new minimum
			minY = mTrackSprite[i].GetSize().y;
	}

	return minY;
}

/* Function: setTrackRandomRow              
   Date Created: April 20, 2012                      
   Date Last Modified: April 22, 2012           
   Description: This function will generate a random number between 1 and 8, one for each type of obstacle configuration.
				Then the program will assign the sprites the correct images according to what random number was generated.
				This program only allows 2 obstacles in one row, no more, no less. The comments next to the if statements
				for the random obstacle configuration number generated tells the different options that could be generated.
				Calls a helper function to determine the x and y positions of the first image. Then, at the end of the function
				this function will convert the coordinates to global coordinates, so the images show up farther apart.
   Input parameters: Takes in the spriteNum, which is always even, from 0 to 6, corresponds to the sprite image numbers,
						and example is in row 0, the two image numbers correspond to 0 and 1, this allows the program to
						use the spriteNum and spriteNum+1 when assigning the images. 
					 Also takes in an integer divider, which shows where the boundary is, used to differentiate between
						the two players.
   Returns: NONE
   Preconditions: NONE.                              
   Postconditions: That the row has been generated, and their starting points are not overlapping.              
*/
void Track::setTrackRandomRow (int spriteNum, double divider){
	int ranObstacleConfig = rand () % 8 + 1; //gets 1-8 for each type of track row configuration
	double x = 0.0, y = 0.0;

	if (ranObstacleConfig == 1){ //barrel, space, cones, space
		mTrackSprite[spriteNum].SetImage(mLarge);

		determineXandYObstacles (x, y, divider, spriteNum, ranObstacleConfig);
		mTrackSprite[spriteNum].SetPosition (x, y); 

		mTrackSprite[spriteNum+1].SetImage(mSmall);
		mTrackSprite[spriteNum+1].SetPosition (mTrackSprite[spriteNum].GetSize().x + 75 + x, y);
	}
	else if (ranObstacleConfig == 2){ //cones, space, barrel, space
		mTrackSprite[spriteNum].SetImage(mSmall);

		determineXandYObstacles (x, y, divider, spriteNum, ranObstacleConfig);
		mTrackSprite[spriteNum].SetPosition (x, y); 

		mTrackSprite[spriteNum+1].SetImage(mLarge);
		mTrackSprite[spriteNum+1].SetPosition (mTrackSprite[spriteNum].GetSize().x + 75 + x, y);

	}
	else if (ranObstacleConfig == 3){ //cones, big space, barrel at far end
		mTrackSprite[spriteNum].SetImage(mSmall);

		determineXandYObstacles (x, y, divider, spriteNum, ranObstacleConfig);
		mTrackSprite[spriteNum].SetPosition (x, y); 

		mTrackSprite[spriteNum+1].SetImage(mLarge);
		mTrackSprite[spriteNum+1].SetPosition (395 - mTrackSprite[spriteNum+1].GetSize().x + x, y);

	}
	else if (ranObstacleConfig == 4){ //barrel, big space, cones at far end
		mTrackSprite[spriteNum].SetImage(mLarge);
		
		determineXandYObstacles (x, y, divider, spriteNum, ranObstacleConfig);
		mTrackSprite[spriteNum].SetPosition (x, y); 

		mTrackSprite[spriteNum+1].SetImage(mSmall);
		mTrackSprite[spriteNum+1].SetPosition (395 - mTrackSprite[spriteNum+1].GetSize().x + x, y);

	}
	else if (ranObstacleConfig == 5){ //space, barrel, cones, no space
		mTrackSprite[spriteNum].SetImage(mSmall);
	
		determineXandYObstacles (x, y, divider, spriteNum, ranObstacleConfig);
		mTrackSprite[spriteNum].SetPosition (x, y); 

		mTrackSprite[spriteNum+1].SetImage(mLarge);
		mTrackSprite[spriteNum+1].SetPosition (x - mTrackSprite[spriteNum+1].GetSize().x, y);

	}
	else if (ranObstacleConfig == 6){ //space, cones, barrel, no space
		mTrackSprite[spriteNum].SetImage(mLarge);

		determineXandYObstacles (x, y, divider, spriteNum, ranObstacleConfig);
		mTrackSprite[spriteNum].SetPosition (x, y); 

		mTrackSprite[spriteNum+1].SetImage(mSmall);
		mTrackSprite[spriteNum+1].SetPosition (x - mTrackSprite[spriteNum+1].GetSize().x, y);

	}
	else if (ranObstacleConfig == 7){ //barrel, cones, left over space
		mTrackSprite[spriteNum].SetImage(mLarge);
		
		determineXandYObstacles (x, y, divider, spriteNum, ranObstacleConfig);
		mTrackSprite[spriteNum].SetPosition (x, y); 

		mTrackSprite[spriteNum+1].SetImage(mSmall);
		mTrackSprite[spriteNum+1].SetPosition (x + mTrackSprite[spriteNum].GetSize().x, y);

	}
	else if (ranObstacleConfig == 8){ //cones, barrel, left over space
		mTrackSprite[spriteNum].SetImage(mSmall);

		determineXandYObstacles (x, y, divider, spriteNum, ranObstacleConfig);
		mTrackSprite[spriteNum].SetPosition (x, y); 

		mTrackSprite[spriteNum+1].SetImage(mLarge);
		mTrackSprite[spriteNum+1].SetPosition (x + mTrackSprite[spriteNum].GetSize().x, y);
		

	}

	//converts coordinates to global, instead of local in the open window, so the images do not appear immediately.
	mTrackSprite[spriteNum].SetPosition(mTrackSprite[spriteNum].GetPosition().x, mTrackSprite[spriteNum].TransformToGlobal(mTrackSprite[spriteNum].GetPosition()).y);
	mTrackSprite[spriteNum+1].SetPosition(mTrackSprite[spriteNum+1].GetPosition().x, mTrackSprite[spriteNum+1].TransformToGlobal(mTrackSprite[spriteNum+1].GetPosition()).y);
}



/* Function: determineXandYObstacles             
   Date Created: April 22, 2012                      
   Date Last Modified: April 22, 2012           
   Description: This function is a helper function for the above function. This function helps to generate the x and y values
				for the obstacle's positions. This function uses two different formulas to determine the x values of the
				obstacle, one for the random number 1-4 and 7-8, and the other for numbers 5 and 6. This function was
				created because there was a lot of excess code in the above function, and this cuts down the code
				by many lines. 
   Input parameters: Takes in double x and y as references, so their values are changed in this function.
					 Also takes in the int divider, to determine if player 1's obstacles are being generated, or
						if player 2's are.
					 Also takes in an integer spriteNum, which represents which row is currently being generated, with
						0 meaning row0, 2 meaning row1, 4 meaning row2, and 6 meaning row3. Generates different y values
						depending on which row is generated.
					 Also takes in the integer ranObstacleConfig, which is a random number from 1-8, corresponding to the type
						of obstacle row attempting to be created.
   Returns: NONE 
   Preconditions: That we are trying to generate a row of obstacles.                              
   Postconditions: That x and y have been assigned.              
*/

void Track::determineXandYObstacles (double &x, double &y, double divider, int spriteNum, int ranObstacleConfig){
	if (ranObstacleConfig == 1 || ranObstacleConfig == 2 || ranObstacleConfig == 3 || ranObstacleConfig == 4 || ranObstacleConfig == 7 || ranObstacleConfig == 8 ){ //these obstacles have same x and y values
		if (divider == 395) //player 2
			x = 400.0;
		else //player 1
			x = 0.0;
	}
	else if (ranObstacleConfig == 5 || ranObstacleConfig == 6){
		if (divider == 395) //player 2
			x = 400.0 + divider - mTrackSprite[spriteNum].GetSize().x;
		else //player 1
			x = 0.0 + 395 - mTrackSprite[spriteNum].GetSize().x;
	}

	//now deal with y values...
	if (spriteNum == 0){
		y = 20.0;
	}
	else if (spriteNum == 2){
		y = -70.0;
	}
	else if (spriteNum == 4){
		y = -160.0;
	}
	else if (spriteNum == 6){
		y = -250.0;
	}
}

/* Function: drawObstacles              
   Date Created: April 13, 2012                      
   Date Last Modified: April 20, 2012           
   Description: This function will draw to the passed in window the track sprites.
   Input parameters: A render window, representing the current opened window.
   Returns: NONE
   Preconditions: That the sprites have been initialized.                              
   Postconditions: NONE.              
*/
void Track::drawObstacles (sf::RenderWindow &App){
	for (int i = 0; i < 8; i++){
		App.Draw (mTrackSprite[i]);
	}
}



/* Function: moveObstacles             
   Date Created: April 13, 2012                      
   Date Last Modified: April 21, 2012           
   Description: This function will move all pieces of the track/obstacles.
   Input parameters: NONE
   Returns: NONE
   Preconditions: NONE.                              
   Postconditions: NONE.              
*/
void Track::moveObstacles (){
	for (int i = 0; i < 8; i+=2){
		mTrackSprite[i].Move (0.0, 0.9);
		mTrackSprite[i+1].Move (0.0, 0.9);
	}
}