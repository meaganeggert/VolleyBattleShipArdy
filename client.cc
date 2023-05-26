#include <fstream>
#include <iostream>
#include "/public/read.h"
#include "/public/colors.h"
#include <unordered_map>
#include <time.h>
#include <ctime>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdlib>
#include <boost/asio.hpp>
#include "function.h"


using namespace std;
using boost::asio::ip::tcp;

void test_function(iostream &stream) {
                stream << "hello schoolbus" << endl;
}

void playBattleship_loser(vector<vector<char>> &shots_on, vector<vector<int>> &playergrid, iostream &stream);

int main(int argc, char* argv[])
{
                string theirs;
                string ours;
                int their_int;
                int our_int;
                char their_char;
                char our_char;

        try
        {
                //LET THE GAMES BEGIN
    srand(time(NULL));

    ifstream bank;
    string line, tempQ, tempA, tempB, tempC, tempD;
    vector<question> quiz_base;
    char add;
    string temp;

        system("figlet Volleypardy | lolcat");

//JEOPARDY INITIAL SETUP
//Creates the question database form the text file
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
        char clientchoice;

//BATTLESHIP INITIAL SETUP
        const int SIZE = 11;
        const int TOTAL_SHIPS = 5;
                int counter = 0;

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


                /*
                if (argc != 3)
                {
                        cerr << "Usage: daytime_client <host> <port>" << endl;
                        return EXIT_FAILURE;
                }
                */

//              tcp::iostream s(argv[1], argv[2]); //[1] == host, [2] == port
                tcp::iostream server("localhost", "3737"); //[1] == host, [2] == port
                if (!server) //Connection failed
                {
                        cout << "Unable to connect: " << server.error().message() << endl;
                        return EXIT_FAILURE;
                }

//----------------------------------------------------------------------//
//LET THE GAMES BEGIN

                bool waiting = false;

        //RULES FUNCTION
                acceptRules(server);
//              cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                cout << "                       Please Wait..                            " << endl << endl;
//              cout << "a" << endl; //These are just debugging strings
        //GAME START
                startResponse(server);
                cout << "Choice: ";
                cin >> ours;
                server << ours;
                if (ours == "n" or ours == "N") {
                        exit(1);
                }

        //WAIT FOR PLAYER 1 TO PLACE SHIPS

                cout << CYAN << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n" << RESET;
                cout << "                       Please Wait..                            "  << endl;
                cout << MAGENTA <<  "               Player 1" << RESET << " is placing their ships.                 " << endl << endl;
                cout << CYAN << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n" << RESET;

        //PLAYER 1 IS FINISHED
                getline(server, theirs);
                cout << "               " << theirs << endl << endl;
                cout << CYAN << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n" << RESET;

        //YOUR TURN TO PLACE SHIPS
//              clientShipResponse(server);

        while(has_ships) {
                        placeShips(player2, player2_ships, SIZE);
                        printPlayerGrid(world_map, player2, SIZE);

                        for (int i = 0; i < TOTAL_SHIPS; i++){
                if (player2_ships.at(i) == true) {
                    has_ships = true;
                    break;
                }
                else {
                    has_ships = false;
                }
            }
                }

        cout << CYAN << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"  << RESET << endl;
        cout << "                 Your ships have been placed                   " << endl;
        cout << CYAN << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"  << RESET << endl << endl;

                server << " has placed their ships.\n";

                clearscreen();
/*
//OPPONENT SHOOTING WAITING SCREEN
                cout << CYAN << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"  << RESET << endl << endl;
        cout << "                 Player 1 is shooting at you!                  " << endl << endl;
        cout << CYAN << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"  << RESET << endl << endl;
*/

/*
        //OPPONENT FIRING AT US. WORKS AS EXPECTED.
                playBattleship_loser(shots_on_2, player2, server);
                playBattleship_loser(shots_on_2, player2, server);
                playBattleship_loser(shots_on_2, player2, server);
                playBattleship_loser(shots_on_2, player2, server);
                playBattleship_loser(shots_on_2, player2, server);
                playBattleship_loser(shots_on_2, player2, server);
*/

//BEGIN JEOPARDY GAME-PLAY SET UP
        bool streak = true;
        char ans;
        int player = 1;
        int answer;
        int question_idx;
        question current;
        time_t time_start;
        float time_passed;
        float record = 100;

        system("figlet Volleypardy | lolcat");
//Allows the answers to show up in a random order
        vector<int> indeces = {0, 1, 2, 3};
        random_shuffle(indeces.begin(), indeces.end());


//JEOPARDY START
        startResponse(server);
        cout << "Choice: ";
        cin >> ours;
        server << ours;
        if (ours == "n" or ours == "N") {
            exit(1);
        }

        //EVERYTHING UP UNTIL WORKS SYMMETRICALLY


//----------------------------------------------------------------------//

//This will allow users to chat back and forth
                /*
                while(true){

                        getline(server, theirs);
                        if(!server) break;

                        cout << MAGENTA << "Meagan: " << RESET << theirs << endl;
                        cout << CYAN << "Ray: " << RESET;
                        getline(cin, ours);
                        server << ours << endl;
                }
                */

//Sends a pre-made message back to the server while(true)
                /*
                   while(true){
                        string message;
                        getline(server, message);
                        if (!server) break;
                        cout << message << endl;
                        test_function(server);
                }
                */
        }
        catch (exception& e)
        {
                cout << "Exception: " << e.what() << endl;
        }
}

void playBattleship_loser(vector<vector<char>> &shots_on, vector<vector<int>> &playergrid, iostream &stream){
    for (int j = 0; j < 3; j++){
        int rowInd, colInd;
        char rowChar, colChar;
        collectLocation(stream, rowInd, colInd);
//      cout << "collected" << endl; //Debugging strings
//      cout << rowInd << " " << colInd << endl; //Debugging strings
        shootAtMe(cout, stream, rowInd, colInd, playergrid);
        printPlayerGrid_after(shots_on, playergrid, 11);
//      cout << "shots" << endl; //Debugging strings
    }
}

