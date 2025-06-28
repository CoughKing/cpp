#include<iostream>
#include<vector>
#include <algorithm>  // for std::shuffle
#include <random>     // for std::default_random_engine
#include <ctime> 


typedef std::vector<std::pair<std::string, std::pair<std::string, int>>> Taas;

class Cards{
    private:
        std::string SUIT[4] = { "HEART", "CLUB", "DIAMOND", "SPADE" }; 
        std::string VALUE[13] = { "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE", "TEN", "JACK", "QUEEN", "KING"};
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

            for (auto cards : Deck)
            {
                std::cout << cards.first <<" of "<< cards.second.first<<" of value "<<cards.second.second<<std::endl;
            }
            
            return Deck;

        }

        Taas shuffle(Taas Deck){
            std::default_random_engine rng(static_cast<unsigned>(std::time(nullptr)));
            std::cout <<rng<<std::endl;
            std::shuffle(Deck.begin(), Deck.end(), rng);

            for (auto cards : Deck)
            {
                std::cout << cards.first <<" of "<< cards.second.first<<" of value "<<cards.second.second<<std::endl;
            }


            return Deck;
        }

};

int main() {

    Cards card1;
    Taas myDeck = card1.deck();
    card1.shuffle(myDeck);


    return 0;
}