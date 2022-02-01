/*

#==========================================================================#
|                                                                          |
|    WAR CARD GAME SIMULATOR                                               |
|                                                                          |
|    BY JOSH KLIPSTEIN                                                     |
|    PROJECT START DATE:  12/27/2021                                       |
|                                                                          |
|    STATISTICAL SIMULATION OF WAR CARD GAME                               |
|    INPUT:  NUMBER OF GAMES                                               |
|    OUTPUT: AVERAGE TIME OF GAMES                                         |
|                                                                          |
|    This program takes an input for number of games of war.  Here are the |
|    rules:  Two players split a 52-deck of cards in half and have their   |
|    own cards face down in their hands.  Cards are drawn and placed face  |
|    up on the table.  The values of the cards are compared, and the player|
|    that presented the card of higher value wins both cards.  If the      |
|    values are the same, the process repeats until a player presents a    |
|    card with higher value.  Play continues until a player wins all the   |
|    cards.  This program plays however many games a user enters and       |
|    records the time taken for each game.  It then takes the average of   |
|    all the times and presents it to the user in the results.             |
|                                                                          |
|    Everything written in C++, with the following include files:          |
|    iostream.h                                                            |
|    cmath.h                                                               |
|    cstdlib.h                                                             |
|    includes.h                                                            |
|    ctime.h                                                               |
|    queue.h                                                               |
|                                                                          |
#==========================================================================#

*/
#include <iostream>
#include "includes.h"

using namespace std;

int main() {

    long prompt;
    Game game;

    // Introduce users to program
    cout << "WAR CARD GAME SIMULATOR\n" << endl;
    cout << "This program takes an input for number of games of War.  Here are the" << endl;
    cout << "rules:  Two players split a 52-deck of cards in half and have their" << endl;
    cout << "own cards face down in their hands.  Cards are drawn and placed face" << endl;
    cout << "up on the table.  The values of the cards are compared, and the player" << endl;
    cout << "that presented the card of higher value wins both cards.  If the" << endl;
    cout << "values are the same, the process repeats until a player presents a" << endl;
    cout << "card with higher value.  Play continues until a player wins all the" << endl;
    cout << "cards.  This program plays however many games a user enters and" << endl;
    cout << "records the time taken for each game.  It then takes the average of" << endl;
    cout << "all the times and presents it to the user in the results." << endl;
    cout << "DEPENDING ON YOUR MACHINE, THIS PROGRAM MAY TAKE A WHILE TO PRODUCE RESULTS!" << endl;

    // Prompt user to run simulation
    do {

        cout << "\nEnter number of games for simulation or 0 to quit: ";
        try {

            cin >> prompt;
            if ( cin.fail() )
                // User enters invalid input
                throw prompt;

            if ( prompt == 0 )
                cout << "\nThank you for using my program!" << endl;

            else if ( prompt > 0 ) {

                game.setNumGames( prompt );

                // Always reset game first
                game.resetGameCount();
                game.resetGame();

                // Tell user we're playing the games
                cout << "Playing " << game.getNumGames() << " game(s)..." << endl;
                
                while ( game.getGameCount() <= game.getNumGames() ) {

                    game.playGame(); // Game object runs loop

                } // end while

                game.outputResults();

            } else {

                cout << "\nPlease enter more than one game." << endl;

            }// end if

        } catch ( long ) {

            cout << "\nERROR:  Invalid input." << endl;

            cin.clear(); // Reset input stream
            cin.ignore( 100, '\n' );
            
            prompt = 1; // Reset prompt

        }; // end try-catch

    } while ( prompt != 0 );
    
    return 0;

}