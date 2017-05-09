# CSC 1120 Final Exam - Tanks

## by Alex Kristy, Kevin Mahoney, and Jacob Davis

In this README we will go over the basic game functions and controls and go over some of the code involved in it.

# The Game
The game is a classic game of two stationary tanks firing shells at one another. The goal of the game is to hit your opponent tank three times before they can land three hits on you. With each hit the terrain, which is randomly generated, will change along with your positions to force you to adjust your shot to hit once again. The hit detection is rather simple and requires you to only hit in a three by three space around the opposing tank, but be sure not to hit yourself. Once hit three times the game is over and you will get an option to play again. 

The controls are, like the game, rather simple. You can control the tank using wasd or the corresponding arrowkeys. The right and left keys control the power while up and down controls the angle you shoot at.

# The Code
The code is a bit more complex than the game it makes. It uses a basic understanding of trajectory to create the shot that the tank fires and a bit of knowledge on how ncurses refreshes to redraw the tanks. Our code uses a ground class, a player class, and a 2DVec class. The ground class generates the randomized ground that the game takes place on. The player class draws the players in and chooses a random place on the map for each to spawn in on. The 2DVec is what makes the shells fly in a realistic fashion and drawing it to show you how to adjust your next shot. It does this through overloads of the function that simplify our function called shoot in our main. However, we ran into a strange bug that needs to be fixed involving the 2DVec 
that changed our shot location to something strange, however it can be easily reverted to working code without the 2DVec. 
