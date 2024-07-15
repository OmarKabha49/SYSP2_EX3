#include "player.hpp"
#include <iostream>
#include <vector>
#include <map>

using namespace std;

namespace ariel {
    // Constructor initializing player's name and default values for resources, development cards, and points
    Player::Player(const string &name) : name(name) {
        resources = {
            {"wool", 0},
            {"brick", 0},
            {"grain", 0},
            {"lumber", 0},
            {"ore", 0}
        };

        devCards = {
            {"knight", 0},
            {"victory point", 0},
            {"year of plenty", 0},
            {"monopoly", 0},
            {"road building", 0}
        };

        vectoryPoints = 0;
        TotalResources = 0;
        numOfSettlements = 0;
        numOfCities = 0;
    }

    // Get the player's name
    const string &Player::getName() const {
        return name;
    }

    // Add resources to the player
    void Player::addResource(const string &resource, int amount) {
        resources[resource] += amount;
        TotalResources += amount;
    }

    // Trade resources with another player
    void Player::trade(Player &other, const string &giveResource, const string &receiveResource, int giveAmount, int receiveAmount) {
        if (giveResource == receiveResource) {
            cout << "Error, same type of resource." << endl;
            return;
        }
        if (giveAmount > resources[giveResource] || receiveAmount > other.resources[receiveResource]) {
            cout << "Error, you don't have enough resources." << endl;
            return;
        }

        if (giveAmount <= 0 || receiveAmount <= 0) {
            cout << "Error, illegal number." << endl;
            return;
        }

        if (resources[giveResource] >= giveAmount && other.resources[receiveResource] >= receiveAmount) {
            resources[giveResource] -= giveAmount;
            other.resources[giveResource] += giveAmount;
            resources[receiveResource] += receiveAmount;
            other.resources[receiveResource] -= receiveAmount;

            TotalResources -= giveAmount;
            other.TotalResources += giveAmount;
            other.TotalResources -= receiveAmount;
            TotalResources += receiveAmount;
            cout << "Trade completed successfully." << endl;
            cout << "Your updated resources: " << endl;
            printResources();
        } else {
            cout << "The trade operation is canceled, because there is not enough resources." << endl;
        }
    }

    // Get the player's total points (including settlements, cities, and victory points)
    int Player::getPoints() {
        int sumOfPoints = 0;
        sumOfPoints += numOfSettlements; // 1 point per settlement
        sumOfPoints += numOfCities * 2;  // 2 points per city
        sumOfPoints += devCards["victory point"]; // Victory points from cards
        return sumOfPoints;
    }

    // Check if the player has enough resources for a specific item (settlement, city, road, etc.)
    bool Player::haveEnoughResources(const string &type) {
        if (type == "settlement") {
            return resources["wool"] >= 1 && resources["brick"] >= 1 && resources["grain"] >= 1 && resources["lumber"] >= 1;
        } else if (type == "city") {
            return resources["ore"] >= 3 && resources["grain"] >= 2;
        } else if (type == "road") {
            return resources["lumber"] >= 1 && resources["brick"] >= 1;
        } else if (type == "development card") {
            return resources["ore"] >= 1 && resources["grain"] >= 1 && resources["wool"] >= 1;
        } else if (type == "knight") {
            return devCards["knight"] >= 1;
        } else if (type == "year of plenty") {
            return devCards["year of plenty"] >= 1;
        } else if (type == "monopoly") {
            return devCards["monopoly"] >= 1;
        } else if (type == "road building") {
            return devCards["road building"] >= 1;
        }
        return false;
    }

