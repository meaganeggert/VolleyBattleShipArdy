#include <fstream>
#include <iostream>
#include "read.h"
#include "colors.h"
#include <unordered_map>
#include <time.h>
#include <ctime>
#include <algorithm>
#include <vector>

using namespace std;

struct question {
        string quest;
        vector<string> answers;
};


//Bravo, megan. This is the best looking documentaion I have seen in a while, all I did was add read.h and colors.h to your local directory..
//- Alex~

//This function will iterate over the whole map and check to see which ships have been sunk and which still exist. If all ships have been sunk, it will call a game over screen.
void shipStatus(vector<vector<int>> &playergrid, const int SIZE);

//Game Over Screen
void gameOver();

//Prints the shot grid from the perspective of the player firing the shots
void printShootingGrid(vector<vector<char>> &shots);

//Allows the player to shoot 3 shots at the opponents map
void shoot3(vector<vector<int>> &playergrid, vector<vector<char>> &shots);

//This function works to place ships on a player's map. It works okay for making sure that the ship will fit on the map, but it does not currently account for ships running into other ships.
void placeShips(vector<vector<int>> &playergrid, vector<bool> &availableships, const int SIZE);

//Outputs the player's layout of ships
//A for Aircraft Carrier, B for Battleship, S for Submarine, D for Destroyer, C for Cruiser
//~ for water (empty)
void printPlayerGrid(vector<vector<char>> &printgrid, vector<vector<int>> &playergrid, const int SIZE);

//This function just prints the world map.
void printMap(vector<vector<char>> &grid, const int SIZE);

//This will trigger the Volleyball/Jeopardy portion of Volleyshipardy
void playJeopardy( bool &playing, vector<question> quiz_base, int &winner);

int main() {
        srand(time(NULL));

        ifstream bank;
        string line, tempQ, tempA, tempB, tempC, tempD;
        vector<question> quiz_base;
        char add;
        string temp;

//BEGIN JEOPARDY INITIAL SETUP
//Creates the question database from the text file
        bank.open("questions.txt");
        while (bank) {
                //Reads the first line for the question then vets the line to appropriately account for the "cramped" newline characters in the text file
                getline(bank, temp);
                for (size_t i = 0; i < temp.length(); i++) {
                        add = temp.at(i);
                        if (add == '\\'){
                                i++;
                                line += " \n";
                        }
                        else {
                                line += add;
                        }
                }
                tempQ = line;
                //Answer A: Correct!
                getline(bank, line);
                tempA = line;
                //Answer B: Wrong
                getline(bank, line);
                tempB = line;
                //Answer C: Wrong
                getline(bank, line);
                tempC = line;
                //Answer D: Wrong
                getline(bank, line);
                tempD = line;
                //Skip the blanks
                getline(bank, line);
                //Add the whole question to the quiz database
                question temp = {tempQ, {tempA, tempB, tempC, tempD}};
                quiz_base.push_back(temp);
        }
        bank.close();
//END JEOPARDY INITIAL SETUP


        char choice;


//BATTLESHIP INITIAL SETUP
        const int SIZE = 11;
        const int TOTAL_SHIPS = 5;

//Blank world map
    vector<vector<char>> world_map(SIZE, vector<char>(SIZE, '~'));

//Holds the players ship placement with integers representing the different ships
    //1: Aircraft Carrier
    //2: Battleship
    //3: Submarine
    //4: Destroyer
    //5: Submarine
    vector<vector<int>> player1(SIZE, vector<int>(SIZE, 0));
    vector<vector<int>> player2(SIZE, vector<int>(SIZE, 0));

//Holds the players shots against their opponent
    vector<vector<char>> shots_on_1(SIZE, vector<char>(SIZE, '~'));
    vector<vector<char>> shots_on_2(SIZE, vector<char>(SIZE, '~'));

// Keeps track of whether or not the player still has more ships to place
    vector<bool> player1_ships(TOTAL_SHIPS, true);
    vector<bool> player2_ships(TOTAL_SHIPS, true);
    bool has_ships = true;

//Build starting map & shooting maps  with the labeled axes. (Columns 0-9, Rows A-J)
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            char row = i + 64;
            char col = j + 47;

            if (i == 0 and j == 0) {
                world_map.at(i).at(j) = 'x';
                shots_on_1.at(i).at(j) = 'x';
                shots_on_2.at(i).at(j) = 'x';
            }
            else {
                if (i > 0 and j > 0) {
                    world_map.at(0).at(j) = col;
                    world_map.at(i).at(0) = row;
                    shots_on_1.at(0).at(j) = col;
                    shots_on_1.at(i).at(0) = row;
                    shots_on_2.at(0).at(j) = col;
                    shots_on_2.at(i).at(0) = row;
                }
                else continue;
            }
        }
    }
//END BATTLESHIP INITIAL SETUP

