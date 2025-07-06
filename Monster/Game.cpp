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

//starting a new games

void CGame::StartNewGame (int Difficulty){
    int Monster;

    COORD Position;

    m_GameStatus = GameRunning;

    //setting difficulty

    switch(Difficulty) {
        case GameEasy:
        m_MonsterNumber = 10;
        m_Player.SetLives (4);
        m_Player.SetLeaps (3);
        m_Arena.X = 25;
        m_Arena.Y =15;
        break;

        case GameMedium:
        m_MonsterNumber = 25;
        m_Player.SetLives (3);
        m_Player.SetLeaps (2);
        m_Arena.X = 35;
        m_Arena.Y =18;
        break;

        case GameDifficult:
        m_MonsterNumber = 35;
        m_Player.SetLives (2);
        m_Player.SetLeaps (1);
        m_Arena.X = 50;
        m_Arena.Y =23;
        break;
    }

    //create Player
    m_Player.RandomLeap (m_Arena);
    m_Player.GetPosition(&Position);
    m_Player.SetScore(0);


    //Create Monster
    m_Monsters = new COORD [m_MonsterNumber];
    srand(time(NULL));

    //calculate random position for monsters
    for(Monster = 0; Monster < m_MonsterNumber; Monster++ ){
        //diff pos than player;

        do {
            m_Monsters [Monster].X = (rand () % (m_Arena.X -1 ) + 1);
            m_Monsters [Monster].Y = (rand () % (m_Arena.Y -1 ) + 1);

        }while (( m_Monsters [Monster].X == Position.X) && ( m_Monsters [Monster].Y == Position.Y));
    }
}

//player Input

int CGame::GetAction (void) {
    m_lastAction = m_Console->GetKey();

    return m_lastAction;
}

//moving monsters to wards player

void CGame::MoveMonster(void) {
    COORD Distance, Position;

    int Monster;
    m_Player.GetPosition (&Position);

    for (Monster = 0; Monster < m_MonsterNumber; Monster++) {
        //check if monster is dead or not
        if (m_Monsters [Monster].X != 0) {
            Distance.X = Position.X - m_Monsters [Monster].X;
            Distance.Y = Position.Y - m_Monsters [Monster].Y;


            //unitary movement
            if (Distance.X > 0)
            {
                Distance.X = 1;
            }
             if (Distance.X < 0)
            {
                Distance.X = -1;
            }
             if (Distance.Y > 0)
            {
                Distance.Y = 1;
            }
             if (Distance.Y < 0)
            {
                Distance.Y = -1;
            }

            //mve them uo


            m_Monsters [Monster].X += Distance.X;
            m_Monsters [Monster].Y += Distance.Y;
        }
    }
}


//process splashScreen

void CGame::ProcessSplash (void) {
    // specific key requirememnts
    if (m_lastAction) {
        m_GameStatus = GameMainMenu;
    }
}

// gets menu option

void CGame::ProcessMenu (void ) {
    switch (m_lastAction){
        //quits
        case VK_ESCAPE:
        case 'Q':
        case 'q':
            m_GameStatus = GameExit;
            break;
        //starting a new game
        case '1':
            StartNewGame (GameEasy);
            m_GameStatus = GameRunning;
            break;
        case '2':
            StartNewGame (GameMedium);
            m_GameStatus = GameRunning;
            break;
        case '3':
            StartNewGame (GameDifficult);
            m_GameStatus = GameRunning;
            break;
        
    }
}

//moving player and Mosters

void CGame::ProcessGame (void) {
    COORD Movement;
    int Monster, MonstersAlive;
    Movement.X = 0;
    Movement.Y = 0;

    //move player

    switch (m_lastAction) {
        case VK_UP: 
            Movement.Y = -1 ;
            break;
        case VK_DOWN: 
            Movement.Y = 1 ;
            break;
        case VK_LEFT: 
            Movement.X = -1 ;
            break;
        case VK_RIGHT: 
            Movement.X = 1 ;
            break;
        

        case VK_HOME:
            Movement.X = -1;
            Movement.Y = -1 ;
            break;
        case VK_PRIOR: 
            Movement.X = 1;
            Movement.Y = -1 ;
            break;
        case VK_END: 
            Movement.X = -1;
            Movement.Y = 1 ;
            break;
        case VK_NEXT: 
            Movement.X = 1;
            Movement.Y = 1 ;
            break;

        case VK_INSERT:
            if (m_Player.GetLepas () > 0) {
                m_Player.RandomLeap (m_Arena);
                m_Player.SetLeaps (m_Player.GetLepas() - 1);
            }
            break;
        case VK_ESCAPE:
            EndGame ();
            m_GameStatus = GameMainMenu;
            break;
    }

    //the movement

    if ((Movement.X != 0) || (Movement.Y != 0)) {
        COORD PlayerPosition;
        m_Player.GetPosition (&PlayerPosition);

        //if inside bounds mover???
        if ((Movement.X + PlayerPosition.X > 0) && (Movement.Y + PlayerPosition.Y > 0) && 
            (Movement.X + PlayerPosition.X < m_Arena.X) && (Movement.Y + PlayerPosition.Y < m_Arena.Y)) 
        {
            m_Player.Move (Movement);
        }

        MoveMonster ();
        CheckCollisions ();

        MonstersAlive = 0;

        for (Monster = 0; Monster < m_MonsterNumber; Monster ++) {
            if (m_Monsters [Monster].X != 0) {
                MonstersAlive = 1;
                break;
            }
        }

        if (MonstersAlive = 0) {
            m_GameStatus = GameWon;
        }
    }
}

