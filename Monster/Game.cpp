#include "Game.h"
#include<iostream>
#include<sstream>

//init members to initail status
 CGame::CGame () {
    m_Console = NULL;
    m_GameStatus = GameSplashScreen;
    m_lastAction = 0;
    m_Monsters = NULL;
 }

 //init members to inital status with console info

  CGame::CGame (Conlib * Console) {
    m_Console = Console;
    m_GameStatus = GameSplashScreen;
    m_lastAction = 0;
    m_Monsters = NULL;
 }

 //default destructor

 CGame::~CGame() {
    m_Console = NULL;
    m_GameStatus = GameSplashScreen;
    m_lastAction = 0;
    m_Monsters = NULL;
 }

 //sets pointer to the console

 void CGame::SetConsole(Conlib * Console) {
    m_Console = Console;
 }

 //returns thr game status
 int CGame::GetStatus (void) {
    return m_GameStatus;
 }

 //shows the splash Screen and main menu

 void CGame::ShowSplash (void) {
    m_Console->Clear ();
    m_Console->OutputString ("“\t Welcome to Monster 1.0 \n\n”");
    m_Console->OutputString ("“Playing Monster is very easy. \n\n”");

    m_Console->OutputString ("“The objective of the game is to destroy \n”");
    m_Console->OutputString ("“all the monsters. Two or more monsters \n”");
    m_Console->OutputString ("“are destroyed when they move to the \n”");
    m_Console->OutputString ("“same cell in the field. You also lose a \n”");
    m_Console->OutputString ("“life if you move to a cell where a \n”");
    m_Console->OutputString ("“monster is. You move the player with the \n”");
    m_Console->OutputString ("“numerical keypad in the eight possible \n”");
    m_Console->OutputString ("“directions. You can also press Insert \n”");
    m_Console->OutputString ("“which will make you leap to a random \n”");
    m_Console->OutputString ("“place in the field.\n\n”");

    m_Console->SetTextColor (ConRed);
    m_Console->OutputString ("“NOTE: Make sure NumLock is turned off.\n\n”");
    m_Console->SetTextColor (ConRed | ConGreen | ConBlue);

    m_Console->OutputString ("“There are three difficulties available:\n\n”");
    m_Console->OutputString ("“ Easy : Monsters = 10 Arena = 25*15\n”");
    m_Console->OutputString ("“ Lives = 4 Leaps = 3\n”");
    m_Console->OutputString ("“ Medium : Monsters = 20 Arena = 35*18\n”");
    m_Console->OutputString ("“ Lives = 3 Leaps = 2\n”");
    m_Console->OutputString ("“ Hard : Monsters = 30 Arena = 50*23\n”");
    m_Console->OutputString ("“Lives = 2 Leaps = 1\n”");
 }

 //shows the main menu

 void CGame::ShowMenu (void) {
    COORD Position;

    m_Console->SetBackgroundColor(0);
    m_Console->SetTextColor(ConRed);
    m_Console->Clear();

    m_Console->SetBackgroundColor(ConRed| ConGreen | ConBlue);

    m_Console->OutputString("                                             \n");
    m_Console->OutputString("             Monster Version 1.0             \n");
    m_Console->OutputString("                                             \n");

    m_Console->SetBackgroundColor(0);
    m_Console->SetTextColor (ConRed| ConGreen | ConBlue);

    Position.X = 1;
    Position.Y = 4;
    m_Console->SetPosition(Position);
    m_Console->OutputString("What Do You Want to do?? ");

    Position.X = 1;
    Position.Y = 4;
    
    m_Console->SetPosition(Position);
    m_Console->OutputString("1. Start New Game - Easy (For Pussies) ");
    
    Position.Y = 7;
    m_Console->SetPosition(Position);
    m_Console->OutputString("2. Start New Game - Medium (For New Born Babies) ");

    Position.Y = 7;
    m_Console->SetPosition(Position);
    m_Console->OutputString("3. Start New Game - Easy (For Real Gamers) ");

    Position.Y = 10;
    m_Console->SetPosition(Position);
    m_Console->OutputString("Q. Exit Game (Go Play Tetris Noob) ");
 }

 //Shows Actual Game 
 void CGame::ShowGame (void){
    COORD Position;
    int Monster;

    //draw player pos
    m_Console->SetBackgroundColor(0);
    m_Console->SetTextColor (ConGreen);

    m_Player.GetPosition(&Position);
    m_Console->SetPosition(Position);
    m_Console->OutputString("P");

    //Draw Field
    int FieldX, FieldY;
    m_Console->SetBackgroundColor(ConRed| ConGreen | ConBlue);
    m_Console->SetTextColor(ConRed| ConGreen | ConBlue);

    for (FieldY = 0; FieldY <=m_Arena.Y; FieldY++){
        if ((FieldY == 0) || (FieldY == m_Arena.Y)) {
            for (FieldX = 0; FieldX <= m_Arena.X; FieldX++){
                Position.X = FieldX;
                Position.Y = FieldY;
                m_Console->SetPosition(Position);
                m_Console->OutputString("#");
            }
        }
        else {
            Position.X = 0;
            Position.Y = FieldY;
            m_Console->SetPosition (Position);
            m_Console->OutputString("#");
            Position.X = m_Arena.X;
            Position.Y = FieldY;
            m_Console->SetPosition (Position);
            m_Console->OutputString("#");
        }
    }

    //Draw Monsters
    m_Console->SetBackgroundColor(0);
    m_Console->SetTextColor(ConRed);
    for(Monster = 0; Monster < m_MonsterNumber; Monster++){
        if(m_Monsters [Monster].X != 0){
            m_Console->SetPosition(m_Monsters [Monster]);
            m_Console->OutputString("M");
        }
    }

    //Show Lifes and Score

    std::ostringstream Buffer;
    Buffer <<" Lives: " <<m_Player.GetLives()-1<<"\t\t Score: "<<m_Player.GetScore()<<"\t Leaps: "<<m_Player.GetLepas();
    Position.X = 5;
    Position.Y = 24;

    std::string Buff = Buffer.str();
    m_Console->SetPosition(Position);
    m_Console->SetTextColor(ConRed|ConGreen);
    m_Console->OutputString(Buff);

   
 }

