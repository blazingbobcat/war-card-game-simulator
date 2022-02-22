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
|    includes.h                                                            |
|    The include file with all pertinent data structures:                  |
|    struct card;                                                          |
|    class player;                                                         |
|    class game;                                                           |
|                                                                          |
#==========================================================================#

*/

#pragma once
#include <ctime>
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <queue>

using namespace std;

struct Card {

    int suit;
    int value;

};

class Player {

    private:
        queue<Card> deck;
        int deckCount;
        long wins;
        int number;

    public:
        Player() {

            resetCards();
            deckCount = 0;
            wins = 0;
            number = 0;

        }

        ~Player() {


        }

        void setNumber( int num ) {

            number = num;

        }

        int getNubmer() const {

            return number;

        }

        Card playCard() {

            Card play;

            play.value = 0;
            play.suit = 0;

            if ( !deck.empty() ) {
                
                play.value = deck.front().value;
                play.suit = deck.front().suit;
                deckCount--; // decrease deckCount
                deck.pop(); // pop front

            } // end if

            return play;

        }

        void addWin() {

            wins++;

        }

        long getWins() const {

            return wins;

        }

        void resetCards() {

            while ( !deck.empty() ) {

                    deck.pop(); // remove all cards

            } // end while

            deckCount = 0;

        }

        void addCard( Card card ) {

            deck.push( card );            
            deckCount++;

        }

        int getDeckCount() const {

            return deckCount;

        }

};

class Game {

    private:
        queue<Card> pile;
        queue<Card> deck;
        Player players[2];
        long numGames;
        long totalNumGames;
        long gameCount;
        float timePlayed;
        bool availableCards[4][13];
        float timePlayedAvg;
        int cardCount;
        int pileCount;
        long drawGames;
        int i;
        int trap;
        float totalTimePlayed;

    public:
        Game() {

            numGames = 0;
            gameCount = 0;
            players[1].setNumber(1);
            for ( int i = 0; i < 4; i++ )
                    for ( int j = 0; j < 13; j++ )
                            availableCards[i][j] = true;
            timePlayedAvg = 0.0f;
            timePlayed = 0.0f;
            cardCount = 0;
            pileCount = 0;
            totalNumGames = 0;
            drawGames = 0;
            i = 0;
            trap = 0;
            totalTimePlayed = 0;

        }

        ~Game() {

            cout << "Game reset." << endl;

        }

        long getNumGames() const {

            return numGames;

        }

        long getGameCount() const {

            return gameCount;

        }

        void setNumGames( long num ) {

            numGames = num;

        }

        void setTotalNumGames( long num ) {

            totalNumGames += num;

        }

        long getTotalNumGames() const {

            return totalNumGames;

        }

        void resetGameCount() {

            gameCount = 0;
            
        }

        long getDrawCount() {

            return drawGames;

        }

        void shuffleDeck() {

            Card newCard;

            // set the seed
            srand( (unsigned)time( NULL ) );

            for ( int i = 0; i < 4; i++ )
                    for ( int j = 0; j < 13; j++ )
                            availableCards[i][j] = true;
            

            players[0].resetCards();
            players[1].resetCards();

            // Loop through all 52 cards
            do {

                    // Random number and suit
                    newCard.value = rand() % 13;
                    newCard.suit = rand() % 4;

                    // Check number and suit
                    if ( availableCards[newCard.suit][newCard.value] == true ) {

                        availableCards[newCard.suit][newCard.value] = false;
                        deck.push( newCard );
                        cardCount++;
                        
                    } // end while

            } while ( cardCount < 52 );

            // Give cards to Player objects. deckCount = 26 for both players
            do {

                    players[0].addCard( deck.front() ); 
                    deck.pop();             

                    players[1].addCard( deck.front() );
                    deck.pop();
                    
                    cardCount -= 2;

            } while ( cardCount > 0 );

        }

        void playGame() {

            Card playerOneCard;
            Card playerTwoCard; 
            Card p1Front; // Front Card object value Player 1
            Card p2Front;

            playerOneCard = players[0].playCard();
            playerTwoCard = players[1].playCard();

            // Put cards in pile
            pile.push( playerOneCard );
            pile.push( playerTwoCard );

            pileCount += 2; // Increase count of cards in pile

            if ( playerOneCard.value == playerTwoCard.value ) {

                // Cards have same value
                playerOneCard = players[0].playCard();
                playerTwoCard = players[1].playCard();
                pile.push( playerOneCard );
                pile.push( playerTwoCard );

                pileCount += 2;
                    
            } else if ( playerOneCard.value > playerTwoCard.value ) {

                for ( i = 0; i < pileCount; i++ ) {

                    // Add cards to winning player's deck
                    players[0].addCard( pile.front() );
                    pile.pop();

                } // end for

                pileCount = 0;  // Reset Pile object

            } else if ( playerOneCard.value < playerTwoCard.value ) {
                
                for ( i = 0; i < pileCount; i++ ) {

                    // Add cards to winning player's deck
                    players[1].addCard( pile.front() );
                    pile.pop();

                } // end for

                pileCount = 0;  // Reset Pile object

            } // end if 1

            timePlayed += static_cast< float >( clock() )
                / static_cast< float >( CLOCKS_PER_SEC ); // Always increase time

            // Look if both players end up with 26 cards in their decks
            if ( players[0].getDeckCount() == 26 )
                trap++; // The game is trapped!

            // Check if player won game
            if ( players[0].getDeckCount() == 52 ) {

                players[0].addWin();
                totalTimePlayed += timePlayed; // Add on time played
                resetGame();

            } else if ( players[1].getDeckCount() == 52 ) {

                players[1].addWin();
                totalTimePlayed += timePlayed;
                resetGame();

            } else if ( pileCount == 52 || trap == 5 ) {

                drawGames++; // Game impossible to win
                setNumGames(numGames--); // Game doesn't count
                resetGame();

            } // end if

        }

        void resetGame() {
        
            shuffleDeck();

            trap = 0; // Reset trap counter
            timePlayed = 0; // Reset time played

            gameCount++;

        }

        float calculateAvg() {

            timePlayedAvg = totalTimePlayed / getTotalNumGames();
            return timePlayedAvg;

        }

        void outputResults() {

            // Total up number of games
            setTotalNumGames( getNumGames() );

            // Output results
            cout << "\nSimulation finished!  Results:" << endl
                << "Total time played: " << totalTimePlayed << " sec." << endl
                << "Average time played: " << calculateAvg() << " sec."
                << endl << "Games played: " << getTotalNumGames() << "."
                << endl << "Player One wins: " << players[0].getWins()
                << "." << endl << "Player Two wins: " << players[1].getWins()
                << "." << endl << "Impossible to win: " << getDrawCount()
                << "." << endl;

        }

};
