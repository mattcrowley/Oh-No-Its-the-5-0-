#include "Headers.h"
#include "Collision.h"
#include "Game.h"


/* Function: Game             
   Date Created: April 13, 2012                      
   Date Last Modified: April 13, 2012           
   Description: This is the constructor for the Game class.
   Input parameters: NONE
   Returns: NONE
   Preconditions: NONE.                              
   Postconditions: NONE.              
*/

Game::Game (){
	mTime = 0.0;
	p1CarChoice = "";
	p2CarChoice = "";
}



/* Function: ~Game             
   Date Created: April 13, 2012                      
   Date Last Modified: April 13, 2012           
   Description: This is the destructor for the Game class.
   Input parameters: NONE
   Returns: NONE
   Preconditions: NONE.                              
   Postconditions: NONE.              
*/
Game::~Game (){

}

/* Function: initPlayers             
   Date Created: April 13, 2012                      
   Date Last Modified: April 16, 2012           
   Description: This function will set up some basic things needed to initialize the players, such as loading the images
				necessary for the car sprites, as well as setting the cars initial positions, and the timer's position.
   Input parameters: NONE
   Returns: Returns a 1 if failed to find an image, or 0 if it was successfully loaded.
   Preconditions: NONE.                              
   Postconditions: NONE.              
*/

int Game::initPlayers (){
	if (!P1.mCar.setImage(p1CarChoice) || !P2.mCar.setImage(p2CarChoice))
		return 1;

	P1.mCar.setPosition(170, 500);
	P2.mCar.setPosition(600, 500);
	
	//set the timers positions
	P1.mTimer.SetPosition(150, 600);
	P2.mTimer.SetPosition(550, 600);

	P1.mTotalLives.SetPosition (200, 650);
	P2.mTotalLives.SetPosition (600, 650);

	if (!P1.mTrack.loadImage ("racing sprites/resized/1cone_118x80.PNG", "racing sprites/resized/barrel_120x76.PNG"))
		return 1; //error loading files
	P1.mTrack.genRandomTrack(395.0 - P1.mCar.getSprite().GetSize().x);
	
	if (!P2.mTrack.loadImage ("racing sprites/resized/1cone_118x80.PNG", "racing sprites/resized/barrel_120x76.PNG"))
		return 1; //error loading files
	P2.mTrack.genRandomTrack(395.0);

	return 0;
}



/* Function: showMenu             
   Date Created: April 13, 2012                      
   Date Last Modified: April 20, 2012           
   Description: This function handles calling the menus. It will first call a function to show a splash screen, then
				it will show the other menus, depending on what the user enters in the main menu function call.
   Input parameters: NONE
   Returns: Returns the character the user of the program entered, which corresponds to the mode that the user wants,
			which was gotten only if the user chose Play on the main menu. Otherwise it returns a null character,
			which is tested for in the function that calls this one.
   Preconditions: NONE.                              
   Postconditions: NONE.              
*/

char Game::showMenu (){
	char choice = '\0', mode = '\0';

	showSplashScreen ();

	while (choice != 'P' && choice != 'Q'){
		choice = showMainMenu (); //shows menu, gets the choice of one of 3 characters the user enters

		if (choice == 'P'){ //play game, show mode screen.
			mode = showModeMenu ();
			showCarSelectScreen ();
		}
		else if (choice == 'V'){ //show instructions, then loop back to main menu...
			showInstructionsScreen ();
			
		}
		else if (choice == 'Q'){
			//don't really need to do anything here...
		}
	}
	return mode;
}



/* Function: showSplashScreen             
   Date Created: April 13, 2012                      
   Date Last Modified: April 20, 2012           
   Description: This function shows the splash screen to prompt the user of the program to enter any
				key to proceed to the main menu.
   Input parameters: NONE
   Returns: NONE
   Preconditions: NONE.                              
   Postconditions: That any key has been pressed.              
*/

void Game::showSplashScreen (){
	sf::RenderWindow Screen(sf::VideoMode(800, 700, 32), "Oh No! Here's 5-0!");
	
	Screen.SetPosition(0, 0); //sets position of window to top left
	sf::Image image;
	if (!image.LoadFromFile("racing sprites/PNG/splash.PNG"))
	{
	}

	sf::Sprite background (image);
	background.SetPosition(0.0, 0.0);

	while (Screen.IsOpened()){
		sf::Event Event;

		while (Screen.GetEvent(Event)){
			if (Event.Type == sf::Event::KeyPressed){ //if any key was pressed...
				Screen.Close();
			}
		}
		Screen.Clear();

		Screen.Draw(background);

		Screen.Display();
	}

}


