//Will move all the functions here

#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "/public/read.h"
#include "/public/colors.h"


using namespace std;

struct question {
    string quest;
    vector<string> answers;
};

void acceptBattleRules(iostream &server){
    string theirs;
    for (int i = 0; i < 5; i++) {
        getline(server, theirs);
        cout << theirs << endl << endl;
        resetcolor();
    }
}

void acceptRules(iostream &stream){
    string theirs;
    for (int i = 0; i < 15; i++) {
        getline(stream, theirs);
        cout << theirs << endl << endl;
        resetcolor();
    }
}

void startResponse(iostream &stream) {
    string theirs;
    for (int i = 0; i < 4 ; i++) {
        getline(stream, theirs);
        cout << theirs << endl;
        resetcolor();
    }
}

//This function just prints the world map.
void printMap(vector<vector<char>> &grid, const int SIZE) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i == 0 && j == 0) {
                setcolor(95, 15, 64);
                cout << grid.at(i).at(j) <<  "  ";
            }
            else if (i == 0 or j == 0){
                setcolor(153, 217, 140);
                cout << grid.at(i).at(j) << "  ";
            }
            else {
                setcolor(30, 96, 145);
                cout << grid.at(i).at(j) << "  ";
            }
        }
        cout << RESET << endl;
    }
    cout << endl;
}

//Outputs the player's layout of ships
//A for Aircraft Carrier, B for Battleship, S for Submarine, D for Destroyer, C for Cruiser
//~ for water (empty)
void printPlayerGrid(vector<vector<char>> &printgrid, vector<vector<int>> &playergrid, const int SIZE) {
        for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                        if (i == 0 && j == 0) {
                                setcolor(95, 15, 64);
                cout << printgrid.at(i).at(j) << "  ";
            }
                        else if (i == 0 or j == 0) {
                setcolor(153, 217, 140);
                cout << printgrid.at(i).at(j) << "  ";
            }
            else {
                if (i > 0 and j > 0) {
                    if (playergrid.at(i).at(j) == 0) {
                        setcolor(30, 96, 145);
                        cout << "~  ";
                    }
                    else if (playergrid.at(i).at(j) == 1){
                        setcolor(233, 196, 106);
                        cout << "A  ";
                    }
                    else if (playergrid.at(i).at(j) == 2){
                        setcolor(233, 196, 106);
                        cout << "B  ";
                    }
                    else if (playergrid.at(i).at(j) == 3){
                        setcolor(233, 196, 106);
                        cout << "S  ";
                    }
                    else if (playergrid.at(i).at(j) == 4){
                        setcolor(233, 196, 106);
                        cout << "D  ";
                    }
                    else if (playergrid.at(i).at(j) == 5){
                        setcolor(233, 196, 106);
                        cout << "C  ";
                    }
                                }
                }
            }
            cout << RESET << endl;
        }
    cout << endl;
}


//Outputs the player's layout of ships
//A for Aircraft Carrier, B for Battleship, S for Submarine, D for Destroyer, C for Cruiser
//~ for water (empty)
void printPlayerGridClient(iostream &client, vector<vector<char>> &printgrid, vector<vector<int>> &playergrid, const int SIZE) {
char axis;
        for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                        if (i == 0 && j == 0) {
                                client << "x";
                        }
                        else if (i == 0 or j == 0) {
                                if (i > 0){
                                        axis = i + 64;
                                }
                                else if (j > 0) {
                                        axis = j + 47;
                                }
                client << axis;
            }
            else {
                if (i > 0 and j > 0) {
                    if (playergrid.at(i).at(j) == 0) {
                        client << "~";
                    }
                    else if (playergrid.at(i).at(j) == 1){
                        client << "A";
                    }
                    else if (playergrid.at(i).at(j) == 2){
                        client << "B";
                    }
                    else if (playergrid.at(i).at(j) == 3){
                        client << "S";
                    }
                    else if (playergrid.at(i).at(j) == 4){
                        client << "D";
                    }
                    else if (playergrid.at(i).at(j) == 5){
                        client << "C";
                    }
                                }
                        }
                }
        }
}

void acceptPlayerGridClient(iostream &server, const int SIZE) {
        string theirs;
        while(true){
                getline(server, theirs);
                if (!server) break;
                cout << theirs << endl;
        }
}


//Prints the shot grid from the perspective of the player firing the shots
void printShootingGrid(vector<vector<char>> &shots) {
    const int SIZE = shots.at(0).size();
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++) {
            if (i == 0 && j == 0) {
                setcolor(95, 15, 64);
                cout << shots.at(i).at(j) << "  ";
            }
            else if (i == 0 or j == 0) {
                setcolor(153, 217, 140);
                cout << shots.at(i).at(j) << "  ";
            }
            else {
                if (i > 0 and j > 0) {
                    if (shots.at(i).at(j) == '-') {
                        setcolor(255, 255, 255);
                        cout << shots.at(i).at(j) << "  ";
                    }
                    else if (shots.at(i).at(j) == '*') {
                        setcolor(200, 5, 5);
                                                cout <<  shots.at(i).at(j) << "  ";
                    }
                    else {
                        setcolor(30, 96, 145);
                        cout << shots.at(i).at(j) << "  ";
                    }
                }
            }
        }
        cout << endl;
    }
    cout << RESET << endl;
}

