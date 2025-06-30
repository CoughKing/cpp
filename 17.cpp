#include<iostream>
#include<vector>
#include <algorithm>  // for std::shuffle
#include <random>     // for std::default_random_engine
#include <ctime> 
#include <stack>
#include <windows.h>

typedef std::vector<std::pair<std::string, std::pair<std::string, int>>> Taas;

class Cards{
    private:
        std::string SUIT[4] = { "HEART", "CLUB", "DIAMOND", "SPADE" }; 
        std::string VALUE[13] = { "ACE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE", "TEN", "JACK", "QUEEN", "KING"};
        int Number[13] ={1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    public:
        Taas deck(){
            Taas Deck;
            for (int i=0; i < 4; i++){
                for (int j=0; j < 13; j++)
                {
                    
                    Deck.push_back({VALUE[j], {SUIT[i], Number[j]}});
                }

            }

            // for (auto cards : Deck)
            // {
            //     std::cout << cards.first <<" of "<< cards.second.first<<" of value "<<cards.second.second<<std::endl;
            // }
            
            return Deck;

        }

        //std::stack<Taas> Stack;

        Taas shuffle(Taas Deck){
            std::default_random_engine rng(static_cast<unsigned>(std::time(nullptr)));
            //std::cout <<rng<<std::endl;
            std::shuffle(Deck.begin(), Deck.end(), rng);

            // for (auto cards : Deck)
            // {
            //     std::cout << cards.first <<" of "<< cards.second.first<<" of value "<<cards.second.second<<std::endl;
                
            // }


           

            

            return Deck;
        }

        void Play(Taas Deck, int players){
            // std::stack<std::pair<std::string, std::pair<std::string, int>>> Stack;
            // for (auto card : Deck){
            //     Stack.push(card);
            // }

            // while(!Stack.empty()){
            //     auto top = Stack.top();
            //     std::cout<<top.first<<" of "
            //              <<top.second.first<<" of value "
            //              <<top.second.second<<std::endl;
            //     Stack.pop();
            // }
            std::vector<int> Score;

            for (int i = 0; i<2 ; i++){
                for(int i=0; i<=players ; i++) {

                    auto top = Deck.back();

                    std::cout <<"Player"<<i+1 << " :"<< top.second.second<<std::endl;

                    
                    
                    Score.push_back(top.second.second);

                    Deck.pop_back();



                //std::cout << top.second.second;
                }
            }
            
            for (int score : Score) {
                std::cout << score <<std::endl;
            }



        }

};

int main() {

    int players;
    int choice;
    bool menu = true;

    while(menu){

        

        std::cout <<"**************************************************|||||Satra (17)|||||********************************************************"<<std::endl;

        std::cout <<"Enter the Choice (1-2): "<<std::endl<<
                    "1. Play The Game"<<std::endl<<
                    "2. Quit the Game"<<std::endl;
        std::cin >> choice;
        std::cout <<"********************************************************************************************************************"<<std::endl;

        switch (choice)
        {
        case 1:
            
            {
                std::cout <<"Enter The Number of Players to play with: ";

                std::cin >> players;
                Cards card1;
                Taas myDeck = card1.deck();
                //card1.shuffle(myDeck);
                card1.Play(card1.shuffle(myDeck), players);
                break;
            }

        case 2:
            {
                std::cout <<"Thanks For Staying to Play The Game!!! GoodBye"<<std::endl;
                Sleep(1000);
                menu=false;

                break;
            }    
        
        default:
            std::cout <<"You must Select Something like 1 or 2 anything Else than That is a Big NO!!!! NO!!! "<<std::endl;
            //menu = false;
            break;
        }
            

        std::cout <<"********************************************************************************************************************"<<std::endl;

        

    }


    return 0;
}