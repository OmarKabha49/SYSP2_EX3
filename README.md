
# Simplified Settlers of Catan

## Table of Contents
1. [Introduction](#introduction)
2. [Project Structure](#project-structure)
3. [Getting Started](#getting-started)
4. [Classes and Methods](#classes-and-methods)
5. [Usage](#usage)
6. [Testing](#testing)
7. [Future Enhancements](#future-enhancements)
8. [Contributing](#contributing)
9. [License](#license)

## Introduction
This project is a simplified version of the popular board game "The Settlers of Catan". It is implemented in C++ and is designed to accommodate three players. The game involves building settlements, roads, and cities, collecting resources, and earning points to win the game.

## Project Structure
The project consists of several files:

- `land.hpp`: Defines the `Land` class, representing a land hexagon on the game board.
- `edge.hpp`: Defines the `Edge` class, representing a road on the game board.
- `vertex.hpp`: Defines the `Vertex` class, representing a corner of the land hexagons on the game board.
- `board.cpp` and `board.hpp`: Implementation and header file for the `Board` class, which manages the game board.
- `catan.cpp` and `catan.hpp`: Implementation and header file for the `Catan` game class, which controls the game flow.
- `player.cpp` and `player.hpp`: Implementation and header file for the `Player` class, which manages player-related actions.
- `main.cpp`: The main file that initializes and starts the game.

## Getting Started
To get started with this project, follow these steps:

1. Clone the repository:
    \`\`\`bash
    https://github.com/OmarKabha49/SYSP2_EX3.git
    \`\`\`

2. Navigate to the project directory:
    \`\`\`bash
    cd simplified-catan
    \`\`\`

3. Compile the project using the provided command:
    \`\`\`bash
    g++ -o catan main.cpp board.cpp player.cpp catan.cpp
    \`\`\`

4. Run the game:
    \`\`\`bash
    ./catan
    \`\`\`

## Classes and Methods

### Land Class (`land.hpp`)
- **Attributes**:
  - `type`: Resource type of the land (e.g., wood, brick).
  - `number`: Dice number associated with the land.
  - `vertices`: Indices of the vertices adjacent to the land.
  - `edges`: Indices of the edges adjacent to the land.

### Edge Class (`edge.hpp`)
- **Attributes**:
  - `id`: Unique identifier for the edge.
  - `owner`: The player who owns the road.
  - `neighbors_vertice`: Indices of neighboring vertices.
  - `neighbors_edges`: Indices of neighboring edges.

### Vertex Class (`vertex.hpp`)
- **Attributes**:
  - `id`: Unique identifier for the vertex.
  - `owner`: The player who owns the settlement or city.
  - `neighbors_vertice`: Indices of neighboring vertices.
  - `neighbors_edges`: Indices of neighboring edges.

### Board Class (`board.cpp`, `board.hpp`)
- **Methods**:
  - `init()`: Initializes the board with lands, vertices, and edges.
  - `placeSettlementAtVertex()`: Places a settlement at a specified vertex.
  - `placeRoadAtEdge()`: Places a road at a specified edge.
  - `upgradeSettlement()`: Upgrades a settlement to a city.
  - `giveResources()`: Distributes resources based on dice rolls.
  - `printBoard()`: Prints the current state of the board.

### Player Class (`player.cpp`, `player.hpp`)
- **Methods**:
  - `addResource()`: Adds resources to the player.
  - `trade()`: Trades resources with another player.
  - `decreaseTheResources()`: Decreases the player's resources.
  - `RolledAtSeven()`: Handles the event when a 7 is rolled.
  - `printResources()`: Prints the player's resources.
  - `increaseNumOfSettlements()`: Increases the number of settlements.
  - `increaseNumOfCities()`: Increases the number of cities.
  - `addDevelopmentCard()`: Adds a development card to the player.
  - `getPoints()`: Calculates the player's points.

### Catan Class (`catan.cpp`, `catan.hpp`)
- **Methods**:
  - `ChooseStartingPlayer()`: Randomly selects the starting player.
  - `nextPlayer()`: Moves to the next player.
  - `previousPlayer()`: Moves to the previous player.
  - `printWinner()`: Prints the winner of the game.
  - `rollDice()`: Rolls the dice and distributes resources.
  - `endTurn()`: Ends the current player's turn.
  - `placeSettlement()`: Places a settlement on the board.
  - `upgradeSettlement()`: Upgrades a settlement to a city.
  - `placeRoad()`: Places a road on the board.
  - `playDevelopmentCard()`: Plays a development card.
  - `buyDevelopmentCard()`: Buys a development card.
  - `isGameEnded()`: Checks if the game has ended.
  - `trade()`: Trades resources with another player.
  - `sellKnight()`: Sells a knight card to another player.
  - `buyKnight()`: Buys a knight card from another player.