//check collision
void CGame::CheckCollisions () {
    COORD Position;
    int MonsterA, MonsterB;

    m_Player.GetPosition (&Position);

    for (MonsterA = 0; MonsterA < m_MonsterNumber; MonsterA++) {
        //check if monster is dead;
        if (m_Monsters [MonsterA].X != 0) {
            //check collsiion with player
            if ((m_Monsters [MonsterA].X == Position.X) && (m_Monsters [MonsterA].Y == Position.Y)){
                m_Monsters [MonsterA].X = 0;
                m_Monsters [MonsterA].Y = 0;

                //updates player lifes
                if (m_Player.GetLives () - 1 <= 0) {
                    m_GameStatus = GameLost;
                }
                else {
                    m_GameStatus = GameLostLife;
                }
                return;
            }

            //collisions of monsters
            for (MonsterB = MonsterA+1; MonsterB < m_MonsterNumber; MonsterB++) {
                //if monster dead?
                if (m_Monsters [MonsterB].X != 0) {
                    //collsion

                    if ((m_Monsters [MonsterA].X == m_Monsters [MonsterB].X) && (m_Monsters [MonsterA].Y == m_Monsters [MonsterB].Y)) {
                        m_Monsters [MonsterA].X = m_Monsters [MonsterB].X = 0;
                        m_Monsters [MonsterA].Y = m_Monsters [MonsterB].Y = 0;
                        m_Player.SetScore (m_Player.GetScore () + 15);
                    }
                }
            }
        }
    }
}

//end game and return to main menu

void CGame::ProcessWon(void) {
     //if user presssed key move to main menu
    if (m_lastAction) {
        m_GameStatus = GameMainMenu;
    }

    EndGame ();
    //Show ();

}

//finnish the game

void CGame::EndGame (void) {
    if (m_Monsters != NULL) {
        delete [] m_Monsters;
    }

    m_Monsters = NULL;
}
//process a life liost 

void CGame::ProcessLostLife (void) {
    int IsValid = 0;
    int Monster;
    COORD Position;

    //remove life if life <= 0 end game
    m_Player.SetLives (m_Player.GetLives () - 1);
    if (m_Player.GetLives () - 1 <= -1) {
        m_GameStatus = GameLost;
    }
    else {
        m_GameStatus = GameRunning;
        IsValid = 0;
        //place player in new pos

        do
        {
           m_Player.RandomLeap (m_Arena);
           m_Player.GetPosition (&Position);

           //pos must be diffn than mosters
           for (Monster = 0; Monster < m_MonsterNumber; Monster++) {
            //check if monster is dead
            if (m_Monsters [Monster].X != 0) {
                if ((m_Monsters [Monster].X != Position.X) && (m_Monsters [Monster].Y != Position.Y)) {
                    IsValid =1 ;
                }
                else {
                    IsValid = 0;
                }
            }
           }

        } while (IsValid == 0);
        
    }
}

//process lest and end game

void CGame::ProcessLost (void) {
    //if user presssed key move to main menu
    if (m_lastAction) {
        m_GameStatus = GameMainMenu;
    }

    EndGame ();
    Show ();
}

//general function that does all tasks for this turn

void CGame::ProcessTurn (void) {
    //Since the splash screen must be shown when we brgin we must force it to be shown
    if (m_GameStatus == GameSplashScreen) {
        Show ();
    }

    //now users action defining

    if (GetAction () ) {
        switch (m_GameStatus) {
            case GameMainMenu:
                ProcessMenu ();
                break;
            case GameRunning:
                ProcessGame ();
                break;
            case GameWon:
                ProcessWon ();
                break;
            case GameLostLife:
                ProcessLostLife ();
                break;
            case GameLost:
                ProcessLost();
                break;
            case GameSplashScreen:
                ProcessSplash ();
                break;

            default:
                break;
        }

        Show ();
    }
}