//Outputs the player's ships AFTER being shot at
//A for Aircraft Carrier, B for Battleship, S for Submarine, D for Destroyer, C for Cruiser
//X for hit ship
//~ for water (empty)
void printPlayerGrid_after (vector<vector<char>> &printgrid, vector<vector<int>> &playergrid, const int SIZE) {
        for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                        if (i == 0 && j == 0) {
                                setcolor(95, 15, 64);
                cout << printgrid.at(i).at(j) << "  ";
            }
                        else if (i == 0 or j == 0) {
                setcolor(153, 217, 140);
                cout << printgrid.at(i).at(j) << "  ";
            }
            else {
                if (i > 0 and j > 0) {
                    if (playergrid.at(i).at(j) == 0) {
                        setcolor(30, 96, 145);
                        cout << "~  ";
                    }
                    else if (playergrid.at(i).at(j) == 1){
                        setcolor(233, 196, 106);
                        cout << "A  ";
                    }
                    else if (playergrid.at(i).at(j) == 2){
                        setcolor(233, 196, 106);
                        cout << "B  ";
                    }
                    else if (playergrid.at(i).at(j) == 3){
                        setcolor(233, 196, 106);
                        cout << "S  ";
                    }
                    else if (playergrid.at(i).at(j) == 4){
                        setcolor(233, 196, 106);
                        cout << "D  ";
                    }
                    else if (playergrid.at(i).at(j) == 5){
                        setcolor(233, 196, 106);
                        cout << "C  ";
                    }
                                        else if (playergrid.at(i).at(j) == 9){
                                                setcolor(200, 5, 5);
                                                cout << "*  ";
                                        }
                                        else if (playergrid.at(i).at(j) == 8) {
                                                setcolor(255, 255, 255);
                                                cout << "-  ";
                                        }
                                }
                }
            }
            cout << RESET << endl;
        }
    cout << endl;
}

void gameOverLose(){
    clearscreen();
    setcolor(124, 181, 24);
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
    setcolor(45, 0, 247);
    cout << "           ##        ##     ###      ##       ##                  " << endl;
    setcolor(106, 0, 244);
    cout << "            #        #     #   #     ##       ##                  " << endl;
    setcolor(137, 0, 242);
    cout << "             #      #     #     #    ##       ##                  " << endl;
    setcolor(161, 0, 242);
    cout << "              ##  ##     #       #   ##       ##                  " << endl;
    setcolor(177, 0, 232);
    cout << "                ##       #       #   ##       ##                  " << endl;
    setcolor(188, 0, 221);
    cout << "                ##        #     #    ##       ##                  " << endl;
    setcolor(209, 0, 209);
    cout << "                ##         #   #      ##     ##                   " << endl;
    setcolor(219, 0, 182);
    cout << "                ##          ###        #######                    " << endl;
    setcolor(229, 0, 164);
    cout << "                                                               " << endl;
    setcolor(242, 0, 137);
    cout << "         ##            #####      #######   #######               " << endl;
        setcolor(229, 0, 164);
    cout << "         ##           #     #     ##        ##                    " << endl;
        setcolor(219, 0, 182);
    cout << "         ##          #       #    ##        ##                    " << endl;
        setcolor(209, 0, 209);
    cout << "         ##          #       #    #######   #######               " << endl;
        setcolor(188, 0, 221);
    cout << "         ##          #       #         ##   ##                    " << endl;
        setcolor(177, 0, 232);
    cout << "         ##           #     #          ##   ##                    " << endl;
        setcolor(161, 0, 242);
    cout << "         ###########   #####      #######   #######               " << endl << endl;
        setcolor(124, 181, 24);
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
    resetcolor();
    exit(1);

}

