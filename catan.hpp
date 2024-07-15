#ifndef CATAN_HPP
#define CATAN_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <ctime> 

#include "player.hpp"
#include "board.hpp"

using namespace std;

namespace ariel
{
    // Represents the Catan game
    class Catan
    {
    private:
        Board board;                       // The game board
        int vectoryPointLeft;              // Victory points left to distribute
        int knightsLeft;                   // Knights left to distribute
        vector<Player> players;            // Players in the game
        size_t currentPlayerIndex;         // Index of the current player

    public:
        // Constructor
        Catan(Player &p1, Player &p2, Player &p3);

        // Get a reference to the game board
        Board &getBoard();

        // Find a player by name
        Player *findPlayer(const string &name);

        // Get the current player
        Player &getCurrentPlayer();

        // Choose the starting player randomly
        void ChooseStartingPlayer();

        // Move to the next player
        void nextPlayer();

        // Move to the previous player
        void previousPlayer();

        // Print the winner of the game
        void printWinner();

        // Roll the dice and distribute resources
        void rollDice(Board &board);

        // End the current player's turn
        void endTurn();

        // Place a settlement on the board
        void placeSettlement(Player &player, Board &board);

        // Upgrade a settlement to a city
        void upgradeSettlement(Player &player, Board &board);

        // Place a road on the board
        void placeRoad(Player &player, Board &board);

        // Play a development card
        void playDevelopmentCard(Player &player);

        // Buy a development card
        void buyDevelopmentCard(Player &player);

        // Play the "Year of Plenty" development card
        void playYearOfPlenty(Player &player);

        // Play the "Monopoly" development card
        void playMonopoly(Player &player);

        // Play the "Road Building" development card
        void playRoadBuilding(Player &player);

        // Check if the game has ended
        bool isGameEnded();

        // Trade resources with another player
        bool trade(Player &player);

        // Sell a knight card to another player
        bool sellKnight(Player &player, Player &otherPlayer);

        // Buy a knight card from another player
        bool buyKnight(Player &player, Player &otherPlayer);
    };
}

#endif // CATAN_HPP
