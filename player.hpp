#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

namespace ariel
{
    // Represents a player in the game
    class Player
    {
    private:
        string name;                   // Player's name
        int vectoryPoints;             // Player's victory points
        int numOfSettlements;          // Number of settlements the player has
        int numOfCities;               // Number of cities the player has
        int TotalResources;            // Total resources the player has
        map<string, int> resources;    // Resources the player owns
        map<string, int> devCards;     // Development cards the player owns

    public:
        // Constructor
        Player(const string &name);

        // Add resources to the player
        void addResource(const string &resource, int amount);

        // Trade resources with another player
        void trade(Player &other, const string &giveResource, const string &receiveResource, int giveAmount, int receiveAmount);

        // Decrease resources of a certain type
        void decreaseTheResources(const string &type);

        // Decrease resources of a certain type by a specific amount
        void decreaseTheResources(const string &type, int amount);

        // Handle the event when a 7 is rolled
        void RolledAtSeven();

        // Print the resources the player owns
        void printResources();

        // Increase the number of settlements
        void increaseNumOfSettlements();

        // Increase the number of cities
        void increaseNumOfCities();

        // Add a development card to the player
        void addDevelopmentCard(string card);

        // Add a number of knights to the player's development cards
        void addKnights(int amount);

        // Get the player's victory points
        int getPoints();

        // Get the total number of settlements and cities the player has
        int getNumOfSettlementsAndCities();

        // Get the amount of knights the player has
        int getAmountOfKnights();

        // Get the amount of a specific resource the player has
        int getAmountOfResources(string type);

        // Get the amount of victory points the player has from development cards
        int getAmountOfVictoryPoint();

        // Get the total number of development cards the player has
        int getAmountOfDevCards();

        // Check if the player has enough resources of a specific type
        bool haveEnoughResources(const string &type);

        // Check if the player has a specific amount of a resource
        bool haveResources(string type, int amount);

        // Check if the player has all knights needed for the largest army
        bool haveAllKnights();

        // Get the development cards the player owns
        map<string, int> getDevelopmentCards();

        // Get the player's name
        const string &getName() const;
    };
}

#endif // PLAYER_HPP
