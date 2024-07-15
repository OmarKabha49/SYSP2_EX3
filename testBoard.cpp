#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "board.hpp"
#include "player.hpp"
using namespace ariel;

TEST_CASE("shuffle Resources") {
    Board board;
    vector<string> resources = board.initResources();
    vector<string> originalResources = resources;

    board.shuffleResources(resources);

    bool isShuffled = false;
    for (size_t i = 0; i < resources.size(); ++i) {
        if (resources[i] != originalResources[i]) {
            isShuffled = true;
            break;
        }
    }
    CHECK(isShuffled);
}

TEST_CASE("PLACE SETTLEMENT") {
    Board board;
    board.init();
    Player player("Kholyo");
    bool isPlaced = board.placeSettlement(0, player, true);
    CHECK(isPlaced);

    isPlaced = board.placeSettlement(1, player, true);
    CHECK(!isPlaced);


    isPlaced = board.placeSettlement(0, player, true);
    CHECK(!isPlaced);

    isPlaced = board.placeSettlement(2, player, false);
    CHECK(!isPlaced);
}

TEST_CASE("Board - isVertexOccupied") {
    Board board;
    board.init();

    Vertex vertex = board.getVertex(0);
    bool isOccupied = board.isVertexAvilable(vertex);
    CHECK(!isOccupied);

    Player player("Bob");
    vertex.setOwner(player.getName());
    isOccupied = board.isVertexAvilable(vertex);
    CHECK(isOccupied);
}

TEST_CASE("Board - hasAdjacentSettlement") {
    Board board;
    board.init();
    Player player("Bob");
    board.placeSettlement(0, player, true);

    bool hasAdjacent = board.hasNeighboureSettlement(board.getVertex(0));
    CHECK(!hasAdjacent);

    hasAdjacent = board.hasNeighboureSettlement(board.getVertex(1));
    CHECK(hasAdjacent);
}

TEST_CASE("Board - placeSettlementAtVertex") {
    Board board;
    board.init();
    Player player("Bob");
    Vertex vertex = board.getVertex(0);
    board.placeSettlementAtVertex(vertex, player);

    CHECK(vertex.getType() == "settlement");
    CHECK(vertex.getOwner() == "Bob");
}

TEST_CASE("Board - placeRoad") {
    Board board;
    board.init();
    Player player("Bob");
    Edge edge = board.getEdge(0);
    edge.owner = "Bob";
    board.placeSettlement(0, player, true);
    bool result = board.placeRoad(edge.id, player);

    CHECK(result);
    CHECK(edge.owner == player.getName());
}

TEST_CASE("Board - isEdgeOccupied") {
    Board board;
    board.init();
    Edge edge = board.getEdge(0);
    edge.owner = "Bob";

    CHECK(board.isEdgeAvilable(edge));

    edge.owner = "";
    CHECK(!board.isEdgeAvilable(edge));
}

TEST_CASE("Board - upgradeSettlement") {
    Board board;
    board.init();
    Player player("Bob");

    board.placeSettlement(0, player, true);
    bool success = board.upgradeSettlement(0, player);
    CHECK(success);

    Player player2("Alice");
    success = board.upgradeSettlement(0, player2);
    CHECK(!success);
}

TEST_CASE("Board - getLand") {
    Board board;
    board.init();

    Land &land = board.getLand(0);
    CHECK(land.type != "");

    CHECK_THROWS_AS(board.getLand(20), std::invalid_argument);
}

TEST_CASE("Board - getVertex") {
    Board board;
    board.init();

    Vertex &vertex = board.getVertex(0);
    CHECK(vertex.id == 0);
    CHECK_THROWS_AS(board.getVertex(999), std::invalid_argument);
    
}


TEST_CASE("Board - isConnectedToPlayerSettlement") {
    Board board;
    board.init();
    Player player("Bob");

    board.placeSettlement(0, player, true);

    Edge edge = board.getEdge(0);
    bool isConnected = board.isConnectedToPlayerSettlement(edge, player);
    CHECK(isConnected);

    Edge edge2 = board.getEdge(1);
    isConnected = board.isConnectedToPlayerSettlement(edge2, player);
    CHECK(!isConnected);
}