//VOLLEYSHIPARDY
        system("figlet Volleyshipardy | lolcat");
    setcolor(47, 157, 143);
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    resetcolor();
    cout << "                  The rules are as follows:                    " << endl;
    setcolor(47, 157, 143);
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
    resetcolor();
        cout << "Each player will begin by placing their ships on a 10x10 grid." << endl << endl;
        cout << "After both players have positioned their ships, the Jeopardy/Volleyball \nround will begin." << endl << endl;
        cout << "During this round, the players will 'volley' a trivia question." << endl << endl;
        cout << "For example: Player 1 has 100 seconds to answer the first question." << endl << endl;
        cout << "If they answer correctly in 10 seconds, the 'ball' will pass to the other player." << endl << endl;
        cout << "Player 2 will now have 10 seconds to answer that question correctly." << endl << endl;
        cout << "If they do so, the question will 'volley' back to Player 1, who now has \nto answer the question in less than 10 seconds." << endl << endl;
        cout << "Once a player 'drops the ball', the player who did not drop the ball will \nbe allowed to fire 3 shots at the the player that dropped the ball's battleships." << endl << endl;
        cout << "If they sink all of the other player's ships during the firing round, the game is over." << endl << endl;
        cout << "Otherwise, the players will re-enter the Jeopardy/Volleyball phase of the game." << endl << endl;
        cout << "This repeats until one player has lost all of their battleships." << endl << endl;
    setcolor(47, 157, 143);
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
    resetcolor();
        cout << "                  Would you like to play?                      " << endl << endl;
    setcolor(47, 157, 143);
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
    resetcolor();

        while (choice != 'n' && choice != 'N' && choice != 'y' && choice != 'Y') {
                cout << "Enter 'y' to play or 'n' to quit: ";
                cin >> choice;
                cout << endl << endl;
        }

        if (choice == 'n' or choice == 'N') exit(1);
        else {
                clearscreen();
                system("figlet Battleship | lolcat");

            setcolor(47, 157, 143);
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
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


//Player 1's turn to place all their ships. It will loop and call the function until there are no more ships available to place.
            cout << "                     Player 2, " << BOLDRED << "LOOK AWAY!                       " << RESET << endl;
        cout << "               Player 1, please place your ships.               " << endl << endl;

        printMap(world_map, SIZE);


        while (has_ships) {
                placeShips(player1, player1_ships, SIZE);
                printPlayerGrid(world_map, player1, SIZE);

                for (int i = 0; i < TOTAL_SHIPS; i++){
                if (player1_ships.at(i) == true) {
                        has_ships = true;
//                      cout << "has_ships: " << has_ships << endl;
                        break;
                }
                else {
                        has_ships = false;
                }
                }
        }

        has_ships = true;
        clearscreen();

        setcolor(47, 157, 143);
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
        resetcolor();
        setcolor(229, 152, 155);
        cout << "                PLAYER 1'S SHIPS HAVE BEEN PLACED              " << endl << endl;
        resetcolor();
        setcolor(47, 157, 143);
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

//Player 2's turn to place all their ships. It will loop and call the function until there are no more ships available to place.
        cout << "                     Player 1, " << BOLDRED << "LOOK AWAY!                       " << RESET << endl;
        cout << "               Player 2, please place your ships.               " << endl << endl;

        printMap(world_map, SIZE);

        while (has_ships) {
                placeShips(player2, player2_ships, SIZE);
                printPlayerGrid(world_map, player2, SIZE);

                for (int i = 0; i < TOTAL_SHIPS; i++){
                if (player2_ships.at(i) == true) {
                        has_ships = true;
//                      cout << "has_ships: " << has_ships << endl;
                        break;
                }
                else {
                        has_ships = false;
                }
                }
        }
                clearscreen();
        setcolor(47, 157, 143);
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
        resetcolor();
        setcolor(69, 123, 157);
        cout << "                PLAYER 2'S SHIPS HAVE BEEN PLACED              " << endl << endl;
        resetcolor();
        setcolor(47, 157, 143);
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

                int round_winner = 0;
                bool playing = true;
                while (playing){
                        system("figlet Volleypardy | lolcat");
                        playJeopardy(playing, quiz_base, round_winner);
                        system("figlet Battleship | lolcat");
                        if (round_winner == 1) {
                                shoot3(player2, shots_on_2);
                        }
                        else if (round_winner == 2) {
                                shoot3(player1, shots_on_1);
                        }
                    setcolor(47, 157, 143);
                        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                    resetcolor();
                cout << "              Get ready for the trivia round.                  " << endl;
            setcolor(47, 157, 143);
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
            resetcolor();
                        cout << "Enter 'y' to continue or 'n' to quit: ";
                        cin >> choice;
                        cout << endl;

                        while (choice != 'n' && choice != 'N' && choice != 'y' && choice != 'Y') {
                        cout << "Enter 'y' to continue or 'n' to quit: ";
                        cin >> choice;
                }

                        if (choice == 'n' or choice == 'N') {
                                exit(1);
                        }
                        else if (choice == 'y' or choice == 'Y') {
                                clearscreen();
                        }
                }
        }
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

//Allows the player to shoot 3 shots at the opponents map
void shoot3(vector<vector<int>> &playergrid, vector<vector<char>> &shots) {
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
                        setcolor(233, 196, 106);
                        cout << shots.at(i).at(j) << "  ";
                    }
                    else if (shots.at(i).at(j) == '*') {
                        cout << BOLDRED << shots.at(i).at(j) << "  ";
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

//This function works to place ships on a player's map. It works okay for making sure that the ship will fit on the map, but it does not currently account for ships running into other ships.
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

//This function will iterate over the whole map and check to see which ships have been sunk and which still exist. If all ships have been sunk, it will call a game over screen.
void shipStatus(vector<vector<int>> &playergrid, const int SIZE) {
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
        }
        if (!BATTLESHIP && bat_SUNK == false) {
                        bat_SUNK = true;
                        cout << "               The Battleship has been destroyed!              " << endl << endl;
        }
        if (!SUBMARINE && sub_SUNK == false) {
                        sub_SUNK = true;
                        cout << "               The Submarine will never resurface!             " << endl << endl;
        }
        if (!DESTROYER && des_SUNK == false) {
                        des_SUNK = true;
                        cout << "                       Bye bye Destroyer!                      " << endl << endl;
        }
        if (!CRUISER && cru_SUNK == false) {
                        cru_SUNK = true;
                        cout << "                No more cruising for the Cruiser!              " << endl << endl;
        }
        if (game_over){
                        gameOver();
        }

}

void gameOver(){
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