void gameOverWin(){
    clearscreen();
    setcolor(124, 181, 24);
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
    setcolor(45, 0, 247);
    cout << "           ##        ##     ###      ##       ##                  " << endl;
    setcolor(106, 0, 244);
    cout << "            #        #     #   #     ##       ##                  " << endl;
    setcolor(137, 0, 242);
    cout << "             #      #     #     #    ##       ##                  " << endl;
    setcolor(161, 0, 242);
    cout << "              ##  ##     #       #   ##       ##                  " << endl;
    setcolor(177, 0, 232);
    cout << "                ##       #       #   ##       ##                  " << endl;
    setcolor(188, 0, 221);
    cout << "                ##        #     #    ##       ##                  " << endl;
    setcolor(209, 0, 209);
    cout << "                ##         #   #      ##     ##                   " << endl;
    setcolor(219, 0, 182);
    cout << "                ##          ###        #######                    " << endl;
    setcolor(229, 0, 164);
    cout << "                                                               " << endl;
    setcolor(242, 0, 137);
    cout << "           ##    #    ##   ########    ###      ##                " << endl;
    setcolor(229, 0, 164);
    cout << "           ##    #    ##      ##       ## #     ##                " << endl;
    setcolor(219, 0, 182);
    cout << "            #    #    #       ##       ##  #    ##                " << endl;
    setcolor(209, 0, 209);
    cout << "            #   # #   #       ##       ##   #   ##                " << endl;
    setcolor(188, 0, 221);
    cout << "            ## #   # ##       ##       ##    #  ##                " << endl;
    setcolor(177, 0, 232);
    cout << "             ##     ##        ##       ##     # ##                " << endl;
    setcolor(161, 0, 242);
    cout << "             #       #     ########    ##      ###                " << endl << endl;
    setcolor(124, 181, 24);
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
    resetcolor();
    exit(1);
}


/*
//This function will iterate over the whole map and check to see which ships have been sunk and which still exist. If all ships have been sunk, it will call a game over screen.
//Built for single terminal
void shipStatus(iostream &stream, vector<vector<int>> &playergrid, const int SIZE) {
        bool AIRCRAFT = false;
        bool BATTLESHIP = false;
        bool SUBMARINE = false;
        bool DESTROYER = false;
        bool CRUISER = false;
        bool game_over = true;
        static bool air_SUNK = false;
        static bool bat_SUNK = false;
        static bool sub_SUNK = false;
        static bool des_SUNK = false;
        static bool cru_SUNK = false;

        for (int i = 0; i < SIZE; i++) {
                        for (int j = 0; j < SIZE; j++) {
                                if (playergrid.at(i).at(j) == 1){
                                        AIRCRAFT = true;
                                        game_over = false;
//                  cout << MAGENTA << "ONE" << endl;
                                }
                                else if (playergrid.at(i).at(j) == 2){
                                        BATTLESHIP = true;
                                        game_over = false;
//                  cout << MAGENTA << "TWO" << endl;
                }
                                else if (playergrid.at(i).at(j) == 3){
                        SUBMARINE = true;
                                        game_over = false;
//                  cout << MAGENTA << "THREE" << endl;
                }
                else if (playergrid.at(i).at(j) == 4){
                        DESTROYER = true;
                    game_over = false;
//                  cout << MAGENTA << "FOUR" << endl;
                }
                else if (playergrid.at(i).at(j) == 5){
                        CRUISER = true;
                    game_over = false;
//                  cout << MAGENTA << "FIVE" << endl;
                }
                else continue;
                        }
        }

        if (!AIRCRAFT && air_SUNK == false) {
                        air_SUNK = true;
                        cout << "               You've sunk the Aircraft Carrier!               " << endl << endl;
                        stream << "               You've sunk the Aircraft Carrier!               \n" << endl;
        }
        if (!BATTLESHIP && bat_SUNK == false) {
                        bat_SUNK = true;
                        cout << "               The Battleship has been destroyed!              " << endl << endl;
                        stream << "               The Battleship has been destroyed!              \n" << endl;
        }
        if (!SUBMARINE && sub_SUNK == false) {
                        sub_SUNK = true;
                        cout << "               The Submarine will never resurface!             " << endl << endl;
                        stream << "               The Submarine will never resurface!             \n" << endl;
        }
        if (!DESTROYER && des_SUNK == false) {
                        des_SUNK = true;
                        cout << "                       Bye bye Destroyer!                      " << endl << endl;
                        stream << "                       Bye bye Destroyer!                      \n" << endl;
        }
        if (!CRUISER && cru_SUNK == false) {
                        cru_SUNK = true;
                        cout << "                No more cruising for the Cruiser!              " << endl << endl;
                        stream << "                No more cruising for the Cruiser!              \n" << endl;
        }
        if (game_over){
                        gameOver();
        }

}
*/

void receive_shipStatus(iostream &stream){
        string theirs;
        getline(stream, theirs);
        cout << theirs << endl;
}

