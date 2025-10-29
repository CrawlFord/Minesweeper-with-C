# Minesweeper-with-C
### Description
A classic game of minesweeper created with C

### Technology
Made in C using Code::Blocks IDE with GNU GCC compiler

### Controls
1)A square matrix will be shown to the player. Its size will be determined by the
 level of difficulty selected by the player.

2)The primary goal is to not open a square with a mine in it.

3)One may open any square by writing the numbered location of that square.

4)All the matrix are numbered from 0 to n both for rows and for columns
(where n is the sixe of the matrix).

5)A standard input consists of 3 integer numbers.

6)If the player wants to open a box, then he has to press 1 and if the player wants
 to flag a mine, then he has press 2 at the end of entering the co-ordinates.

7)The first two input numbers are co-ordinates and the third is a number which is either 
  1 or 2.

         FOR EXAMPLE: 1 3 1
  It means that the co-ordinate is (1,3) and the player wants to open the box.

8)Based on the number shown when each square is opened, one has to deduce the possible 
  positions of a mine and has to mark that position.

9)When a player has marked the positions of all of the bombs, the player wins the game.

10)If any player opens up a square containing  a mine, the player loses the game.