    // Decrease resources of a certain type when purchasing an item
    void Player::decreaseTheResources(const string &type) {
        if (type == "settlement") {
            resources["wool"]--;
            resources["brick"]--;
            resources["grain"]--;
            resources["lumber"]--;
            TotalResources -= 4;
            cout << "Done deal, settlement purchased." << endl;
        } else if (type == "city") {
            resources["ore"] -= 3;
            resources["grain"] -= 2;
            TotalResources -= 5;
            cout << "Done deal, city purchased." << endl;
        } else if (type == "road") {
            resources["lumber"]--;
            resources["brick"]--;
            TotalResources -= 2;
            cout << "Done deal, road purchased." << endl;
        } else if (type == "development card") {
            resources["ore"]--;
            resources["grain"]--;
            resources["wool"]--;
            TotalResources -= 3;
            cout << "Done deal, Development card purchased." << endl;
        } else if (type == "knight") {
            devCards["knight"]--;
            cout << "Knight card purchased." << endl;
        } else if (type == "year of plenty") {
            devCards["year of plenty"]--;
            cout << "Done deal, year of plenty card purchased." << endl;
        } else if (type == "monopoly") {
            devCards["monopoly"]--;
            cout << "Done deal, monopoly card purchased." << endl;
        } else if (type == "road building") {
            devCards["road building"]--;
            cout << "Done deal, road building card purchased." << endl;
        } else {
            cout << "Unknown type." << endl;
        }
    }

    // Decrease resources of a certain type by a specific amount
    void Player::decreaseTheResources(const string &type, int amount) {
        if (amount > 0) {
            if (type == "wool") {
                resources["wool"] -= amount;
                TotalResources -= amount;
            } else if (type == "brick") {
                resources["brick"] -= amount;
                TotalResources -= amount;
            } else if (type == "grain") {
                resources["grain"] -= amount;
                TotalResources -= amount;
            } else if (type == "lumber") {
                resources["lumber"] -= amount;
                TotalResources -= amount;
            } else if (type == "ore") {
                resources["ore"] -= amount;
                TotalResources -= amount;
            }
        }
    }

    // Handle the event when a 7 is rolled (player loses half of their resources if they have more than 7)
    void Player::RolledAtSeven() {
        if (TotalResources > 7) {
            int half = TotalResources / 2;

            for (int i = 0; i < half; i++) {
                vector<string> availableResources;

                for (const auto &entry : resources) {
                    if (entry.second > 0) {
                        availableResources.push_back(entry.first);
                    }
                }

                if (!availableResources.empty()) {
                    size_t index = static_cast<size_t>(rand()) % availableResources.size();
                    string resource = availableResources[index];

                    resources[resource]--;
                    TotalResources--;
                }
            }
        }
    }

    // Print the resources the player owns
    void Player::printResources() {
        for (const auto &entry : resources) {
            cout << entry.first << ": " << entry.second << endl;
        }
    }

    // Get the total number of settlements and cities the player has
    int Player::getNumOfSettlementsAndCities() {
        return numOfSettlements + numOfCities;
    }

    // Increase the number of settlements
    void Player::increaseNumOfSettlements() {
        numOfSettlements++;
    }

    // Increase the number of cities (and decrease the number of settlements)
    void Player::increaseNumOfCities() {
        numOfCities++;
        numOfSettlements--;
    }

    // Add a development card to the player
    void Player::addDevelopmentCard(string card) {
        devCards[card]++;
    }

    // Get the amount of knights the player has
    int Player::getAmountOfKnights() {
        return devCards["knight"];
    }

    // Check if the player has a specific amount of a resource
    bool Player::haveResources(string type, int amount) {
        return resources[type] >= amount;
    }

    // Add a number of knights to the player's development cards
    void Player::addKnights(int amount) {
        devCards["knight"] += amount;
    }

    // Get the amount of a specific resource the player has
    int Player::getAmountOfResources(string type) {
        return resources[type];
    }

    // Check if the player has all knights needed for the largest army
    bool Player::haveAllKnights() {
        return devCards["knight"] >= 3;
    }

    // Get the amount of victory points the player has from development cards
    int Player::getAmountOfVictoryPoint() {
        return devCards["victory point"];
    }

    // Get the total number of development cards the player has
    int Player::getAmountOfDevCards() {
        int sum = 0;
        for (auto &card : devCards) {
            sum += card.second;
        }
        return sum;
    }

    // Get the development cards the player owns
    map<string, int> Player::getDevelopmentCards() {
        return devCards;
    }
}
