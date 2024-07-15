#include <random>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "board.hpp"

namespace ariel
{
    // Constructor that initializes the board
    Board::Board() { init(); }

    // Initialize the resource types on the board
    vector<string> Board::initResources() {
        vector<string> resources = {
            "Desert",
            "wool", "wool", "wool", "wool",
            "brick", "brick", "brick",
            "grain", "grain", "grain", "grain",
            "lumber", "lumber", "lumber", "lumber",
            "ore", "ore", "ore"};

        return resources;
    }

    // Shuffle the resource tiles
    void Board::shuffleResources(vector<string> &resources) {
        random_device rd;
        mt19937 g(rd());
        shuffle(resources.begin(), resources.end(), g);
    }

    // Initialize the board
    void Board::init() {
        // Land numbers and resource initialization
        vector<int> landsNum = {10, 2, 9, 12, 6, 4, 10, 9, 11, 3, 8, 8, 3, 4, 5, 5, 6, 11};
        vector<string> resources = initResources();
        shuffleResources(resources);

        // Create a 2D grid of Land objects
        lands = vector<vector<Land>>(5);
        vector<int> mapShape = {3, 4, 5, 4, 3};

        for (size_t i = 0; i < 5; ++i) {
            lands[i].resize(static_cast<size_t>(mapShape[i]));
        }

        // Fill the lands with resources and numbers
        size_t R_index = 0;
        size_t L_INDEX = 0;
        for (size_t i = 0; i < 5; ++i) {
            for (size_t j = 0; j < mapShape[i]; ++j) {
                if (resources[R_index] == "Desert") {
                    lands[i][j] = Land("Desert", 7);
                    R_index++;
                } else {
                    lands[i][j] = Land(resources[R_index++], landsNum[L_INDEX++]);
                }
            }
        }

        // Initialize vertices
        for (int i = 0; i < 54; i++) {
            vertices.push_back(Vertex(i));
        }
        initVertices();

        // Initialize edges
        for (int i = 0; i < 72; i++) {
            edges.push_back(Edge(i));
        }
        initEdges();
        initTheLandsOnTheMap();
    }

    // Helper function to initialize vertices
    void initVerticesHelper(Vertex& vertex, std::initializer_list<int> vertice_neighbors, std::initializer_list<int> edge_neighbors) {
        vertex.neighbors_vertice = vertice_neighbors;
        vertex.neighbors_edges = edge_neighbors;
    }

