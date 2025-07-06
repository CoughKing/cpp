#include "Conlib.h"

#include "Game.h"

int main () {
    Conlib  Console;
    CGame  Game (&Console);
    
    Console.SetTitle("Monster");

    while (Game.GetStatus () != GameExit) {
        Game.ProcessTurn ();
    }

    return 0;
}