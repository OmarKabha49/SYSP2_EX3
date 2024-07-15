#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <string>
#include <vector>

using namespace std;

namespace ariel
{
    // Represents a Vertex in the game board
    class Vertex
    {
    public:
        int id;                        // Unique identifier for the vertex
        string owner;                  // Player who owns the vertex
        string type;                   // Type of structure at the vertex (e.g., settlement, city)
        vector<int> neighbors_vertice; // Indices of neighboring vertices
        vector<int> neighbors_edges;   // Indices of neighboring edges

        Vertex(int id) : id(id), owner(""), type("") {}

        bool hasSettlement() const { return !owner.empty(); }
        bool isCity() const { return type == "city"; }
        bool isSettlement() const { return type == "settlement"; }
        void setOwner(const string &player) { owner = player; }
        void setType(const string &type) { this->type = type; }
        string getOwner() const { return owner; }
        string getType() const { return type; }
    };
}

#endif // VERTEX_HPP