    // Initialize vertices with neighbors
    void Board::initVertices() {
        initVerticesHelper(vertices[0], {1, 8}, {0, 6});
        initVerticesHelper(vertices[1], {0, 2}, {0, 1});
        initVerticesHelper(vertices[2], {1, 3, 10}, {1, 2, 7});
        initVerticesHelper(vertices[3], {2, 4}, {2, 3});
        initVerticesHelper(vertices[4], {3, 5, 12}, {3, 4, 8});
        initVerticesHelper(vertices[5], {4, 6}, {4, 5});
        initVerticesHelper(vertices[6], {5, 14}, {5, 9});
        initVerticesHelper(vertices[7], {8, 17}, {10, 18});
        initVerticesHelper(vertices[8], {0, 7, 9}, {6, 10, 11});
        initVerticesHelper(vertices[9], {8, 10, 19}, {11, 12, 19});
        initVerticesHelper(vertices[10], {2, 9, 11}, {7, 12, 13});
        initVerticesHelper(vertices[11], {10, 12, 21}, {13, 14, 20});
        initVerticesHelper(vertices[12], {4, 11, 13}, {8, 14, 15});
        initVerticesHelper(vertices[13], {12, 14, 23}, {15, 16, 21});
        initVerticesHelper(vertices[14], {6, 13, 15}, {9, 16, 17});
        initVerticesHelper(vertices[15], {14, 25}, {17, 22});
        initVerticesHelper(vertices[16], {17, 27}, {23, 33});
        initVerticesHelper(vertices[17], {7, 16, 18}, {18, 23, 24});
        initVerticesHelper(vertices[18], {17, 19, 29}, {24, 25, 34});
        initVerticesHelper(vertices[19], {9, 18, 20}, {19, 25, 26});
        initVerticesHelper(vertices[20], {19, 21, 31}, {26, 27, 35});
        initVerticesHelper(vertices[21], {11, 20, 22}, {20, 27, 28});
        initVerticesHelper(vertices[22], {21, 23, 33}, {28, 29, 36});
        initVerticesHelper(vertices[23], {13, 22, 24}, {21, 29, 30});
        initVerticesHelper(vertices[24], {23, 25, 35}, {30, 31, 37});
        initVerticesHelper(vertices[25], {15, 24, 26}, {22, 31, 32});
        initVerticesHelper(vertices[26], {25, 37}, {32, 38});
        initVerticesHelper(vertices[27], {16, 28}, {33, 39});
        initVerticesHelper(vertices[28], {27, 29, 38}, {39, 40, 49});
        initVerticesHelper(vertices[29], {18, 28, 30}, {34, 40, 41});
        initVerticesHelper(vertices[30], {29, 31, 40}, {41, 42, 50});
        initVerticesHelper(vertices[31], {20, 30, 32}, {35, 42, 43});
        initVerticesHelper(vertices[32], {31, 33, 42}, {43, 44, 51});
        initVerticesHelper(vertices[33], {22, 32, 34}, {36, 44, 45});
        initVerticesHelper(vertices[34], {33, 35, 44}, {45, 46, 52});
        initVerticesHelper(vertices[35], {24, 34, 36}, {37, 46, 47});
        initVerticesHelper(vertices[36], {35, 37, 46}, {47, 48, 53});
        initVerticesHelper(vertices[37], {26, 36}, {38, 48});
        initVerticesHelper(vertices[38], {28, 39}, {49, 54});
        initVerticesHelper(vertices[39], {38, 40, 47}, {54, 55, 62});
        initVerticesHelper(vertices[40], {30, 39, 41}, {50, 55, 56});
        initVerticesHelper(vertices[41], {40, 42, 49}, {56, 57, 63});
        initVerticesHelper(vertices[42], {32, 41, 43}, {51, 57, 58});
        initVerticesHelper(vertices[43], {42, 44, 51}, {58, 59, 64});
        initVerticesHelper(vertices[44], {34, 43, 45}, {52, 59, 60});
        initVerticesHelper(vertices[45], {44, 46, 53}, {60, 61, 65});
        initVerticesHelper(vertices[46], {36, 45}, {53, 61});
        initVerticesHelper(vertices[47], {39, 48}, {62, 66});
        initVerticesHelper(vertices[48], {47, 49}, {66, 67});
        initVerticesHelper(vertices[49], {41, 48, 50}, {63, 67, 68});
        initVerticesHelper(vertices[50], {49, 51}, {68, 69});
        initVerticesHelper(vertices[51], {43, 50, 52}, {64, 69, 70});
        initVerticesHelper(vertices[52], {51, 53}, {70, 71});
        initVerticesHelper(vertices[53], {45, 52}, {65, 71});
    }

    // Helper function to initialize edges
    void initEdgesHelper(Edge& edge, std::initializer_list<int> vertice_neighbors, std::initializer_list<int> edge_neighbors) {
        edge.neighbors_vertice = vertice_neighbors;
        edge.neighbors_edges = edge_neighbors;
    }

