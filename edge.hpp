#ifndef EDGE_HPP
#define EDGE_HPP

#include <string>
#include <vector>

using namespace std;

namespace ariel{
    // Represents an Edge in the game board
    class Edge
    {
    public:
        int id;                       
        string owner;                  // Player who owns the edge
        vector<int> neighbors_vertice; // Indices of neighboring vertices
        vector<int> neighbors_edges;   // Indices of neighboring edges

        Edge(int id) : id(id), owner("") {}
    };
}

#endif // EDGE_HPP