//shows game Won
void CGame::ShowWon (void){
    ShowGame();
    COORD Position;

    Position.X = 20;
    Position.Y = 11;
    m_Console->SetPosition(Position);

    m_Console->SetBackgroundColor(ConGreen);
    m_Console->SetTextColor(ConRed);

    m_Console->OutputString("###############################");


    Position.Y = 12;
    m_Console->SetPosition(Position);
    m_Console->OutputString ("#      Congratulations!      #");


    Position.Y = 13;
    m_Console->SetPosition(Position);
    m_Console->OutputString ("#   You Have Killed Everyone #");
    Position.Y = 14;
    m_Console->SetPosition(Position);
    m_Console->OutputString("###############################");
}

//Shows life Lost ox

void CGame::ShowLostLife (void) {
    ShowGame();
    COORD Position;

    Position.X = 20;
    Position.Y = 11;
    m_Console->SetPosition(Position);

    m_Console->SetBackgroundColor(ConGreen);
    m_Console->SetTextColor(ConRed);

    m_Console->OutputString("###############################");


    Position.Y = 12;
    m_Console->SetPosition(Position);
    m_Console->OutputString ("#      Too Bad!!!!!    !!!  #");


    Position.Y = 13;
    m_Console->SetPosition(Position);
    m_Console->OutputString ("#    You Have Lost a Life   #");
    Position.Y = 14;
    m_Console->SetPosition(Position);
    m_Console->OutputString("###############################");
}

//Shows Game Lost Box

void CGame::ShowLost (void) {
    ShowGame();
    COORD Position;

    Position.X = 20;
    Position.Y = 11;
    m_Console->SetPosition(Position);

    m_Console->SetBackgroundColor(ConGreen);
    m_Console->SetTextColor(ConRed);

    m_Console->OutputString("###############################");


    Position.Y = 12;
    m_Console->SetPosition(Position);
    m_Console->OutputString ("#    LOLOLOL You No Life!     #");


    Position.Y = 13;
    m_Console->SetPosition(Position);
    m_Console->OutputString ("#   You Have Been Lost        #");
    Position.Y = 14;
    m_Console->SetPosition(Position);
    m_Console->OutputString("###############################");
}

//shows exit text
void CGame::ShowExit (void){
    m_Console->SetBackgroundColor(0);
    m_Console->SetTextColor(ConRed|ConGreen|ConBlue);
    m_Console->Clear();
    m_Console->OutputString("\n Monsterssss \n\n");
    m_Console->OutputString("By CoughKing\n\n");
    m_Console->OutputString("Thanks For PLaying\n\n");
    m_Console->OutputString("Xanax For Life\n\n");
}

//showing correct game Screen
void CGame::Show (void){
    m_Console->SetBackgroundColor(0);
    m_Console->SetTextColor(ConRed|ConGreen|ConBlue);
    m_Console->Clear();

    switch (m_GameStatus){
        case GameMainMenu:
            ShowMenu();
            break;
        case GameRunning:
            ShowGame();
            break;
        case GameWon:
            ShowWon();
            break;
        case GameLostLife:
            ShowLostLife();
            break;
        case GameLost:
            ShowLost();
            break;
        case GameExit:
            ShowExit();
            break;
        case GameSplashScreen:
            ShowSplash();
            break;
        default:
            break;    
    }
}