    // Initialize edges with neighbors
    void Board::initEdges() {
        initEdgesHelper(edges[0], {0, 1}, {1, 6});
        initEdgesHelper(edges[1], {1, 2}, {0, 2, 7});
        initEdgesHelper(edges[2], {2, 3}, {1, 3, 7});
        initEdgesHelper(edges[3], {3, 4}, {2, 4, 8});
        initEdgesHelper(edges[4], {4, 5}, {3, 5, 8});
        initEdgesHelper(edges[5], {5, 6}, {4, 9});
        initEdgesHelper(edges[6], {0, 8}, {0, 10, 11});
        initEdgesHelper(edges[7], {2, 10}, {1, 2, 11, 12});
        initEdgesHelper(edges[8], {4, 12}, {3, 4, 14, 15});
        initEdgesHelper(edges[9], {6, 14}, {5, 16, 17});
        initEdgesHelper(edges[10], {7, 8}, {6, 11, 18});
        initEdgesHelper(edges[11], {8, 9}, {6, 10, 12, 19});
        initEdgesHelper(edges[12], {9, 10}, {7, 11, 13, 19});
        initEdgesHelper(edges[13], {10, 11}, {7, 12, 14, 20});
        initEdgesHelper(edges[14], {11, 12}, {8, 13, 15, 20});
        initEdgesHelper(edges[15], {12, 13}, {8, 14, 16, 21});
        initEdgesHelper(edges[16], {13, 14}, {9, 15, 17, 21});
        initEdgesHelper(edges[17], {14, 15}, {9, 16, 22});
        initEdgesHelper(edges[18], {7, 17}, {10, 23, 24});
        initEdgesHelper(edges[19], {9, 19}, {11, 12, 25, 26});
        initEdgesHelper(edges[20], {11, 21}, {13, 14, 27, 28});
        initEdgesHelper(edges[21], {13, 23}, {15, 16, 29, 30});
        initEdgesHelper(edges[22], {15, 25}, {17, 31, 32});
        initEdgesHelper(edges[23], {16, 17}, {18, 24, 33});
        initEdgesHelper(edges[24], {17, 18}, {18, 23, 25, 34});
        initEdgesHelper(edges[25], {18, 19}, {19, 24, 26, 34});
        initEdgesHelper(edges[26], {19, 20}, {19, 25, 27, 35});
        initEdgesHelper(edges[27], {20, 21}, {20, 26, 28, 35});
        initEdgesHelper(edges[28], {21, 22}, {20, 27, 29, 36});
        initEdgesHelper(edges[29], {22, 23}, {21, 28, 30, 36});
        initEdgesHelper(edges[30], {23, 24}, {21, 29, 31, 37});
        initEdgesHelper(edges[31], {24, 25}, {22, 30, 32, 37});
        initEdgesHelper(edges[32], {25, 26}, {22, 31, 38});
        initEdgesHelper(edges[33], {16, 27}, {23, 39});
        initEdgesHelper(edges[34], {18, 29}, {24, 25, 40, 41});
        initEdgesHelper(edges[35], {20, 31}, {26, 27, 42, 43});
        initEdgesHelper(edges[36], {22, 33}, {28, 29, 44, 45});
        initEdgesHelper(edges[37], {24, 35}, {30, 31, 46, 47});
        initEdgesHelper(edges[38], {26, 37}, {32, 48});
        initEdgesHelper(edges[39], {27, 28}, {33, 40, 49});
        initEdgesHelper(edges[40], {28, 29}, {34, 39, 41, 49});
        initEdgesHelper(edges[41], {29, 30}, {34, 40, 42, 50});
        initEdgesHelper(edges[42], {30, 31}, {35, 41, 43, 50});
        initEdgesHelper(edges[43], {31, 32}, {35, 42, 44, 51});
        initEdgesHelper(edges[44], {32, 33}, {36, 43, 45, 51});
        initEdgesHelper(edges[45], {33, 34}, {36, 44, 46, 52});
        initEdgesHelper(edges[46], {34, 35}, {37, 45, 47, 52});
        initEdgesHelper(edges[47], {35, 36}, {37, 46, 48, 53});
        initEdgesHelper(edges[48], {36, 37}, {38, 47, 53});
        initEdgesHelper(edges[49], {28, 38}, {39, 40, 54});
        initEdgesHelper(edges[50], {30, 40}, {41, 42, 55, 56});
        initEdgesHelper(edges[51], {32, 42}, {43, 44, 57, 58});
        initEdgesHelper(edges[52], {34, 44}, {45, 46, 59, 60});
        initEdgesHelper(edges[53], {36, 46}, {47, 48, 61});
        initEdgesHelper(edges[54], {38, 39}, {49, 55, 62});
        initEdgesHelper(edges[55], {39, 40}, {50, 54, 56, 62});
        initEdgesHelper(edges[56], {40, 41}, {50, 55, 57, 63});
        initEdgesHelper(edges[57], {41, 42}, {51, 56, 58, 63});
        initEdgesHelper(edges[58], {42, 43}, {51, 57, 59, 64});
        initEdgesHelper(edges[59], {43, 44}, {52, 58, 60, 64});
        initEdgesHelper(edges[60], {44, 45}, {52, 59, 61, 65});
        initEdgesHelper(edges[61], {45, 46}, {53, 60, 65});
        initEdgesHelper(edges[62], {39, 47}, {54, 55, 66});
        initEdgesHelper(edges[63], {41, 49}, {56, 57, 67, 68});
        initEdgesHelper(edges[64], {43, 51}, {58, 59, 69, 70});
        initEdgesHelper(edges[65], {45, 53}, {60, 61, 71});
        initEdgesHelper(edges[66], {47, 48}, {62, 67});
        initEdgesHelper(edges[67], {48, 49}, {63, 66, 68});
        initEdgesHelper(edges[68], {49, 50}, {63, 67, 69});
        initEdgesHelper(edges[69], {50, 51}, {64, 68, 70});
        initEdgesHelper(edges[70], {51, 52}, {64, 69, 71});
        initEdgesHelper(edges[71], {52, 53}, {65, 70});
    }