/* Function: showMainMenu             
   Date Created: April 13, 2012                      
   Date Last Modified: April 20, 2012           
   Description: This function shows the main menu. It has three choices, play game, view instructions, and exit.
   Input parameters: NONE
   Returns: Returns the character choice of P for play, V for view instructions, or E for exit. 
   Preconditions: NONE.                              
   Postconditions: That a P, V, or E was returned.              
*/

char Game::showMainMenu (){
	sf::RenderWindow Screen(sf::VideoMode(800, 700, 32), "Main Menu");
	char choice;

	Screen.SetPosition(0, 0); //sets position of window to top left
	sf::Image background;
	if (!background.LoadFromFile("racing sprites/PNG/main menu.PNG")){

	}

	sf::Sprite backSprite (background);
	backSprite.SetPosition (0.0, 0.0);

	while (Screen.IsOpened ()){
		sf::Event Event;

		while (Screen.GetEvent(Event)){
			if (Event.Type == sf::Event::KeyPressed){
				if (Event.Key.Code == sf::Key::P){
					choice = 'P';
					Screen.Close ();			
				}
				if (Event.Key.Code == sf::Key::V){
					choice = 'V';
					Screen.Close ();			
				}
				if (Event.Key.Code == sf::Key::Q){
					choice = 'Q';
					Screen.Close ();			
				}
			}
		}
		Screen.Clear();

		Screen.Draw (backSprite);
		Screen.Display();
	}
	return choice;
}


/* Function: showInstructionsScreen              
   Date Created: April 13, 2012                      
   Date Last Modified: April 20, 2012           
   Description: This function will show the instruction menu. It will tell you what controls are used to control the cars.
   Input parameters: NONE
   Returns: NONE
   Preconditions: That the user entered 'V' on the main menu screen.                              
   Postconditions: NONE.              
*/

void Game::showInstructionsScreen (){
	sf::RenderWindow Screen(sf::VideoMode(800, 700, 32), "Instructions");
	
	Screen.SetPosition(0.0, 0.0); //sets position of window to top left

	sf::Image InstructionsImage;
	if (!InstructionsImage.LoadFromFile("racing sprites/PNG/controls.PNG")){

	}

	sf::Sprite InstructionsSprite (InstructionsImage);
	InstructionsSprite.SetPosition(0.0, 0.0);

	while (Screen.IsOpened ()){
		sf::Event Event;

		while (Screen.GetEvent (Event)){
			if (Event.Type == sf::Event::KeyPressed)
				Screen.Close();
		}

		Screen.Draw (InstructionsSprite);

		Screen.Display();
	}
}


/* Function: showModeMenu             
   Date Created: April 13, 2012                      
   Date Last Modified: April 20, 2012           
   Description: This function will show the Mode select screen. It asks the user to choose which type of mode they
				want.
   Input parameters: NONE
   Returns: Returns a character that corresponds to the mode that the user wanted.
   Preconditions: That play was selected on the main menu.                              
   Postconditions: R or S was returned.              
*/

char Game::showModeMenu (){
	sf::RenderWindow Screen(sf::VideoMode(800, 700, 32), "Choose a mode");
	char choice;
	
	Screen.SetPosition(0, 0); //sets position of window to top left
	sf::Image im;
	
	if (!im.LoadFromFile ("racing sprites/PNG/game slect.PNG")){

	}

	sf::Sprite sprite (im);
	sprite.SetPosition (0.0, 0.0);

	while (Screen.IsOpened ()){
		sf::Event Event;

		while (Screen.GetEvent (Event)){
			if (Event.Type == sf::Event::KeyPressed){
				if (Event.Key.Code == sf::Key::R){
					choice = 'R';
					Screen.Close();
				}
				if (Event.Key.Code == sf::Key::S){
					choice = 'S';
					Screen.Close();

				}
			}
		}
		Screen.Clear();

		Screen.Draw (sprite);
		Screen.Display ();
	}

	return choice;
}


/* Function: showCarSelectScreen             
   Date Created: April 13, 2012                      
   Date Last Modified: April 20, 2012           
   Description: This function will prompt the two players to choose the cars they want. It starts with asking
				player 1 which car he wants, then after 1-4 has been entered, it asks player 2 which car he
				wants. Allows both players to choose the same car.
   Input parameters: NONE
   Returns: NONE
   Preconditions: That Play was selected on the main menu.                              
   Postconditions: That two car filenames were stored in the proper variables in the Game class.              
*/