//This will trigger the Volleyball/Jeopardy portion of Volleyshipardy
void playJeopardy( bool &playing, vector<question> quiz_base, int &winner) {
        bool streak = true;
        char choice;
        char ans;
        int player = 1;
        int answer;
        int question_idx;
        question current;
        time_t time_start;
        float time_passed;
        float record = 100;

//Allows the answers to show up in a random order
        vector<int> indeces = {0, 1, 2, 3};
        random_shuffle(indeces.begin(), indeces.end());

//Let the games begin
        setcolor(47, 157, 143);
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        resetcolor();
        cout << endl << "Are you ready to play a game?" << endl << endl;
        while (choice != 'n' && choice != 'N' && choice != 'y' && choice != 'Y') {
                cout << "Enter 'y' to play or 'n' to quit: ";
                cin >> choice;
                        cout << endl << endl;
        }
        setcolor(47, 157, 143);
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
        resetcolor();

        if (choice == 'N' or choice == 'n') {
                        exit(1);
        }
        else if (choice == 'Y' or choice == 'y') {
                while (streak) {
                        time_start = time(0); //Starts the timer

                        if (player % 2 == 1) {
                                setcolor(229, 152, 155);
                                cout << "                        ----------                         " << endl;
                                cout << "                        Player One                         " << endl;
                                cout << "                        ----------                         " << endl << endl;
                                resetcolor();
                        }
                        else {
                                setcolor(69, 123, 157);
                                cout << "                        ----------                         " << endl;
                                cout << "                        Player Two                         " << endl;
                                cout << "                        ----------                         " << endl << endl;
                                resetcolor();
                        }

                        cout << "        Answer the question before the time runs out.          " << endl << endl;
                        cout << "              The time to beat is ";
                        setcolor(243, 222, 44);
                        cout << record;
                        resetcolor();
                        cout << " seconds.                  " << endl << endl;

                        //Pulls a random question from the quiz_base
                        question_idx = rand() % quiz_base.size();
                        current = quiz_base.at(question_idx);
            setcolor(47, 157, 143);
                        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                setcolor(152, 82, 119);

                        cout << "                         Question:                             " << endl;
                setcolor(47, 157, 143);
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
                resetcolor();
                        cout << current.quest << endl << endl;
            setcolor(47, 157, 143);
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            setcolor(152, 82, 119);
                        cout << "                      Possible Answers:                        " << endl;
            setcolor(47, 157, 143);
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
            resetcolor();
                        for (size_t i = 0; i < indeces.size(); i++) {
                                char j = i + 65;
                                cout << j << ": " << current.answers.at(indeces.at(i)) << endl;
                        }
                        setcolor(47, 157, 143);
            cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
                        resetcolor();
                        cout <<  "Your Answer: ";
                        cin >> ans;
                        cout << endl;
                        if (ans == 'a' or ans == 'A') {
                                answer = 0;
                        }
                        else if (ans == 'b' or ans == 'B') {
                                answer = 1;
                        }
                        else if (ans == 'c' or ans == 'C') {
                                answer = 2;
                        }
                        else if (ans == 'd' or ans == 'D') {
                                answer = 3;
                        }
                        else {
                                cout << RED << "FOLLOW THE RULES" << endl;
                                EXIT_FAILURE;
                        }
                        if (indeces.at(answer) == 0){
                                time_passed = (time(0) - time_start) ;
                                if (time_passed < record) {
                                        record = time_passed;
                                        setcolor(47, 157, 143);
                        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
                                        resetcolor();
                                        cout << "             ";
                                        setcolor(56, 176, 0);
                                        cout << "--------";
                                        setcolor(255, 255, 255);
                                        cout << " That's Correct! ";
                                        setcolor(56, 176, 0);
                                        cout << "--------";
                                        cout << "             " << endl << endl;
                                        setcolor(255, 255, 255);
                                        cout << "                You answered in: ";
                                        setcolor(243, 222, 44);
                                        cout << time_passed;
                                        setcolor(255, 255, 255);
                                        cout << " seconds.                " << endl << endl;
                                        setcolor(47, 157, 143);
                                        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
                                        resetcolor();
                                }
                                else {
                                        streak = false;

                        setcolor(47, 157, 143);
                        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
                        resetcolor();
                        cout << "          ";
                        setcolor(214, 40, 40);
                        cout << "--------";
                        setcolor(255, 255, 255);
                        cout << " You ran out of time! ";
                        setcolor(214, 40, 40);
                        cout << "--------";
                        cout << "              " << endl << endl;
                        setcolor(255, 255, 255);
                                cout << "               You answered in: ";
                        setcolor(243, 222, 44);
                            cout << time_passed;
                            setcolor(255, 255, 255);
                        cout << " seconds.                " << endl;
                        cout << "            ";
                                        cout << " The time to beat was ";
                                        setcolor(243, 222, 44);
                                        cout << record;
                                        setcolor(255, 255, 255);
                                        cout << " seconds.            " << endl << endl;
                        setcolor(47, 157, 143);
                            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
                            resetcolor();

                    if (player % 2 == 1) {
                                                winner = 2;
                        setcolor(47, 157, 143);
                                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
                                                setcolor(229, 152, 155);
                            cout << "               Player 1 dropped the ball.                      " << endl << endl;
                                                resetcolor();
                        setcolor(47, 157, 143);
                                    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
                        resetcolor();
                                        }
                    else {
                                                winner = 1;
                        setcolor(47, 157, 143);
                        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
                            setcolor(69, 123, 157);
                        cout << "               Player 2 dropped the ball.                      " << endl << endl;
                            resetcolor();
                        setcolor(47, 157, 143);
                        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
                        resetcolor();
                                        }

                                }
                        }
                        else {
                                time_passed = (time(0) - time_start);
                                if (time_passed < record) {
                                        streak = false;

                    setcolor(47, 157, 143);
                    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
                    resetcolor();
                    cout << "             ";
                    setcolor(214, 40, 40);
                    cout << "--------";
                    setcolor(255, 255, 255);
                    cout << " That's Wrong! ";
                    setcolor(214, 40, 40);
                    cout << "--------";
                    cout << "             " << endl << endl;
                    setcolor(255, 255, 255);
                    cout << "  The correct answer was: ";
                    setcolor(243, 222, 44);
                    cout << current.answers.at(0) << endl << endl;
                    setcolor(47, 157, 143);
                    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
                    resetcolor();

                                        if (player % 2 == 1) {
                                                winner = 2;
                        setcolor(47, 157, 143);
                        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
                        setcolor(229, 152, 155);
                        cout << "               Player 1 dropped the ball.                      " << endl << endl;
                        resetcolor();
                        setcolor(47, 157, 143);
                        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
                                                resetcolor();
                                        }
                                        else {
                                                winner = 1;
                        setcolor(47, 157, 143);
                            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
                        setcolor(69, 123, 157);
                            cout << "               Player 2 dropped the ball.                      " << endl << endl;
                        resetcolor();
                        setcolor(47, 157, 143);
                            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
                                                resetcolor();
                                        }
                                }
                                else {
                                        streak = false;

                    setcolor(47, 157, 143);
                    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
                    resetcolor();
                    cout << "   ";
                    setcolor(214, 40, 40);
                    cout << "--------";
                    setcolor(255, 255, 255);
                    cout << " You ran out of time AND you were wrong! ";
                    setcolor(214, 40, 40);
                    cout << "--------";
                    cout << "       " << endl << endl;
                    setcolor(255, 255, 255);
                    cout << "  The correct answer was: ";
                    setcolor(243, 222, 44);
                    cout << current.answers.at(0) << endl << endl;
                    setcolor(47, 157, 143);
                    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
                    resetcolor();

                                        if (player % 2 == 1) {
                                                winner = 2;
                        setcolor(47, 157, 143);
                        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
                        setcolor(229, 152, 155);
                        cout << "               Player 1 dropped the ball.                      " << endl << endl;
                        resetcolor();
                        setcolor(47, 157, 143);
                        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
                                                resetcolor();
                    }
                    else {
                                                winner = 1;
                        setcolor(47, 157, 143);
                        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
                        setcolor(69, 123, 157);
                        cout << "               Player 2 dropped the ball.                      " << endl << endl;
                        resetcolor();
                        setcolor(47, 157, 143);
                        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
                                                resetcolor();
                    }
                                }
                        }
                        player++;
                }
        }
}

