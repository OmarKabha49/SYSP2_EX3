#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "player.hpp"

using namespace ariel;

TEST_CASE("Player - getName") {
    Player player("Alice");
    CHECK(player.getName() == "Alice");
}

TEST_CASE("Player - addResource") {
    Player player("Alice");
    player.addResource("wool", 2);
    CHECK(player.getAmountOfResources("wool") == 2);
}

TEST_CASE("Player - trade") {
    Player player1("Alice");
    Player player2("Bob");

    player1.addResource("wool", 3);
    player2.addResource("brick", 3);

    player1.trade(player2, "wool", "brick", 2, 2);

    CHECK(player1.getAmountOfResources("wool") == 1);
    CHECK(player1.getAmountOfResources("brick") == 2);
    CHECK(player2.getAmountOfResources("wool") == 2);
    CHECK(player2.getAmountOfResources("brick") == 1);
}

TEST_CASE("Player - getPoints") {
    Player player("Alice");
    player.increaseNumOfSettlements(); // Adds 1 point
    player.increaseNumOfSettlements(); // Adds 1 point
    player.addDevelopmentCard("victory point"); // Adds 1 point
    player.addDevelopmentCard("victory point"); // Adds 1 point
    player.addDevelopmentCard("victory point"); // Adds 1 point
    player.increaseNumOfCities(); // Adds 2 points, removes 1 settlement  
    CHECK(player.getPoints() == 6); 
}

TEST_CASE("Player - hasEnoughResources") {
    Player player("Alice");
    player.addResource("wool", 1);
    player.addResource("brick", 1);
    player.addResource("grain", 1);
    player.addResource("lumber", 1);

    CHECK(player.haveEnoughResources("settlement"));
    player.decreaseTheResources("settlement");

    player.addResource("ore", 3);
    player.addResource("grain", 2);

    CHECK(player.haveEnoughResources("city"));
    player.decreaseTheResources("city");

    player.addResource("lumber", 1);
    player.addResource("brick", 1);

    CHECK(player.haveEnoughResources("road"));
}

TEST_CASE("Player - decreaseTheResourcesAmount") {
    Player player("Alice");
    player.addResource("wool", 2);
    player.decreaseTheResources("wool", 1);

    CHECK(player.getAmountOfResources("wool") == 1);
}

TEST_CASE("Player - itsSeven") {
    Player player("Alice");
    player.addResource("wool", 3);
    player.addResource("brick", 3);
    player.addResource("grain", 3);
    player.addResource("lumber", 3);

    player.RolledAtSeven();

    CHECK(player.getAmountOfResources("wool") + player.getAmountOfResources("brick") +
          player.getAmountOfResources("grain") + player.getAmountOfResources("lumber") <= 7);
}

TEST_CASE("Player - printResources") {
    Player player("Alice");
    player.addResource("wool", 2);

    std::stringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

    player.printResources();

    std::cout.rdbuf(oldCout);

    std::string output = buffer.str();
    CHECK(output.find("wool: 2") != std::string::npos);
}

TEST_CASE("Player - getNumOfSettlementsAndCities") {
    Player player("Alice");
    player.increaseNumOfSettlements(); // 1 settlement
    player.increaseNumOfSettlements(); // 2 settlements
    player.increaseNumOfCities(); // 1 city, 1 settlement left

    CHECK(player.getNumOfSettlementsAndCities() == 2); // 1 city + 1 settlement = 2
}

TEST_CASE("Player - increaseNumOfSettlements") {
    Player player("Alice");
    player.increaseNumOfSettlements();
    CHECK(player.getNumOfSettlementsAndCities() == 1);
}

TEST_CASE("Player - increaseNumOfCities") {
    Player player("Alice");
    player.increaseNumOfSettlements();
    player.increaseNumOfCities();
    CHECK(player.getNumOfSettlementsAndCities() == 1);
}

TEST_CASE("Player - addDevelopmentCard") {
    Player player("Alice");
    player.addDevelopmentCard("knight");
    CHECK(player.getAmountOfKnights() == 1);
}

TEST_CASE("Player - removeDevelopmentCard") {
    Player player("Alice");
    player.addDevelopmentCard("knight");
    CHECK(player.getAmountOfKnights() == 1);

    player.decreaseTheResources("knight");
    CHECK(player.getAmountOfKnights() == 0);
}

TEST_CASE("Player - getDevelopmentCards") {
    Player player("Alice");
    player.addDevelopmentCard("knight");
    player.addDevelopmentCard("victory point");

    std::map<std::string, int> devCards = player.getDevelopmentCards();
    CHECK(devCards["knight"] == 1);
    CHECK(devCards["victory point"] == 1);
}

TEST_CASE("Player - getNumOfDevelopmentCards") {
    Player player("Alice");
    player.addDevelopmentCard("knight");
    player.addDevelopmentCard("victory point");

    CHECK(player.getAmountOfDevCards() == 2);
}

TEST_CASE("Player - getNumOfKnights") {
    Player player("Alice");
    player.addDevelopmentCard("knight");

    CHECK(player.getAmountOfKnights() == 1);
}

TEST_CASE("Player - getNumOfCities") {
    Player player("Alice");

    player.increaseNumOfSettlements();
    player.increaseNumOfCities();

    CHECK(player.getNumOfSettlementsAndCities() == 1);
}

TEST_CASE("Player - getNumOfSettlements") {
    Player player("Alice");

    player.increaseNumOfSettlements();

    CHECK(player.getNumOfSettlementsAndCities() == 1);
}

TEST_CASE("Player - getNumOfVictoryPoints") {
    Player player("Alice");
    player.addDevelopmentCard("victory point");

    CHECK(player.getAmountOfVictoryPoint() == 1);
}

TEST_CASE("Player - getNumOfResources") {
    Player player("Alice");
    player.addResource("wool", 2);
    player.addResource("brick", 3);

    CHECK(player.getAmountOfResources("wool") == 2);
    CHECK(player.getAmountOfResources("brick") == 3);
}

TEST_CASE("Player - haveResources") {
    Player player("Alice");
    player.addResource("wool", 2);

    CHECK(player.haveResources("wool", 2));
    CHECK(!player.haveResources("wool", 3));
}

TEST_CASE("Player - getResource") {
    Player player("Alice");
    player.addResource("grain", 2);

    CHECK(player.getAmountOfResources("grain") == 2);
}

TEST_CASE("Player - removeResource") {
    Player player("Alice");
    player.addResource("ore", 2);
    player.decreaseTheResources("ore", 1);

    CHECK(player.getAmountOfResources("ore") == 1);
}

TEST_CASE("Player - hasResource") {
    Player player("Alice");
    player.addResource("lumber", 2);

    CHECK(player.haveResources("lumber", 1));
    CHECK(player.haveResources("lumber", 2));
    CHECK(!player.haveResources("lumber", 3));
}

TEST_CASE("Player - getAmountOfDevCards") {
    Player player("Alice");
    player.addDevelopmentCard("knight");
    player.addDevelopmentCard("victory point");
    CHECK(player.getAmountOfDevCards() == 2);
}
