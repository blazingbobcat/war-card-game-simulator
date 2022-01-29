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

            cout << "Player destroyed." << endl;

        }

        void setNumber(int num) {

            number = num;

        }

        int getNubmer() const {

            return number;

        }

        Card playCard() {

            Card play;

            play.value = 0;
            play.suit = 0;

            if ( getDeckCount() > 0 ) {
                
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

        void addCard(Card card) {

            deck.push(card);            
            deckCount++;

        }

        Card showFront() {

            return deck.front();

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

    public:
        Game() {

            numGames = 0;
            gameCount = 0;
            players[1].setNumber(1);
            for (int i = 0; i < 4; i++)
                    for (int j = 0; j < 13; j++)
                            availableCards[i][j] = true;
            timePlayedAvg = 0.0f;
            timePlayed = 0.0f;
            cardCount = 0;
            pileCount = 0;
            totalNumGames = 0;

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

        void setNumGames(long num) {

            numGames = num;

        }

        void setTotalNumGames(long num) {

            totalNumGames += num;

        }

        long getTotalNumGames() const {

            return totalNumGames;

        }

        void resetGameCount() {

            gameCount = 0;
            
        }

        void shuffleDeck() {

            Card newCard;

            // set the seed
            srand( (unsigned)time( NULL ) );

            for (int i = 0; i < 4; i++)
                    for (int j = 0; j < 13; j++)
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
                        deck.push(newCard);
                        cardCount++;

                    } // end while

            } while ( cardCount < 52 );

            // Give cards to Player objects. deckCount = 26 for both players
            do {

                    players[0].addCard(deck.front()); 
                    deck.pop();             

                    players[1].addCard(deck.front());
                    deck.pop();
                    
                    cardCount -= 2;

            } while (cardCount > 0);

        }

        void playGame() {

            Card playerOneCard;
            Card playerTwoCard; 
            Card p1Front; // Front Card object value Player 1
            Card p2Front;

            playerOneCard = players[0].playCard();
            playerTwoCard = players[1].playCard();

            // Put cards in pile
            pile.push(playerOneCard);
            pile.push(playerTwoCard);

            pileCount += 2;

            if (pile.front().value == pile.back().value) {

                    do {

                        // Cards have same value
                        playerOneCard = players[0].playCard();
                        playerTwoCard = players[1].playCard();
                        pile.push(playerOneCard);
                        pile.push(playerTwoCard);

                        // Tell Player objects to show fronts of Deck queues
                        p1Front = players[0].showFront();
                        p2Front = players[1].showFront();

                        pileCount += 2;

                    } while (p1Front.value == p2Front.value);
                    
                    if (p1Front.value > p2Front.value) {

                            // Player One wins cards
                            playerOneCard = players[0].playCard();
                            playerTwoCard = players[1].playCard();
                            pile.push(playerOneCard);
                            pile.push(playerTwoCard);

                            pileCount += 2;

                            for (int p = 0; p < pileCount; p++) {

                                    players[0].addCard(pile.front());
                                    pile.pop();
                                    // The temporary only lasts...

                            } // end for
                            
                    } else if (p1Front.value < p2Front.value) {

                            // sometimes, but not always =^>
                            playerOneCard = players[0].playCard();
                            playerTwoCard = players[1].playCard();
                            pile.push(playerOneCard);
                            pile.push(playerTwoCard);

                            pileCount += 2;

                            for (int p = 0; p < pileCount; p++) {

                                    players[1].addCard(pile.front());
                                    pile.pop();

                            } // end for

                    } // end if 2

            } else if (pile.front().value < pile.back().value) {

                    players[1].addCard(pile.front());

                    players[1].addCard(pile.back());

                    pile.pop();
                    pile.pop();
                    
            } else if (pile.front().value > pile.back().value) {

                    players[0].addCard(pile.front());
                    
                    players[0].addCard(pile.back());

                    pile.pop();
                    pile.pop();
                    
            } // end if 1

            pileCount = 0;  // Reset Pile object
            timePlayed += static_cast< float >( clock() )
            / static_cast< float >( CLOCKS_PER_SEC ); // Always increase time

            // Check if player won game
            if (players[0].getDeckCount() == 52) {

                players[0].addWin();
                resetGame();

            } else if (players[1].getDeckCount() == 52) {

                players[1].addWin();
                resetGame();

            } // end if

        }

        void resetGame() {
        
            shuffleDeck();

            gameCount++;

        }

        float calculateAvg() {

            timePlayedAvg = timePlayed / getTotalNumGames();
            return timePlayedAvg;

        }

        void outputResults() {

            // Total up number of games
            setTotalNumGames(getNumGames());

            // Output results
            cout << "\nSimulation finished!  Results:" << endl
                    << "Total time played: " << timePlayed << " sec." << endl
                    << "Average time played: " << calculateAvg() << " sec."
                    << endl << "Games played: " << getTotalNumGames() << "."
                    << endl << "Player One wins: " << players[0].getWins()
                    << "." << endl << "Player Two wins: " << players[1].getWins()
                    << "." << endl << "\n";

        }

        Player getPlayer(int number) const {

            return players[number];

        }

};