//Allows the player to shoot 1 shot at the opponents map
//Called by the player being shot AT
void shootAtMe(ostream &outs, iostream &opponent, int row, int col, vector<vector<int>> &playergrid) {
        string ours;
        if (playergrid.at(row).at(col) != 0) {
                setcolor(47, 157, 143);
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
                resetcolor();
                outs << "                      You've been hit.\n";
/*       setcolor(47, 157, 143);
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
        resetcolor();
*/
                ours =  "That's a hit!\n";
                playergrid.at(row).at(col) = 9;
        }
        else {
        setcolor(47, 157, 143);
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
        resetcolor();
                outs << "                        They missed.\n\n";
        setcolor(47, 157, 143);
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
        resetcolor();
                ours =  "   Splash!\n";
                playergrid.at(row).at(col) = 8;
        }
        opponent << ours;

        //THE FOLLOWING SECTION WILL LET THE PLAYERS KNOW IF A SHIP HAS BEEN SUNK

        bool AIRCRAFT = false;
        bool BATTLESHIP = false;
        bool SUBMARINE = false;
        bool DESTROYER = false;
        bool CRUISER = false;
        bool game_over = true;
        static bool air_SUNK = false;
        static bool bat_SUNK = false;
        static bool sub_SUNK = false;
        static bool des_SUNK = false;
        static bool cru_SUNK = false;

        for (int i = 0; i < 11; i++) {
                        for (int j = 0; j < 11; j++) {
                                if (playergrid.at(i).at(j) == 1){
                                        AIRCRAFT = true;
                                        game_over = false;
//                  cout << MAGENTA << "ONE" << endl;
                                }
                                else if (playergrid.at(i).at(j) == 2){
                                        BATTLESHIP = true;
                                        game_over = false;
//                  cout << MAGENTA << "TWO" << endl;
                }
                                else if (playergrid.at(i).at(j) == 3){
                        SUBMARINE = true;
                                        game_over = false;
//                  cout << MAGENTA << "THREE" << endl;
                }
                else if (playergrid.at(i).at(j) == 4){
                        DESTROYER = true;
                    game_over = false;
//                  cout << MAGENTA << "FOUR" << endl;
                }
                else if (playergrid.at(i).at(j) == 5){
                        CRUISER = true;
                    game_over = false;
//                  cout << MAGENTA << "FIVE" << endl;
                }
                else continue;
                        }

        }

        if (!AIRCRAFT && air_SUNK == false) {
                        air_SUNK = true;
                        cout << "               You've sunk the Aircraft Carrier!               " << endl;
                        ours = "               You've sunk the Aircraft Carrier!               \n";
        }
                else if (!BATTLESHIP && bat_SUNK == false) {
                        bat_SUNK = true;
                        cout << "               The Battleship has been destroyed!              " << endl;
                        ours = "               The Battleship has been destroyed!              \n";
        }
                else if (!SUBMARINE && sub_SUNK == false) {
                        sub_SUNK = true;
                        cout << "               The Submarine will never resurface!             " << endl;
                        ours = "               The Submarine will never resurface!             \n";
        }
                else if (!DESTROYER && des_SUNK == false) {
                        des_SUNK = true;
                        cout << "                       Bye bye Destroyer!                      " << endl;
                        ours = "                       Bye bye Destroyer!                      \n";
        }
                else if (!CRUISER && cru_SUNK == false) {
                        cru_SUNK = true;
                        cout << "                No more cruising for the Cruiser!              " << endl;
                        ours = "                No more cruising for the Cruiser!              \n";
        }
                else {
                        ours = "               You didn't sink any ships this time             \n";
                }
                        //
                opponent << ours;

        setcolor(47, 157, 143);
        cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
        resetcolor();



        if (game_over){
                        gameOverLose();
        }
}

