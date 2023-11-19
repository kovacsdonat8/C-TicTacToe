# Tic Tac Toe - User documentation


## Game rules
Tic Tac Toe is played by two players on a square grid board. Players take turns placing their own pieces ("O" or "X") in one of the still empty squares. The game ends when one player wins or when the board is full, in which case a draw will result. To win, one player must place at least five of their pieces in a line, next to each other. The line can be horizontal, vertical or diagonal.

## Players
The game can be played by two players, either human or computer. In the case of the computer, several strategies (offensive, defensive, random) can be selected. By default, humans play against the computer's offensive strategy.

## Menu
The program works in character mode and it is menu-driven, the structure of which is as follows:
#### 1. Play
  1. New Game - start a new game
  2. Continue Game - continuation of the game
  3. Save Game - saving the game position
  4. Load Game - loading a saved game position
  0. Main Menu – return to the main menu
#### 2. Options
  1. Size – setting the size of the board
  2. Player 1 Name: Player 1 - setting the name of the first player
  3. Player 1 Type: Human - setting the type of the first player
  4. Player 2 Name: Player 2 - setting the name of the second player
  5. Player 2 Type: Computer Offensive - setting the second player type
  0. Main Menu – return to the main menu
#### 3. Rules - displaying game rules
#### 0. Exit - exit from the game

## Gameplay
At each step, the program requests the coordinates of the next step from the player and checks whether the step is possible. If not, the program informs the player. And if the computer is playing, the step is taken by pressing Enter. By pressing "0" you can exit the game to the main menu.

## Board
The board is displayed in character mode (redrawn at each step) and vertical and horizontal lines indicate the square grids. By default, the track is 10x10, but it can be changed to any size between 5x5 and 50x50 in the Options/Size menu. Since the board is necessarily square, a size parameter must be specified, which is the length of one of the sides of the square. The lines are indicated by letters from "A" to "Z", after which the numbering continues with double letters from "AA" to "AZ". And the columns are marked with numbers starting from 1. At the end of the game, the winning position is highlighted with a parenthesis "(X)".
(e.g.: J12 represents the twelfth column of the tenth row)

## Save game position
By pressing "0" after any step, you can exit to the main menu and there you can save the game state by selecting the menu item Play/Save Game. The game can be continued after pressing the Play/Continue Game menu item. Of course, even after restarting the program, the saved game position can be restored at any time in the Play/Load Game menu item, and the game can be continued by pressing the Play/Continue Game menu item.
