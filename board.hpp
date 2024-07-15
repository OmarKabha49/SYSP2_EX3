#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <map>
#include <stdexcept>

#include "player.hpp"
#include "land.hpp"
#include "edge.hpp"
#include "vertex.hpp"

using namespace std;

namespace ariel
{
    // Represents the game board
    class Board {
    private:
        vector<vector<Land>> lands; // 2D grid of Land objects
        vector<Vertex> vertices;    // List of Vertex objects
        vector<Edge> edges;         // List of Edge objects

        // Initialize the edges
        void initEdges();

        // Initialize the vertices
        void initVertices();

    public:
        // Constructor
        Board();

        // Print the current state of the board
        void printBoard();

        // Shuffle the resource tiles
        void shuffleResources(vector<string> &resources);

        // Initialize the board
        void init();

        // Place a settlement at a specific vertex
        void placeSettlementAtVertex(Vertex &v, Player &p);

        // Place a road at a specific edge
        void placeRoadAtEdge(Edge &edge, Player &player);

        // Distribute resources to a player based on a dice roll result
        void giveResources(Player &player, int result);

        // Initialize the lands on the map
        void initTheLandsOnTheMap();

        // Place a settlement at a specific vertex (public method)
        bool placeSettlement(int vertexId, Player &p, bool firstTurn);

        // Place a road at a specific edge (public method)
        bool placeRoad(int edgeId, Player &p);

        // Check if a vertex is available for building
        bool isVertexAvilable(const Vertex &v) const;

        // Check if an edge is available for building
        bool isEdgeAvilable(const Edge &e) const;

        // Check if a vertex is connected to any of the player's roads
        bool isConnectedToPlayerRoad(const Vertex &v, Player &p) const;

        // Check if an edge is connected to any of the player's roads
        bool isConnectedToPlayerRoad(const Edge &edge, Player &player) const;

        // Check if an edge is connected to any of the player's settlements
        bool isConnectedToPlayerSettlement(const Edge &edge, Player &player) const;

        // Check if a vertex has a neighboring settlement
        bool hasNeighboureSettlement(const Vertex &v) const;

        // Upgrade a settlement to a city
        bool upgradeSettlement(int vertexId, Player &player);

        // Validate if a settlement can be placed at a specific vertex
        bool isValidSettlementAtVertex(int vertexId);

        // Validate if a road can be placed at a specific edge
        bool isValidRoadAtEdge(int edgeId);

        // Get a reference to a Land object
        Land &getLand(int i);

        // Get a reference to a Vertex object
        Vertex &getVertex(int i);

        // Get a reference to an Edge object
        Edge &getEdge(int i);

        // Initialize the resource types on the board
        vector<string> initResources();

        // Get the size of the lands vector
        int getLandsSize() const;

        // Get the size of the vertices vector
        int getVerticesSize() const;

        // Get the size of the edges vector
        int getEdgesSize() const;
    };
}

#endif // BOARD_HPP