//Allows the player to shoot 1 shot at the opponent map
//Call by the player SHOOTING
void shooter(ostream &outs, iostream &opponent, int row, int col, vector<vector<char>> &shots, int &counter){
        string theirs;
        getline(opponent, theirs);
        cout << "                         " << theirs << endl;
        /*
    setcolor(47, 157, 143);
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
    resetcolor();
        */
        if (theirs == "That's a hit!"){
                shots.at(row).at(col) = '*';
                counter += 1;
        }
        else {
                shots.at(row).at(col) = '-';
        }

        //RECEIVES THE MESSAGE THAT A SHIP HAS BEEN SUNK
        getline(opponent, theirs);
        cout << theirs << endl <<  endl;
    setcolor(47, 157, 143);
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
    resetcolor();

        if (counter == 17) gameOverWin();
}

//Collects location opponent is firing at
void collectLocation(iostream &opponent, int &row, int &col){
        opponent >> row;
        opponent >> col;
//      cout << row << "**" << col; //debugging strings
}

//Sends location to fire at
void sendLocation(iostream &opponent, int row, int col){
        opponent << row << endl;
        opponent << col << endl;
}


//Allows the player to shoot 3 shots at the opponents map
//Built for single terminal game
/*void shoot3(vector<vector<int>> &playergrid, vector<vector<char>> &shots, bool &stillPlaying) {
    char row, col;
    const int size = playergrid.at(0).size();

    for (int i = 0; i < 3; i++) {
        cout << "Choose a location to fire at in the format 'A 4'." << endl << endl;
        printShootingGrid(shots);
        cout << "Location: ";
        cin >> row >> col;
        row = toupper(row);
        cout << endl;

        int rowInd = row - 64;
        int columnInd = col - 47;
        if (playergrid.at(rowInd).at(columnInd) != 0) {
            setcolor(143, 37, 12);
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
            resetcolor();
            cout << BOLDRED << "                         That's a hit!                         " << endl << endl;
            playergrid.at(rowInd).at(columnInd) = 0;
            shots.at(rowInd).at(columnInd) = '*';
            shipStatus(playergrid, size); //Lets you know if you've sunk a ship
            cout << RESET;
            setcolor(143, 37, 12);
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            resetcolor();
        }
        else {
            setcolor(30, 96, 145);
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
            resetcolor();
            cout << CYAN << "                           Splash!                             " << RESET << endl << endl;
            setcolor(30, 96, 145);
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
            resetcolor();
            shots.at(rowInd).at(columnInd) = '-';
        }
    }
}
*/