void Game::showCarSelectScreen (){
	sf::RenderWindow Screen(sf::VideoMode(800, 700, 32), "Choose a car");
	
	Screen.SetPosition(0, 0); //sets position of window to top left

	sf::String message1, message2, instr;
	sf::Image im1;
	if (!im1.LoadFromFile ("racing sprites/PNG/car select p1.PNG")){
	}

	sf::Sprite sprite (im1);
	sprite.SetPosition (0.0, 0.0);

	while (Screen.IsOpened ()){
		sf::Event Event;

		while (Screen.GetEvent (Event)){
			if (Event.Type == sf::Event::KeyPressed){
				if (Event.Key.Code == sf::Key::Num1){
					if (p1CarChoice == "") //p1 still not chosen car...
						p1CarChoice = "racing sprites/red/resized/red, no dam_47x80.PNG";
					else{
						p2CarChoice = "racing sprites/red/resized/red, no dam_47x80.PNG";
						Screen.Close();
					}
				}
				if (Event.Key.Code == sf::Key::Num2){
					if (p1CarChoice == "") //p1 still not chosen car...
						p1CarChoice = "racing sprites/blue/resized/blue, no dam_47x80.PNG";
					else{
						p2CarChoice = "racing sprites/blue/resized/blue, no dam_47x80.PNG";
						Screen.Close();
					}
				}
				if (Event.Key.Code == sf::Key::Num3){
					if (p1CarChoice == "") //p1 still not chosen car...
						p1CarChoice = "racing sprites/yellow/resized/yellow no dam_47x80.PNG";
					else{
						p2CarChoice = "racing sprites/yellow/resized/yellow no dam_47x80.PNG";
						Screen.Close();
					}

				}
				if (Event.Key.Code == sf::Key::Num4){
					if (p1CarChoice == "") //p1 still not chosen car...
						p1CarChoice = "racing sprites/green/resized/green no dam_47x80.PNG";
					else{
						p2CarChoice = "racing sprites/green/resized/green no dam_47x80.PNG";
						Screen.Close();
					}

				}
			}
		}

		Screen.Clear();

		if (p1CarChoice != ""){
			if (!im1.LoadFromFile ("racing sprites/PNG/car select p2.PNG")){
			}
			sprite.SetImage(im1);
		}
		
		Screen.Draw (sprite);
		
		Screen.Display ();
	}

}



/* Function: playGame              
   Date Created: April 13, 2012                      
   Date Last Modified: April 20, 2012           
   Description: This function handles calling the functions to play the game.
   Input parameters: NONE
   Returns: NONE
   Preconditions: NONE.                              
   Postconditions: NONE.              
*/
int Game::playGame (){
	int retValue;
	char mode;
	
	do{
		//resets the images to be nothing, for future loops
		p1CarChoice = "";
		p2CarChoice = "";
		
		//resets color of text for the lives after multiple games
		P1.mLives = 3;
		P1.mTotalLives.SetColor (sf::Color::White);
		P2.mLives = 3;
		P2.mTotalLives.SetColor (sf::Color::White);

		mode = showMenu ();

		if (mode == 'R'){ //racing mode
			retValue = raceMode ();
		}
		else if (mode == 'S'){ //survival mode
			retValue = survivalMode ();
		}
		else {//no mode chosen...
			retValue = -1;
		}
	} while (retValue != -1 && retValue != 1);

	return retValue;
}



