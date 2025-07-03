#include<iostream>

#include<ctime>

int diceRoll();

int main() {
    srand(time(0));
    std::cout <<"*********************g****************a***a**********************************************************************************"<<std::endl;
    std::cout <<"********************g****************a******a********************************************************************************"<<std::endl;
    std::cout <<"******************g*******************a******a*******************************************************************************"<<std::endl;
    std::cout <<"*******************g*****************a********a*******************************************************************************"<<std::endl;
    std::cout <<"*********************g*****g*g*g*****a**aa*a*a*a***a*********************************************************************************"<<std::endl;
    std::cout <<"************************g***g********a*********a*******************************************************************************"<<std::endl;
    std::cout <<"***************************g*********a**********a*****************************************************************************"<<std::endl;


    char any;
    std::cout <<"Enter any Alphabet to Continue"<<std::endl;
    std::cin >> any;
     std::cout <<"Rules of Game:\n"
                "Bet from $10 to $100 and win based on your dice guess!\n"
                "Guess correctly to multiply your bet:\n"
                "  - 2 or 12: ×5\n"
                "  - 4 or 10: ×2.5\n"
                "  - 6 or 8: ×1.5\n";

    int bet;
    int chance;

    int cash = 1000;  
    while (cash > 10)
    {
        std::cout <<"You Currently Have $"<<cash<<std::endl;
        std::cout <<"Enter Your Bet Money: $(10 to 100) "<<std::endl;
        std::cin >> bet;
         if (bet < 10 || bet > 100) {
            std::cout << "Invalid bet amount. Try again.\n";
            continue;
        }
        std::cout <<"Enter Your Chance of Dice: 2 or 12, 4 or 10 and 6 or 8"<<std::endl;
        std::cin >> chance;

        int DiceVal = diceRoll();
        if (chance == DiceVal){
            switch(DiceVal) {
                case 2:
                case 12:
                    std::cout << "You Win! Your Bet Multiplied by 5.\n";
                    bet *= 5;
                    cash += bet;
                    break;
                case 4:
                case 10:
                    std::cout << "You Win! Your Bet Multiplied by 2.5.\n";
                    bet *= 2.5;
                    cash += bet;
                    break;
                case 6 :
                case 8:
                    std::cout << "You Win! Your Bet Multiplied by 1.5.\n";
                    bet *= 1.5;
                    cash += bet;
                    break;
                default:
                    std::cout << "Unexpected win condition.\n";
                    //cash -= bet;
                    break;
            }
        }  else{
             std::cout << "You guessed wrong.\n";
            cash -= bet;
        }
        //std::cout <<"Your Current Cash:"<< cash;
         

    } ;
      
    std::cout << "\nGame Over! You have less than $10.\n";

    return 0;
}


int diceRoll() {
    int dice1 = rand() % 6 +1;
    int dice2 = rand() % 6 +1;
    int result = dice1 + dice2;
    std::cout << "The Sum of these Dice are i.e "<< dice1<<" + " <<dice2<<": "<<result<<std::endl;
    return result;

}