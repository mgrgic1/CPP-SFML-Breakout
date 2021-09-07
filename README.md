# CPP-SFML-Breakout
This uses the game engine made <a href = "https://github.com/mgrgic1/CPP-SFML-Engine">here</a> to make Breakout, a brick breaker game.

# Setup
This repo includes the necessary "include" files to make SFML run. Once the repo is cloned, from the root directory, run the command 
``` g++ *.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio```
and the game will start.

Note that this was developed in VSCode on Linux Mint, so I did not make a project hierarchy using Visual Studio (which would have added up to be 200MB). Moreover, I found this simple, lightweight approach to be much easier.

# Game Features
The game features:
<ul>
  <li>Collision Detection</li>
   <li>Simple physics behaviors (making the ball move around the screen)</li>
   <li>Reading levels from an XML file (TinyXML library is included in the repo)</li>
   <li>Animations (which can easily be added and expanded upon)</li>
   <li>Music</li>
</ul>

# Playing the Game
The game will exit if the player either loses all three lives OR finishes the game while still holding all lives.




