#include<iostream>
#include<vector>
#include <algorithm>  // for std::shuffle
#include <random>     // for std::default_random_engine
#include <ctime> 
#include <stack>

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

            for (int i = 0; i<2 ; i++){
                for(int i=0; i<=players ; i++) {

                    auto top = Deck.back();

                    std::cout <<"Player"<<i+1 << " :"<< top.second.second<<std::endl;

                    std::vector<int> Score;
                    
                    Score.push_back(top.second.second);

                    Deck.pop_back();



                //std::cout << top.second.second;
                }
            }
            



        }

};

int main() {

    int players;


    std::cout <<"**************************************************Satra (17)********************************************************"<<std::endl;

    std::cout <<"Enter The Number of Players to play with: ";

    std::cin >> players;

    std::cout <<"********************************************************************************************************************"<<std::endl;

    Cards card1;
    Taas myDeck = card1.deck();
    //card1.shuffle(myDeck);
    card1.Play(card1.shuffle(myDeck), players);


    return 0;
}