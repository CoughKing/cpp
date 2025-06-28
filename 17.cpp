#include<iostream>
#include<vector>
#include <algorithm>  // for std::shuffle
#include <random>     // for std::default_random_engine
#include <ctime> 

class Cards{
    private:
        std::string SUIT[4] = { "HEART", "CLUB", "DIAMOND", "SPADE" }; 
        std::string VALUE[13] = { "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE", "TEN", "JACK", "QUEEN", "KING"};

    public:
        std::vector<std::pair<std::string, std::string>> deck(){
            std::vector<std::pair<std::string, std::string>> Deck;
            for (int i=0; i < 4; i++){
                for (int j=0; j < 13; j++)
                {
                    
                    Deck.push_back({VALUE[j], SUIT[i]});
                }

            }

            for (auto cards : Deck)
            {
                std::cout << cards.first <<" of "<< cards.second<<std::endl;
            }
            
            return Deck;

        }

        std::vector<std::pair<std::string, std::string>> shuffle(std::vector<std::pair<std::string, std::string>> Deck){
            std::default_random_engine rng(static_cast<unsigned>(std::time(nullptr)));
            std::cout <<rng<<std::endl;
            std::shuffle(Deck.begin(), Deck.end(), rng);

            for (auto cards : Deck)
            {
                std::cout << cards.first <<" of "<< cards.second<<std::endl;
            }


            return Deck;
        }

};

int main() {

    Cards card1;
    std::vector<std::pair<std::string, std::string>> myDeck = card1.deck();
    card1.shuffle(myDeck);


    return 0;
}