/* Function: survivalMode             
   Date Created: April 13, 2012                      
   Date Last Modified: April 22, 2012           
   Description: This function handles the survival mode of the game. It will exit once all lives of one player is gone. 
   Input parameters: NONE
   Returns: 1 if unsuccessfully exited, 0 if successfully exited.
   Preconditions: The user entered a S on the mode select screen.                              
   Postconditions: NONE.              
*/
int Game::survivalMode (){
	sf::RenderWindow App(sf::VideoMode(800, 700, 32), "Oh No! Here's 5-0! - Survival!!!!!!"); 

	App.SetPosition(0, 0); //sets position of window to top left

	//will place icon in top left of the window created
	sf::Image ic;
	if (!ic.LoadFromFile("testIcon.png")) //change this to anything
		return 1;

	App.SetIcon(128, 128, ic.GetPixelsPtr()); //length of pic, width, then some other variable that is useless
	//end icon stuff


	if (initPlayers() == 1)
		return 1;

	//resets timers from navigating the menus
	P1.mClock.resetTime ();
	P2.mClock.resetTime ();

	// Start game loop
	while (App.IsOpened())
    {
		P1.mTrack.checkOutOfBounds(395.0 - P1.mCar.getSprite().GetSize().x);
		P2.mTrack.checkOutOfBounds(395.0);

		//set the text of both players timers to the correct times
		P1.mTimer.SetText(P1.mClock.convertTime(1));
		P2.mTimer.SetText(P2.mClock.convertTime(2));


		// Process events
        sf::Event Event;
       	const sf::Input& i = App.GetInput(); //better than Event? - yes, gets multiple key presses at once

		while (App.GetEvent(Event))
        {
            // Close window : exit
            if (Event.Type == sf::Event::Closed)
                App.Close();
        }
		
		//move player1's car
		if (!P1.mTrack.checkCollisionWithTrack(P1.mCar)) //if no collision with the track and car1...
			P1.mCar.moveCar(i, 1);
		else{
			P1.mClock.addTime(3, 1); //add 3 seconds to the clock
			P1.subtractLife(); //subtract a life
			if (!P1.mCar.changeImage (P1.mLives))
				return 1; //could not change image.
		}

		//move player2's car
		if (!P2.mTrack.checkCollisionWithTrack(P2.mCar)) //if no collision with the track and car2...
			P2.mCar.moveCar(i, 2);
		else{
			P2.mClock.addTime(3, 2); //add 3 seconds to the clock
			P2.subtractLife(); //subtract a life
			if (!P2.mCar.changeImage (P2.mLives))
				return 1; //could not change image.
		}

		//move the pieces of track
		P1.mTrack.moveObstacles();
		P2.mTrack.moveObstacles();

		//show lives
		P1.mTotalLives.SetText(P1.showLives());
		P2.mTotalLives.SetText(P2.showLives());


        // Clear the screen (fill it with black color)
        App.Clear();

		App.Draw(P1.mTimer); //draw player 1 timer to screen
		App.Draw(P2.mTimer); //draw player 2 timer to screen
		App.Draw(P1.mTotalLives);
		App.Draw(P2.mTotalLives);

        App.Draw(sf::Shape::Line(395, 0, 395, 700, 2, sf::Color::Red)); //draws barrier between the two cars

		App.Draw(P1.mCar.getSprite());
		App.Draw(P2.mCar.getSprite());
		
		P1.mTrack.drawObstacles(App);
		P2.mTrack.drawObstacles(App);

         //Display window contents on screen
        App.Display();

		if (P1.areLivesGone() || P2.areLivesGone() ){ //exits the game for survival rules.
			sf::Sleep(2);
			//show end game screen, based on who won...
			App.Close();
			showGameOverScreen();
		}
    }

	return 0;
}



