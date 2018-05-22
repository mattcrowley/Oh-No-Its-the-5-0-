*******************************************************************************************************************
Instructions on how to play (Matt Crowley, Matthew Rotter, Gabe Heuton, and Yuhong Bao)'s programming assignment
												8 game.
*******************************************************************************************************************

 

The game is called Oh No! Here's 5-0! It is a car game, where you basically avoid the obstacles, trying to beat
the other player in how many lives you have remaining. Player 1 controls the car with WASD, and player 2 controls
the car with Up/Down/Left/Right, which can be seen in the instructions page. There are 3 lives total for each player.

There are two modes to this game: Racing and Survival. 

Racing is where you want to try to end up with the most lives left at the end of 60 seconds. The game ends 
once 60 seconds have passed, and then the game over screen is shown, with the winning player.

Survival is where you race endlessly, until one player runs out of lives. 

There are menus for the main screen, with a nice splash screen, a main menu image, the instructions page, as
well as the winner's image. These are included with the zip file that has all the code.




*********************************************
Instructions on how to set up the project.
*********************************************

In our project, we wrote the code using SFML 1.6, so the project has a few things that need to be changed before it
will work. I assume that you have the files for SFML 1.6 in your possession, if not, download the files called:
SFML full SDK (headers / libraries / documentation / sources / samples / external libraries).

Now, onto the project properties. Go to the project properties->C/C++->General, then in the box called: "Additional
Include directories" change the filename to where the include folder of SFML 1.6 is. Mine was in the same folder
as my project. Everything else should be set up in the provided project. Nothing else should need to be changed. 

I also assume that you are using VS 2008, since that is what we were using.