    // Helper function to initialize lands with neighbors
    void initLandsHelper(Land& land, std::initializer_list<int> vertice_neighbors, std::initializer_list<int> edge_neighbors) {
        land.vertices = vertice_neighbors;
        land.edges = edge_neighbors;
    }

    // Initialize lands with neighbors
    void Board::initTheLandsOnTheMap() {
        initLandsHelper(lands[0][0], {0, 1, 2, 8, 9, 10}, {0, 1, 6, 7, 11, 12});
        initLandsHelper(lands[0][1], {2, 3, 4, 10, 11, 12}, {2, 3, 7, 8, 13, 14});
        initLandsHelper(lands[0][2], {4, 5, 6, 12, 13, 14}, {4, 5, 8, 9, 15, 16});
        initLandsHelper(lands[1][0], {7, 8, 9, 17, 18, 19}, {10, 11, 18, 19, 24, 25});
        initLandsHelper(lands[1][1], {9, 10, 11, 19, 20, 21}, {12, 13, 19, 20, 26, 27});
        initLandsHelper(lands[1][2], {11, 12, 13, 21, 22, 23}, {14, 15, 20, 21, 28, 29});
        initLandsHelper(lands[1][3], {13, 14, 15, 23, 24, 25}, {16, 17, 21, 22, 30, 31});
        initLandsHelper(lands[2][0], {16, 17, 18, 27, 28, 29}, {23, 24, 33, 34, 39, 40});
        initLandsHelper(lands[2][1], {18, 19, 20, 29, 30, 31}, {25, 26, 34, 35, 41, 42});
        initLandsHelper(lands[2][2], {20, 21, 22, 31, 32, 33}, {27, 28, 35, 36, 43, 44});
        initLandsHelper(lands[2][3], {22, 23, 24, 33, 34, 35}, {29, 30, 36, 37, 45, 46});
        initLandsHelper(lands[2][4], {24, 25, 26, 35, 36, 37}, {31, 32, 37, 38, 47, 48});
        initLandsHelper(lands[3][0], {28, 29, 30, 38, 39, 40}, {40, 41, 49, 50, 54, 55});
        initLandsHelper(lands[3][1], {30, 31, 32, 40, 41, 42}, {42, 43, 50, 51, 56, 57});
        initLandsHelper(lands[3][2], {32, 33, 34, 42, 43, 44}, {44, 45, 51, 52, 58, 59});
        initLandsHelper(lands[3][3], {34, 35, 36, 44, 45, 46}, {46, 47, 52, 53, 60, 61});
        initLandsHelper(lands[4][0], {39, 40, 41, 47, 48, 49}, {55, 56, 62, 63, 66, 67});
        initLandsHelper(lands[4][1], {41, 42, 43, 49, 50, 51}, {57, 58, 63, 64, 68, 69});
        initLandsHelper(lands[4][2], {43, 44, 45, 51, 52, 53}, {59, 60, 64, 65, 70, 71});
    }

