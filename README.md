# TraceX

This source code was made for "Qt creator 4.14.0 (community)" with the 5.15.2 MinGW_64/5.15.2 MinGW_32 compiler.

Once you have it complied, you can start a TraceXServer and a TraceXClient.

## Connection
With the TraceXClient, press "Jouer" then you will be prompted to enter a username and a color. You cannot choose twice the same username. If you do, you will be kicked out of the server. If 2 players choose the same color, one of the 2 will get a color reasigned. Per client, there is a maximum of 3 players. Note that that key input is also shown on the right for each player.

Make sure you enter the right ip. If the server is running on the same machine as the client, leave "127.0.0.1" otherwise, make sure you enter the remote ip to connect to the server. Then you can press "Jouer!"

## Lobby
The UI should change and you are now waiting for players to join. You have a rundown of all connected players on the left under "Score". There you can see the color of each player, it's name and the current score.

Once all players have joined, press "Prêt ?" which will tell the server that you are ready to start the game. If all clients send the ready signal, the game will start.

## The Game
### Controlls
Each player controlls one trace which has a unique color. As stated before, each player has keys assigned to it which allows them to move either left or right.

### Objectif
Try to be the last player alive. The longer you are alive, the more points you will get. The last player alive also gets bonus points.

### How to stay alive
If you touch with your head the trace of another player (dead or alive) you will die. Also, touching the bounds of the game kills you too.

### Leave the Game
To leave the game, simply close the window
