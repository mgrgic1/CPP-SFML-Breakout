#include "Game.hpp"

int main() {

    //Initialize Game
    Game game;

    //game loop
    while(game.isRunning()) 
    {

        //UPDATE
        game.Update();

        //RENDER
        game.Render();

        game.CheckInput();

    }


    //end application
    return 0;


}