/* Function: raceMode             
   Date Created: April 13, 2012                      
   Date Last Modified: April 22, 2012           
   Description: This function handles the racing mode of the game, it will exit when all lives of one player are
				gone, or when timer reaches 60 seconds.
   Input parameters: NONE
   Returns: 1 if unsuccessfully exited, 0 if successfully exited.
   Preconditions: A S was entered on the mode select screen.                              
   Postconditions: NONE.              
*/
int Game::raceMode (){
	sf::RenderWindow App(sf::VideoMode(800, 700, 32), "Oh No! Here's 5-0! - Racing for 60 seconds!!!"); 
	sf::Clock c;

	App.SetPosition(0, 0); //sets position of window to top left

	//will place icon in top left of the window created
	sf::Image ic;
	if (!ic.LoadFromFile("testIcon.png")) //change this to anything
		return 1;

	App.SetIcon(128, 128, ic.GetPixelsPtr()); //length of pic, width, then some other variable that is useless
	//end icon stuff


	if (initPlayers() == 1)
		return 1;


	//resets timers from navigating the menus
	c.Reset(); 
	P1.mClock.resetTime ();
	P2.mClock.resetTime ();

	// Start game loop
	while (App.IsOpened())
    {
		P1.mTrack.checkOutOfBounds(395.0 - P1.mCar.getSprite().GetSize().x);
		P2.mTrack.checkOutOfBounds(395.0);

		mTime = c.GetElapsedTime(); //sets default timer
		
		//set the text of both players timers to the correct times
		P1.mTimer.SetText(P1.mClock.convertTime(1));
		P2.mTimer.SetText(P2.mClock.convertTime(2));


		// Process events
        sf::Event Event;
       	const sf::Input& i = App.GetInput(); //better than Event? - yes, gets multiple key presses at once

		while (App.GetEvent(Event))
        {
            // Close window : exit
            if (Event.Type == sf::Event::Closed)
                App.Close();
        }
		
		//move player1's car
		if (!P1.mTrack.checkCollisionWithTrack(P1.mCar)) //if no collision with the track and car1...
			P1.mCar.moveCar(i, 1);
		else{
			P1.mClock.addTime(3, 1); //add 3 seconds to the clock
			P1.subtractLife(); //subtract a life
			if (!P1.mCar.changeImage (P1.mLives))
				return 1; //could not change image.
		}

		//move player2's car
		if (!P2.mTrack.checkCollisionWithTrack(P2.mCar)) //if no collision with the track and car2...
			P2.mCar.moveCar(i, 2);
		else{
			P2.mClock.addTime(3, 2); //add 3 seconds to the clock
			P2.subtractLife(); //subtract a life
			if (!P2.mCar.changeImage (P2.mLives))
				return 1; //could not change image.
		}

		//move the pieces of track
		P1.mTrack.moveObstacles();
		P2.mTrack.moveObstacles();

		//show lives
		P1.mTotalLives.SetText(P1.showLives());
		P2.mTotalLives.SetText(P2.showLives());


        // Clear the screen (fill it with black color)
        App.Clear();

		App.Draw(P1.mCar.getSprite());
		App.Draw(P2.mCar.getSprite());
		
		P1.mTrack.drawObstacles(App);
		P2.mTrack.drawObstacles(App);

		App.Draw(P1.mTimer); //draw player 1 timer to screen
		App.Draw(P2.mTimer); //draw player 2 timer to screen
		App.Draw(P1.mTotalLives);
		App.Draw(P2.mTotalLives);

        App.Draw(sf::Shape::Line(395, 0, 395, 700, 2, sf::Color::Red)); //draws barrier between the two cars


         //Display window contents on screen
        App.Display();
		
		if (mTime >= 60.0 || P1.areLivesGone() || P2.areLivesGone()){ //exits the game for racing rules.
			sf::Sleep(2);
			//show end game screen, based on who won...
			App.Close();
			showGameOverScreen();
		}
    }

	return 0;
}



/* Function: showGameOverScreen             
   Date Created: April 22, 2012                      
   Date Last Modified: April 22, 2012           
   Description: This function shows the game over screen, and tells the users who won, if anyone won, or if was a draw.
   Input parameters: NONE
   Returns: NONE
   Preconditions: That the game is over.                              
   Postconditions: NONE.              
*/

void Game::showGameOverScreen (){
	int winner = determineWinner();

	sf::RenderWindow Screen(sf::VideoMode(800, 700, 32), "Game Over!");
	
	Screen.SetPosition(0.0, 0.0); //sets position of window to top left

	sf::Image EndImage;
	sf::Clock c;
	c.Reset();

	if (winner == 1){ //winner is 1st player...
		if (!EndImage.LoadFromFile("racing sprites/PNG/player 1 win.PNG")){

		}
	}
	
	else if (winner == 2){ //winner is second player...
		if (!EndImage.LoadFromFile("racing sprites/PNG/player 2 win.PNG")){

		}
	}
	
	else if (winner == 0){ //draw...
		if (!EndImage.LoadFromFile("racing sprites/PNG/tie.PNG")){

		}
	}

	sf::Sprite EndSprite (EndImage);
	EndSprite.SetPosition(0.0, 0.0);

	while (Screen.IsOpened ()){
		sf::Event Event;

		while (Screen.GetEvent (Event)){
			if (Event.Type == sf::Event::KeyPressed && c.GetElapsedTime() >= 2.0) //key pressed and 2 seconds elapsed...
				Screen.Close();
		}
		
		Screen.Clear();

		Screen.Draw (EndSprite);

		Screen.Display();
	}

}


/* Function: determineWinner             
   Date Created: April 22, 2012                      
   Date Last Modified: April 22, 2012           
   Description: This function compares the two players info, and determines who won, or if it was a draw.
   Input parameters: NONE
   Returns: Returns a 0 if the players have the same number of lives, returns a 1 if player 1 has more lives than player 2,
			or returns a 2 if player 2 has more lives than player 1.
   Preconditions: That the game has ended.                              
   Postconditions: A winner has been determined.              
*/

int Game::determineWinner (){
	int result = 0; //sets initially as a draw

	if (P1.mLives > P2.mLives) //player 1 has more lives than player 2...
		result = 1; //player 1 wins!!!!
	
	else if (P2.mLives > P1.mLives) //player 2 has more lives than player 1...
		result = 2; //player 2 wins!

	return result;
}