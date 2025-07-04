#include<windows.h>

#include<time.h>

//player class

class CPlayer{
    private:
        COORD m_Position;
        short m_Lives;
        int m_Score;
        int m_Leaps;

    public:
        //constructor and Destructor
        CPlayer();
        ~CPlayer();

        //move player

        void Move (COORD Direction);
        void RandomLeap (COORD Arenasize);

        //maintain methods
        void GetPosition (COORD *Position);
        void SetLives (short Lives);
        short GetLives (void);

        void SetScore (int Score);
        int GetScore (void);

        void SetLeaps(int Leaps);
        int GetLepas (void);
};