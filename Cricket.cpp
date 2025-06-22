#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#include<map>
//#include<iomanip>


class BallEvent {
    private:
        int over;
        int ball;
        std::string result;
    public:
        BallEvent(int over, int ball, const std::string &result) : over(over), ball(ball), result(result) {

        }

        void display() const{
            std::cout << "Over "<< over << "." << ball << ": ";
            if(result == "W"){
                std::cout << "OUT!! \n";
            }
            else {
                std::cout << result << " Run" << (result != "1" ? "s" : "") << "\n";
            }
        }

        int getOver() const {return over;}
        int getBall() const {return ball;}
        std::string getResult() const {return result;}
};


class Innings {
    private:
        int totalRuns;
        int totalWickets;
        int balls = 30;
        std::vector<BallEvent> events;

        std::vector<std::string> runOptions = {"0", "1", "2", "3", "4", "6"};

    public:
        Innings(int runs, int wickets) : totalRuns(runs), totalWickets(wickets) {
            srand(time(0));
        }

        void simulate() {
            int remainingRuns = totalRuns;
            int remainingWickets = totalWickets;

            std::vector<int> outBalls;
            std::vector<std::string> runBalls;
            std::vector<int> runPositions;

            //choose positions for outs
            int outsToAssign = (totalWickets == 10) ? 9 :totalWickets;

            while ((int)outBalls.size() < outsToAssign) {
                int pos = rand() % balls;
                if (std::find(outBalls.begin(), outBalls.end(), pos) == outBalls.end()) {
                    outBalls.push_back(pos);
                }

            }

            std::sort(outBalls.begin(), outBalls.end());

            int runBallsNeeded = (totalWickets == 10) ? balls : balls - totalWickets;
            //generate runs
            while (true) {
                runBalls.clear();
                int sum = 0;
                for (int i = 0; i < runBallsNeeded; i++) {
                    std::vector<std::string> validOptions;
                    
                    for (const std::string &run : runOptions) {
                        int val = std::stoi(run);
                        int minRemaining = runBallsNeeded - i - 1;
                        if (sum + val + minRemaining <= totalRuns) {
                            validOptions.push_back(run);
                        }
                    }

                    if (validOptions.empty()) break;

                    std::string chosen = validOptions[rand() % validOptions.size()];
                    runBalls.push_back(chosen);
                    sum += std::stoi(chosen);

                }
                if (sum == totalRuns && runBalls.size() == runBallsNeeded) 
                    break;
            }

            //assign positions for run balls
            for (int i = 0; i < balls; i++) {
                if (std::find(outBalls.begin(), outBalls.end(), i) == outBalls.end())
                    runPositions.push_back(i);
            }

            //for 10 wickets
            if (totalWickets == 10) {
                int lastRunBall = runPositions.back();
                for (int i = lastRunBall + 1; i < balls; i++) {
                    if (std::find(outBalls.begin(), outBalls.end(), i) == outBalls.end()) {
                        outBalls.push_back(i);
                        break;
                    }
                }
            }

            std::sort(outBalls.begin(), outBalls.end());

            std::map<int, std::string> ballMap;
            for (size_t i = 0; i < runBalls.size(); i++) {
                ballMap[runPositions[i]] = runBalls[i];
            }
            for (int outBall : outBalls) {
                ballMap[outBall] = "W";
            }

            //cretae events in correct order

            for (int i = 0; i < balls; i++) {
                int over = i / 6;
                int ball = (i % 6) +1;

                if (ballMap.find(i) != ballMap.end()) {
                    std::string res = ballMap[i];
                    events.emplace_back(over, ball, res);
                    if (totalWickets == 10 && res == "W" && (int)std::count_if(events.begin(), events.end(), [](auto &e) { return e.getResult() == "W";}) == 10)
                        break;
                    }
                    else {
                        //
                        events.emplace_back(over, ball, "0");
                    }
            }

        }

        void displayCommentary() const {

            
            std::cout << "\n -----------------------------------/Ball by Ball Commentary/-----------------------------------\n";
            for (const BallEvent &event : events) {
                event.display();
            }
            const BallEvent &last = events.back();
            int totalOvers = last.getOver();
            int totalBalls = last.getBall();

            if (totalBalls == 6) {
                totalOvers += 1;
                totalBalls = 0;
            }
            std::cout << "\n Final Score of the Innings: " << totalRuns << "/" << totalWickets
                      << " in " << totalOvers << "." << totalBalls << " Overs \n";
        }
};

int main() {
    
    int runs, wickets;
    std::cout << "**************************Cricket Playthrough (5 Overs Max) ********************************** \n";
    std::cout << "Enter the Number of Runs: \n";
    std::cin >> runs;

    std::cout << "Enter the Number of Wickets: \n";
    std::cin >> wickets;

    if (wickets > 10) {
        std::cout << "You cant enter more than 10 Wickets";
        return 1;
    }

    Innings innings(runs, wickets);
    innings.simulate();
    innings.displayCommentary();
    std::cout << "************************************************************************************************ \n";
    return 0;
}