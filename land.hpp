#ifndef LAND_HPP
#define LAND_HPP

#include <string>
#include <vector>

using namespace std;

namespace ariel
{
    // Represents a Land in the game board
    class Land
    {
    public:
        string type;          // Resource type of the land (e.g., wood, brick)
        int number;           // Dice number associated with the land
        vector<int> vertices; // Indices of the vertices adjacent to the land
        vector<int> edges;    // Indices of the edges adjacent to the land

        // Default constructor
        Land() = default;

        // Parameterized constructor to initialize the type and number
        Land(const string &type, int number) : type(type), number(number) {}
    };
}

#endif // LAND_HPP
