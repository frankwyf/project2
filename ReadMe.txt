URL of my git repository: https://github.com/frankwyf/project2 

Screen shots of commit history: 

****************************user hand book*****************************
Welcome to my C language version of Conway’s Game of life. In the following part I will explain the main components of this project and how to play the game.

1.	Brief introduction to the four parts of this project.
There are four modules, 26 function (including some integrated functions) to perform the game. The four modules are divided by input/output, evolution, new generation and visualization (SDL). Each of the four parameters of this game, namely row, column, steps and delay time are defined in the state file but can be configured according to player’s wish. Also, replay and initialize by click during the game are provided to the players, detailed instruction on how to do so will be provided below. All the choices in this project are simple questions that can be answered with ‘y’ or numbers, no other inputs are allowed.


2.	How to play the game
2.1.	The size of the game can be configured through command line or through user input, so it’s okay to start the game with or without two command line arguments.
2.2.	If the game is stared without arguments, then a question on the terminal will ask the player whether he or she wants to change the initial state or not, enter ‘y’ if you wish so, enter row and column as well as delay time, then you can choose to initialize the randomly generated game thorough clicks on the screen. Due to the SDL library restrictions, computer players should move their mouse out of the window immediately after a click, or the state of the cell will change twice. Finally, press enter when you are satisfied with you “cell world”. If you don’t wish to change, just press a random button to continue, then a question will be presented to ask the steps of the game, enter the number of steps you want to game to continue running for or 0 for infinite steps.
2.3.	If command line arguments are provided, then the programme will check automatically and reopen the same size of the game if the size entered is the same as last time. Otherwise, a new random game map will be provided and you can choose to re-establish it by clicking, rules are the same as in 2.2.

2.4.	After initializing, the game will start to run. A window with tips will be shown, displaying the message about the following optional operations you can make during the game:
1.	Press backspace for change the state of the cells, this can be done at ant step during the game.
2.	Press enter for replay the game until now, this can be done at ant step during the game. 
3.	Press esc to terminate the game and a replay request will be presented. This can be done at ant step during the game. 
4.	Also, you can press the button on right-top of the window during the game, however this is not recommended as there will be a small window influencing your operation there.

During the game, a small window with information as current step, time, living and dead cells will be presented on the right-top of the game window. This dynamic and changes every time the game evolves.

2.5.	Finally, after all the steps/manually terminated, you can type ‘y’ on the terminal to replay the game, else, press any key and the game will be saved after a good bye message.
