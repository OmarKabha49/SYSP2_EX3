#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "catan.hpp"
#include "player.hpp"

using namespace ariel;
using namespace std;

TEST_CASE("Catan - ChooseStartingPlayer") {
    Player p1("Alice"), p2("Bob"), p3("Charlie");
    Catan game(p1, p2, p3);
    game.ChooseStartingPlayer();

    bool ans = game.getCurrentPlayer().getName() == "Alice" ||
          game.getCurrentPlayer().getName() == "Bob" ||
          game.getCurrentPlayer().getName() == "Charlie";

    CHECK(ans);
}

TEST_CASE("Catan - nextPlayer") {
    Player p1("Alice"), p2("Bob"), p3("Charlie");
    Catan game(p1, p2, p3);
    game.nextPlayer();

    CHECK(game.getCurrentPlayer().getName() == "Bob");

    game.nextPlayer();
    CHECK(game.getCurrentPlayer().getName() == "Charlie");
}

TEST_CASE("Catan - previousPlayer") {
    Player p1("Alice"), p2("Bob"), p3("Charlie");
    Catan game(p1, p2, p3);
    game.previousPlayer();

    CHECK(game.getCurrentPlayer().getName() == "Charlie");

    game.previousPlayer();
    CHECK(game.getCurrentPlayer().getName() == "Bob");
}

TEST_CASE("Catan - getBoard") {
    Player p1("Alice"), p2("Bob"), p3("Charlie");
    Catan game(p1, p2, p3);
    Board &board = game.getBoard();

    CHECK(board.getLandsSize() > 0);
}

TEST_CASE("Catan - printWinner") {
    Player p1("Alice"), p2("Bob"), p3("Charlie");
    Catan game(p1, p2, p3);
    

    stringstream buffer;
    streambuf *oldCout = cout.rdbuf(buffer.rdbuf());

    game.printWinner();

    cout.rdbuf(oldCout);

    std::string output = buffer.str();
    CHECK(output.find("The game not finished, no winner yet") != string::npos);
}

TEST_CASE("Catan - rollDice") {
    Player p1("Alice"), p2("Bob"), p3("Charlie");
    Catan game(p1, p2, p3);
    Board &board = game.getBoard();

    game.rollDice(board);
}

TEST_CASE("Catan - endTurn") {
    Player p1("Alice"), p2("Bob"), p3("Charlie");
    Catan game(p1, p2, p3);
    game.endTurn();

    CHECK(game.getCurrentPlayer().getName() == "Bob");
}

TEST_CASE("Catan - getCurrentPlayer") {
    Player p1("Alice"), p2("Bob"), p3("Charlie");
    Catan game(p1, p2, p3);

    CHECK(game.getCurrentPlayer().getName() == "Alice");
}

TEST_CASE("Catan - isGameEnded") {
    Player p1("Alice"), p2("Bob"), p3("Charlie");


    for (int i = 0; i < 10; ++i) {
        p1.increaseNumOfSettlements();
    }
    Catan game(p1, p2, p3);
    CHECK(game.isGameEnded());
}

TEST_CASE("Catan - findPlayerByName") {
    Player p1("Alice"), p2("Bob"), p3("Charlie");
    Catan game(p1, p2, p3);

    CHECK(game.findPlayer("Alice")->getName() == "Alice");
    CHECK(game.findPlayer("Bob")->getName() == "Bob");
    CHECK(game.findPlayer("Charlie")->getName() == "Charlie");
    CHECK(game.findPlayer("Dave") == nullptr);
}

TEST_CASE("Catan - placeSettlement") {
    Player p1("Alice"), p2("Bob"), p3("Charlie");
    Catan game(p1, p2, p3);
    Board &board = game.getBoard();

    game.placeSettlement(p1, board);
}

TEST_CASE("Catan - upgradeSettlement") {
    Player p1("Alice"), p2("Bob"), p3("Charlie");
    Catan game(p1, p2, p3);
    Board &board = game.getBoard();

    game.placeSettlement(p1, board);
    game.upgradeSettlement(p1, board);
}

TEST_CASE("Catan - placeRoad") {
    Player p1("Alice"), p2("Bob"), p3("Charlie");
    Catan game(p1, p2, p3);
    Board &board = game.getBoard();

    game.placeRoad(p1, board);
}

TEST_CASE("Catan - playDevelopmentCard") {
    Player p1("Alice"), p2("Bob"), p3("Charlie");
    Catan game(p1, p2, p3);

    p1.addDevelopmentCard("year of plenty");

    game.playDevelopmentCard(p1);
}

TEST_CASE("Catan - trade") {
    Player p1("Alice"), p2("Bob"), p3("Charlie");
    Catan game(p1, p2, p3);

    game.trade(p1);
}

TEST_CASE("Catan - buyDevelopmentCard") {
    Player p1("Alice"), p2("Bob"), p3("Charlie");
    Catan game(p1, p2, p3);

    p1.addResource("grain", 1);
    p1.addResource("wool", 1);
    p1.addResource("ore", 1);

    game.buyDevelopmentCard(p1);
}
