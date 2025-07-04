#include<windows.h>
#include<iostream>

#include "Conlib.h"
#include "Player.h"

//status enumerator

enum GameStatus {
    GameMainMenu = 1,
    GameRunning,
    GamePaused,
    GameWon,
    GameLostLife,
    GameLost,
    GameExit,
    GameSplashScreen
};

//Difficulty

enum GameDifficult {
    GameEasy = 1,
    GameMedium,
    GameDifficult,
};

//game base class

class CGame {
    private:
        Conlib * m_Console;
        int     m_lastAction;

        //game info
         int m_GameStatus;
         COORD m_Arena;
         CPlayer m_Player;
         COORD * m_Monsters;
         int m_MonsterNumber;

    public:
        //construcot and des
        CGame();
        CGame (Conlib * Console);
        ~CGame();

        //Shows the Relative
        void ShowSplash(void);
        void ShowMenu(void);
        void ShowGame (void);
        void ShowWon (void);
        void ShowLostLife (void);
        void ShowLost (void);
        void ShowExit (void);

        //Process the turn
        void ProcessSplash(void);
        void ProcessMenu(void);
        void ProcessGame (void);
        void ProcessWon (void);
        void ProcessLostLife (void);
        void ProcessLost (void);
        void ProcessExit (void);
        void ProcessTurn (void);

        //set COnsole info
        void SetConsole (Conlib * Console);

        //game methods
        void StartNewGame (int Difficulty);
        void EndGame (void);
        void CheckCollisions ();
        int GetAction (void);
        int GetStatus (void);
        void MoveMonster (void);

};