    // Place a settlement at a specific vertex
    bool Board::placeSettlement(int vertexId, Player &player, bool firstRound) {
        for (auto &vertex : vertices) {
            if (vertex.id == vertexId) {
                if (isVertexAvilable(vertex)) {
                    cout << "Vertex already in use." << endl;
                    return false;
                }

                if (!firstRound && !isConnectedToPlayerRoad(vertex, player)) {
                    cout << "Vertex not reachable, there is no road to this vertex." << endl;
                    return false;
                }

                if (hasNeighboureSettlement(vertex)) {
                    cout << "Settlement already connected to an adjacent vertex." << endl;
                    return false;
                }

                placeSettlementAtVertex(vertex, player);
                cout << "Settlement placed successfully." << endl;
                return true;
            }
        }

        return false;
    }

    // Check if a vertex is available for building
    bool Board::isVertexAvilable(const Vertex &vertex) const {
        return !vertex.owner.empty();
    }

    // Check if a vertex is connected to any of the player's roads
    bool Board::isConnectedToPlayerRoad(const Vertex &vertex, Player &player) const {
        for (auto &edgeId : vertex.neighbors_edges) {
            for (auto &edge : edges) {
                if (edge.id == edgeId && edge.owner == player.getName()) {
                    return true;
                }
            }
        }
        return false;
    }

    // Check if a vertex has a neighboring settlement
    bool Board::hasNeighboureSettlement(const Vertex &vertex) const {
        for (auto &neighborId : vertex.neighbors_vertice) {
            if (!vertices[(size_t)neighborId].owner.empty()) {
                return true;
            }
        }
        return false;
    }

    // Place a settlement at a specific vertex
    void Board::placeSettlementAtVertex(Vertex &vertex, Player &player) {
        vertex.setType("settlement");
        vertex.setOwner(player.getName());
    }

    // Place a road at a specific edge
    bool Board::placeRoad(int edgeId, Player &player) {
        for (auto &edge : edges) {
            if (edge.id == edgeId) {
                if (isEdgeAvilable(edge)) {
                    cout << "Edge already in use." << endl;
                    return false;
                }
                if (!isConnectedToPlayerRoad(edge, player) && !isConnectedToPlayerSettlement(edge, player)) {
                    cout << "Not reachable, no road and settlement connected to this edge." << std::endl;
                    return false;
                }

                placeRoadAtEdge(edge, player);
                cout << "Road placed successfully." << endl;
                return true;
            }
        }
        return false;
    }

    // Check if an edge is available for building
    bool Board::isEdgeAvilable(const Edge &edge) const {
        return !edge.owner.empty();
    }

    // Check if an edge is connected to any of the player's roads
    bool Board::isConnectedToPlayerRoad(const Edge &edge, Player &player) const {
        for (auto &neighborEdgeId : edge.neighbors_edges) {
            for (auto &e : edges) {
                if (e.id == neighborEdgeId && e.owner == player.getName()) {
                    return true;
                }
            }
        }
        return false;
    }

    // Place a road at a specific edge
    void Board::placeRoadAtEdge(Edge &edge, Player &player) {
        edge.owner = player.getName();
    }

    // Check if an edge is connected to any of the player's settlements
    bool Board::isConnectedToPlayerSettlement(const Edge &edge, Player &player) const {
        for (auto &vertexId : edge.neighbors_vertice) {
            for (auto &v : vertices) {
                if (v.id == vertexId && v.owner == player.getName() && v.type == "settlement") {
                    return true;
                }
            }
        }
        return false;
    }

