#include "Player.h"

//does nothing add cons and dest

CPlayer::CPlayer() {}
CPlayer::~CPlayer() {}

//Moves Player

void CPlayer::Move (COORD Direction) {
    m_Position.X += Direction.X;
    m_Position.Y += Direction.Y;

}

//makes randomleap
void CPlayer::RandomLeap (COORD ArenaSize) {

    srand(time(NULL));
    m_Position.X = (rand() % (ArenaSize.X - 1) + 1);
    m_Position.Y = (rand() % (ArenaSize.Y - 1) + 1);

}

//gets pos
void CPlayer::GetPosition (COORD *Position) {
    memcpy (Position, &m_Position, sizeof (COORD));

}

//set player lives

void CPlayer:: SetLives(short Lives) {
    m_Lives = Lives;
}

//gets player lives

short CPlayer::GetLives (void){
    return m_Lives;

}
//sets player scores
void CPlayer:: SetScore(int Score) {
    m_Score = Score;
}

int CPlayer:: GetScore(void) {
    return m_Score;
}

//sets player availale leaps

void CPlayer::SetLeaps(int Leaps){
    m_Leaps = Leaps;
}

//gets player availale leaps

int CPlayer::GetLepas (void) {
    return m_Leaps;
}