void placeShips(vector<vector<int>> &playergrid, vector<bool> &availableships, const int SIZE) {
        int ship;
        int size;
        char row, col;
        int rowInd, colInd;
        char direction;
                bool valid_spot = true;
        int AIRCRAFT_CARRIER = 1;
        int BATTLESHIP = 2;
        int SUBMARINE = 3;
        int DESTROYER = 4;
        int CRUISER = 5;

        vector<string> ships = {"1: Aircraft Carrier", "2: Battleship", "3: Submarine", "4: Destroyer", "5: Cruiser"};

//Checks to see which ships the player still needs to place, and outputs the strings to represent the ones left
        cout << "Which ship would you like to place?" << endl;
        for (size_t i = 0; i < ships.size(); i++) {
                if (availableships.at(i) == true) {
                        cout << "    " << ships.at(i) << endl;
                }
        }
        cout << endl;
        ship = read("Ship: ");

        while (ship != AIRCRAFT_CARRIER and ship != BATTLESHIP and ship != SUBMARINE and ship != DESTROYER and ship != CRUISER) {
                ship = read("Please enter the number of the ship you'd like to place.\nShip: ");
        cout << endl;
        }

        cout << endl;

        if (ship == AIRCRAFT_CARRIER) {
            size = 5;
            setcolor(47, 157, 143);
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            resetcolor();
            cout << "You are placing the Aircraft Carrier. \nIt is 5 units long. \nChoose where you'd like to place the top-left corner of the ship in the format 'A 4'." << endl;
            setcolor(47, 157, 143);
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            resetcolor();
        }
        else if (ship == BATTLESHIP) {
                size = 4;
                    setcolor(47, 157, 143);
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                resetcolor();
                cout << "You are placing the Battleship. \nIt is 4 units long. \nChoose where you'd like to place the top-left corner of the ship in the format 'A 4'." << endl;
                setcolor(47, 157, 143);
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                resetcolor();
        }
        else if (ship == SUBMARINE) {
                size = 3;
                setcolor(47, 157, 143);
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                resetcolor();
                cout << "You are placing the Submarine. \nIt is 3 units long. \nChoose where you'd like to place the top-left corner of the ship in the format 'A 4'." << endl;
            setcolor(47, 157, 143);
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                resetcolor();
        }
        else if (ship == DESTROYER) {
                size = 3;
                setcolor(47, 157, 143);
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                resetcolor();
                cout << "You are placing the Destroyer. \nIt is 3 units long. \nChoose where you'd like to place the top-left corner of the ship in the format 'A 4'." << endl;
                setcolor(47, 157, 143);
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                resetcolor();
        }
        else if (ship == CRUISER) {
                size = 2;
                setcolor(47, 157, 143);
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                resetcolor();
                cout << "You are placing the Cruiser. \nIt is 2 units long. \nChoose where you'd like to place the top-left corner of the ship in the format 'A 4'." << endl;
                setcolor(47, 157, 143);
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                resetcolor();
        }

//This doesn't currently vet that the location is valid.. Just follow the rules.
        cout << "Location: ";
        cin >> row >> col;
        row = toupper(row);
        rowInd = row - 64;
        colInd = col - 47;
                row = tolower(row);
//      cout << "You chose row " << row << " column " << col << endl;

                cout << "Would you like to place it horizontally or vertically?" << endl << endl
                        << "Direction (Please enter 'H' or 'V': ";
        cin >> direction;
        cout << endl;
                while (direction != 'h' and direction != 'H' and direction != 'v' and direction != 'V') {
                        cout << BOLDRED << "That's not a valid direction." << RESET << endl;
                        cout << "Would you like to place it horizontally or vertically?" << endl << endl
                                << "Direction (Please enter 'H' or 'V': ";
                        cin >> direction;
                        cout << endl;
                }

        if (direction == 'H' or direction == 'h') {
                        if (colInd + size > SIZE) {
                                cout << BOLDRED <<  "Your ship doesn't fit there!" << RESET << endl << endl;
            }
            else {
                                for (int i = colInd; i < colInd + size; i++) {
                                        if (playergrid.at(rowInd).at(i) != 0) {
                                                valid_spot = false;
                                        }
                                }
                                if (valid_spot){
                                        for (int i = colInd; i < colInd + size; i++) {
                                                playergrid.at(rowInd).at(i) = ship;
                                        }
                                        availableships.at( ship - 1 ) = false;
                                }
                                else {
                                        cout << BOLDRED << "Sorry, your ships can't overlap." << RESET << endl << endl;
                                }
                        }
        }
        else if (direction == 'V' or direction == 'v') {
                        if (rowInd + size > SIZE) {
                                cout << BOLDRED << "Your ship doesn't have enough space there!" << RESET << endl << endl;
                        }
                        else {
                for (int i = rowInd; i < rowInd + size; i++) {
                    if (playergrid.at(i).at(colInd) != 0) {
                        valid_spot = false;
                    }
                }
                                if (valid_spot){
                                        for (int i = rowInd; i < rowInd + size; i++) {
                                                playergrid.at(i).at(colInd) = ship;
                                        }
                                        availableships.at( ship - 1 ) = false;
                                }
                                else {
                                        cout << BOLDRED << "Sorry, your ships can't overlap." << RESET << endl << endl;
                                }
                        }
        }
}

