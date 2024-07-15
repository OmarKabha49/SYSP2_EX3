#include <iostream>
#include <stdexcept>
#include <vector>

#include "player.hpp"
#include "board.hpp"
#include "catan.hpp"

using namespace std;
using namespace ariel;

// Function to place initial structures for a player
void placeStructures(Catan &catan, Player &player, Board &board){
    catan.placeSettlement(player, board);
    catan.placeRoad(player, board);
}

// Function to handle a player's turn
void playerTurn(Catan &catan, Board &board){
    int choice;
    string name, giveResource, receiveResource;
    Player &player = catan.getCurrentPlayer();

    do {
        cout << "1. Place road" << endl;
        cout << "2. Place settlement" << endl;
        cout << "3. Place city" << endl;
        cout << "4. Buy development card" << endl;
        cout << "5. Play development card" << endl;
        cout << "6. Trade resources or Knights" << endl;
        cout << "7. Print my resources" << endl;
        cout << "8. Print board data" << endl;
        cout << "9. End turn" << endl;

        cout << "Enter your choice: ";

        while (!(cin >> choice) || choice < 1 || choice > 9) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error, invalid choice. Enter a number between 1 and 9: ";
        }

        switch (choice) {
        case 1:
            catan.placeRoad(player, board);
            break;

        case 2:
            catan.placeSettlement(player, board);
            break;

        case 3:
            catan.upgradeSettlement(player, board);
            break;

        case 4:
            catan.buyDevelopmentCard(player);
            break;

        case 5:
            catan.playDevelopmentCard(player);
            break;

        case 6:
            catan.trade(player);
            break;

        case 7:
            player.printResources();
            break;

        case 8:
            board.printBoard();
            break;

        case 9:
            catan.endTurn();
            cout << "--------------------------" << endl;
            break;

        default:
            break;
        }

    } while (choice != 9);
}

int main() {
    cout << "Game started" << endl;
    cout << "Welcome to Catan" << endl;

    // Get player names
    cout << "Please enter the name of the first player: ";
    string name1;
    cin >> name1;

    cout << "Please enter the name of the second player: ";
    string name2;
    cin >> name2;

    cout << "Please enter the name of the third player: ";
    string name3;
    cin >> name3;

    // Create players
    Player p1(name1);
    Player p2(name2);
    Player p3(name3);

    // Initialize the game
    Catan catan(p1, p2, p3);
    catan.ChooseStartingPlayer();
    Board board = catan.getBoard();

    // Display board setup images
    string photo1 = "xdg-open Edges.jpg";
    string photo2 = "xdg-open Vertex.jpg";
    system(photo1.c_str());
    system(photo2.c_str());

    cout << "Every player places two settlements and two roads." << endl;

    // Place initial structures for all players
    placeStructures(catan, catan.getCurrentPlayer(), board);
    catan.nextPlayer();
    placeStructures(catan, catan.getCurrentPlayer(), board);
    catan.nextPlayer();
    placeStructures(catan, catan.getCurrentPlayer(), board);
    placeStructures(catan, catan.getCurrentPlayer(), board);
    catan.previousPlayer();
    placeStructures(catan, catan.getCurrentPlayer(), board);
    catan.previousPlayer();
    placeStructures(catan, catan.getCurrentPlayer(), board);

    cout << endl;
    cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
    cout << "             Game started" << endl;
    cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
    cout << endl;

    // Main game loop
    while (!catan.isGameEnded()) {
        cout << "@ It's " << catan.getCurrentPlayer().getName() << "'s turn. @" << endl << endl;
        catan.rollDice(board);
        cout << "Your resources: " << endl;
        catan.getCurrentPlayer().printResources();
        playerTurn(catan, board);
    }

    // Print the winner at the end of the game
    catan.printWinner();
    return 0;
}
