#include <fstream>
#include <ios>
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
        stream << "hello kitty" << endl;
}

void playBattleship_winner(vector<vector<char>> &shots_on, iostream &stream, int &count);

int main()
{
        string theirs, ours;

  try
  {
    boost::asio::io_context io_context;

    tcp::endpoint endpoint(tcp::v4(), 3737);
    tcp::acceptor acceptor(io_context, endpoint);

    for (;;)
    {
      tcp::iostream client;
      boost::system::error_code ec;
          cout << "Waiting....." << endl;
      acceptor.accept(client.socket(), ec);
          cout << "Connected!" << endl;
      if (!ec)
      {
//----------------------------------------------------------------------//
//LET THE GAMES BEGIN
    srand(time(NULL));

    ifstream bank;
    string line, tempQ, tempA, tempB, tempC, tempD;
    vector<question> quiz_base;
    char add;
    string temp;

        system("figlet Volleypardy | lolcat");

//JEOPARDY DATABASE INITIAL SETUP
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

//DO YOU WANT TO PLAY VOLLEYSHIPARDY
        bool waiting = true;

        printRules(cout, client);

        gameStart(cout, client);
        client >> clientchoice;

//      cout << choice << endl;
        if (clientchoice == 'n' or clientchoice == 'N'){
                setcolor(47, 157, 143);
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
                resetcolor();
                setcolor(214, 40, 40);
                cout << "        Sorry, your friend doesn't want to play with you.      \n\n";
        resetcolor();
                setcolor(47, 157, 143);
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
                resetcolor();
                exit(1);
        }
        else if (clientchoice == 'y' or clientchoice == 'Y'){

//BEGIN PLAYER SHIP PLACEMENT
//YOUR TURN TO PLACE SHIPS
                clearscreen();
                system("figlet Battleship | lolcat");

                while (has_ships) {
            placeShips(player1, player1_ships, SIZE);
            printPlayerGrid(world_map, player1, SIZE);

            for (int i = 0; i < TOTAL_SHIPS; i++){
                if (player1_ships.at(i) == true) {
                    has_ships = true;
                    break;
                }
                else {
                    has_ships = false;
                }
            }
        }
        setcolor(47, 157, 143);
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"  << endl;
        resetcolor();
                cout << "                 Your ships have been placed                   " << endl;
                setcolor(47, 157, 143);
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"  << endl << endl;
            resetcolor();

                client << MAGENTA << "Player 1 " << RESET << "has placed their ships.\n";

                setcolor(47, 157, 143);
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
                resetcolor();

                has_ships = true;
                clearscreen();

//WAIT FOR PLAYER 2 TO PLACE SHIPS
                cout << "                       Please Wait..                            "  << endl;
                setcolor(69, 123, 157);
                cout <<  "               Player 2";
                resetcolor();
                cout << " is placing their ships.                 " << endl << endl;
                setcolor(47, 157, 143);
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
                resetcolor();

        //PLAYER 2 IS FINISHED
                getline(client, theirs);
                setcolor(69, 123, 157);
                cout << "               Player 2";
                resetcolor();
                cout << theirs << endl << endl;
                setcolor(47, 157, 143);
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        resetcolor();
//END PLACING SHIPS

/*
        //TEST FIRING AT OPPONENT. WORKS AS EXPECTED.
                playBattleship_winner(shots_on_2, client, counter);
                playBattleship_winner(shots_on_2, client, counter);
                playBattleship_winner(shots_on_2, client, counter);
                playBattleship_winner(shots_on_2, client, counter);
                playBattleship_winner(shots_on_2, client, counter);
                playBattleship_winner(shots_on_2, client, counter);
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
                jeopStart(cout, client);
                client >> clientchoice;
                if (clientchoice == 'n' or clientchoice == 'N'){
                        setcolor(47, 157, 143);
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
                        resetcolor();
                        setcolor(214, 40, 40);
                        cout << "        Sorry, your friend doesn't want to play with you.      \n\n";
                        resetcolor();
                        setcolor(47, 157, 143);
                        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
                        resetcolor();
                        exit(1);
        }

        string outcome;
        //EVERYTHING UP UNTIL WORKS SYMMETRICALLY
                while(streak){
                        get_jeopQuest(outcome, streak, record);
                        client << outcome << endl;
                        client << record;
                }


/*
                setcolor(47, 157, 143);
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        resetcolor();
        cout << "                Back to the Volleypardy round! "<<  endl << endl;
        setcolor(47, 157, 143);
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
                resetcolor();
*/


//----------------------------------------------------------------------//

//This will allow users to chat back and forth
                  /*
                  while(true) {
                          cout << CYAN << "Meagan: " << RESET;
                          getline(cin, ours);
                          client << ours << endl;
                          getline(client, theirs);
                          if (!client) break;
                          cout << MAGENTA << "Ray: " << RESET << theirs << endl;
                          usleep(333333);
                  }
                  */

//Constantly passes messages back and forth until someone quits
                  /*
                  while(true){
                        test_function(client);
                        string message;
                        getline(client, message);
                        if (!client) break;
                        cout << message << endl;
                        usleep(333333);
                  }
                  */
      }
    }
  }
  }
  catch (exception& e)
  {
    cerr << e.what() << endl;
  }
}

void playBattleship_winner(vector<vector<char>> &shots_on, iostream &stream, int &count){
        for (int i = 0; i < 3; i++){
        printShootingGrid(shots_on);
        char rowChar, colChar;
        cout << "      Enter a location to fire at in the format 'A 4': ";
        cin >> rowChar >> colChar;
        cout << endl;
        rowChar = toupper(rowChar);
        int rowInt, colInt;
        rowInt = rowChar - 64;
        colInt = colChar - 47;


        sendLocation(stream, rowInt, colInt);

        setcolor(47, 157, 143);
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        resetcolor();
        cout << "                      You fired at (" << rowChar << ", " << colChar << ")" <<  endl << endl;
        setcolor(47, 157, 143);
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        resetcolor();

        shooter(cout, stream, rowInt, colInt, shots_on, count);
        cout << endl;
//      cout << "shots" << endl;
//      cout << "print" << endl;
        }
}