    // Upgrade a settlement to a city
    bool Board::upgradeSettlement(int vertexId, Player &player) {
        for (auto &vertex : vertices) {
            if (vertex.id == vertexId && vertex.owner == player.getName() && vertex.isSettlement()) {
                vertex.type = "city";
                cout << "Upgraded to city successfully." << endl;
                return true;
            }
        }
        return false;
    }

    // Get a reference to a Land object
    Land &Board::getLand(int i) {
        size_t index = static_cast<size_t>(i);
        if (index < 0 || index >= 19) {
            throw invalid_argument("Invalid land index");
        }
        if (index < 3) {
            return lands[0][index];
        } else if (index < 7) {
            return lands[1][index - 3];
        } else if (index < 12) {
            return lands[2][index - 7];
        } else if (index < 16) {
            return lands[3][index - 12];
        } else {
            return lands[4][index - 16];
        }
    }

    // Get a reference to a Vertex object
    Vertex &Board::getVertex(int vertexId) {
        if (vertexId < 0 || vertexId >= vertices.size()) {
            throw invalid_argument("Invalid vertex index");
        }
        return vertices[static_cast<size_t>(vertexId)];
    }

    // Get a reference to an Edge object
    Edge &Board::getEdge(int edgeId) {
        if (edgeId < 0 || edgeId >= edges.size()) {
            throw invalid_argument("Invalid edge index");
        }
        return edges[static_cast<size_t>(edgeId)];
    }

    // Distribute resources to a player based on a dice roll result
    void Board::giveResources(Player &player, int result) {
        for (int i = 0; i < 19; i++) {
            Land &land = getLand(i);
            if (land.number == result) {
                for (int vertexId : land.vertices) {
                    Vertex &vertex = getVertex(vertexId);
                    if (vertex.owner == player.getName()) {
                        if (vertex.isCity()) {
                            player.addResource(land.type, 2);
                            cout << player.getName() << " got 2 " << land.type << " from a city." << endl;
                        } else if (vertex.isSettlement()) {
                            player.addResource(land.type, 1);
                            cout << player.getName() << " got 1 " << land.type << " from a settlement." << endl;
                        }
                    }
                }
            }
        }
    }

    // Validate if a settlement can be placed at a specific vertex
    bool Board::isValidSettlementAtVertex(int location) {
        if (location < 0 || location >= vertices.size()) {
            cout << "Error, choose another location, location is out of range, you chose: " << location << endl;
            return false;
        }
        if (isVertexAvilable(vertices[static_cast<size_t>(location)])) {
            cout << "Error, choose another vertex, vertex is occupied, you chose: " << location << endl;
            return false;
        }
        if (hasNeighboureSettlement(vertices[static_cast<size_t>(location)])) {
            cout << "Error, vertex has a neighboring settlement, you chose: " << location << endl;
            return false;
        }
        return true;
    }

    // Validate if a road can be placed at a specific edge
    bool Board::isValidRoadAtEdge(int location) {
        if (location < 0 || location >= edges.size()) {
            return false;
        }
        return !isEdgeAvilable(edges[static_cast<size_t>(location)]);
    }

    // Print the current state of the board
    void Board::printBoard() {
        cout << "********************" << endl;
        for (auto &edge : edges) {
            if (!edge.owner.empty()) {
                cout << edge.owner << " road at edge " << edge.id << endl;
            }
        }
        for (auto &vertex : vertices) {
            if (!vertex.owner.empty()) {
                if (vertex.isSettlement()) {
                    cout << vertex.owner << " settlement at vertex " << vertex.id << endl;
                } else {
                    cout << vertex.owner << " city at vertex " << vertex.id << endl;
                }
            }
        }
        cout << "********************" << endl;
    }

    // Get the size of the lands vector
    int Board::getLandsSize() const { return lands.size(); }

    // Get the size of the vertices vector
    int Board::getVerticesSize() const { return vertices.size(); }

    // Get the size of the edges vector
    int Board::getEdgesSize() const { return edges.size(); }

}
