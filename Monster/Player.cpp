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