//Asks the players if they want to play and quits if either says no.
void gameStart(ostream &outs, iostream &client){
        char choice;
        setcolor(47, 157, 143);
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"  << endl;
        resetcolor();
    client << CYAN <<  "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << RESET;
    cout << "                      Do you want to play?                       " << endl;
        setcolor(47, 157, 143);
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        resetcolor();
    cout << "Enter 'y' to play or 'n' to quit: " << endl;
        while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') {
                cout << "Choice: " ;
                cin >> choice;
        }
        if (choice == 'n' or choice == 'N') {
                exit(1);
        }
        else {
                client  << "               A friend wants to play a game with you.         \n";
        client << CYAN << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << RESET;
                client << "Enter 'y' to play or 'n' to quit: " << endl;
        }
}


//This will print the rules of volleyshipardy to both cout and the client
void printRules(ostream &outs, iostream &client){
//RULES TO COUT
    setcolor(47, 157, 143);
    outs << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    resetcolor();
    outs << "                  The rules are as follows:                    " << endl;
    setcolor(47, 157, 143);
    outs << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
    resetcolor();
    outs << "Each player will begin by placing their ships on a 10x10 grid." << endl << endl;
    outs << "After both players have positioned their ships, the Jeopardy/Volleyball \nround will begin." << endl << endl;
    outs << "During this round, the players will 'volley' a trivia question." << endl << endl;
    outs << "For example: Player 1 has 100 seconds to answer the first question." << endl << endl;
    outs << "If they answer correctly in 10 seconds, the 'ball' will pass to the other player." << endl << endl;
    outs << "Player 2 will now have 10 seconds to answer that question correctly." << endl << endl;
    outs << "If they do so, the question will 'volley' back to Player 1, who now has \nto answer the question in less than 10 seconds." << endl << endl;
    outs << "Once a player 'drops the ball', the player who did not drop the ball will \nbe allowed to fire 3 shots at the the player that dropped the ball's battleships." << endl << endl;
    outs << "If they sink all of the other player's ships during the firing round, the game is over." << endl << endl;
    outs << "Otherwise, the players will re-enter the Jeopardy/Volleyball phase of the game." << endl << endl;
    outs << "This repeats until one player has lost all of their battleships." << endl << endl;
    setcolor(47, 157, 143);
    outs << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
    resetcolor();

//RULES TO THE CLIENT
    setcolor(47, 157, 143);
    client << CYAN <<  "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << RESET;
    client << "                  The rules are as follows:                    \n";
    client << CYAN << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << RESET;
    client << "Each player will begin by placing their ships on a 10x10 grid.\n";
    client << "After both players have positioned their ships, the Jeopardy/Volleyball round will begin.\n";
    client << "During this round, the players will 'volley' a trivia question.\n";
    client << "For example: Player 1 has 100 seconds to answer the first question.\n";
    client << "If they answer correctly in 10 seconds, the 'ball' will pass to the other player.\n";
    client << "Player 2 will now have 10 seconds to answer that question correctly.\n";
    client << "If they do so, the question will 'volley' back to Player 1, who now has to answer the question in less than 10 seconds.\n";
    client << "Once a player 'drops the ball', the player who did not drop the ball will be allowed to fire 3 shots at the the player that dropped the ball's battleships.\n";
    client << "If they sink all of the other player's ships during the firing round, the game is over.\n";
    client << "Otherwise, the players will re-enter the Jeopardy/Volleyball phase of the game.\n";
    client << "This repeats until one player has lost all of their battleships.\n";
    client << CYAN << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << RESET;
        resetcolor();
}

//Prints the rules for battleship to the players
void printBattleRules(ostream &outs){
//TO COUT
        setcolor(47, 157, 143);cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
        resetcolor();
        cout << "Each player will be able to place their ships on a 10x10 grid.\n";
        cout << "You can only place ships vertically or horizontally." << endl;
        cout << "Your fleet of ships consists of the following: " << endl
                << "1 Aircraft Carrier: 5 spaces" << endl
                << "1 Battleship: 4 spaces" << endl
                << "1 Submarine: 3 spaces" << endl
                << "1 Destroyer: 3 spaces" << endl
                << "1 Cruiser: 2 spaces" << endl << endl;
        setcolor(47, 157, 143);
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
        resetcolor();

}

//Asks the players if they want to play and quits if either says no.
void jeopStart(ostream &outs, iostream &client){
        char choice;
        setcolor(47, 157, 143);
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"  << endl;
        resetcolor();
    client << CYAN <<  "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << RESET;
    cout << "                      Ready for Volleypardy?                       " << endl;
        setcolor(47, 157, 143);
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        resetcolor();
    cout << "Enter 'y' to play or 'n' to quit: " << endl;
        while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') {
                cout << "Choice: " ;
                cin >> choice;
        }
        if (choice == 'n' or choice == 'N') {
                exit(1);
        }
        else {
                client  << "               Your friend is ready for volleypardy.         \n";
        client << CYAN << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << RESET;
                client << "Enter 'y' to play or 'n' to quit: " << endl;
        }
}

