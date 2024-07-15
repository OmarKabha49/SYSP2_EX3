#include "catan.hpp"

using namespace std;

namespace ariel
{
    // Constructor initializing the players, knights, and victory points
    Catan::Catan(Player &p1, Player &p2, Player &p3) : currentPlayerIndex(0){
        players = {p1, p2, p3};
        knightsLeft = 3;
        vectoryPointLeft = 4;
    }

    // Get a reference to the game board
    Board &Catan::getBoard() { return board; }

    // End the current player's turn
    void Catan::endTurn() { nextPlayer(); }

    // Find a player by name
    Player *Catan::findPlayer(const string &name){
        for (auto &player : players){
            if (player.getName() == name) { return &player; }
        }
        return nullptr;
    }

    // Get the current player
    Player &Catan::getCurrentPlayer() { return players[currentPlayerIndex]; }

    // Check if the game has ended (a player has 10 or more points)
    bool Catan::isGameEnded(){
        for (auto &player : players){
            if (player.getPoints() >= 10){
                return true;
            }
        }
        return false;
    }

    // Choose the starting player randomly
    void Catan::ChooseStartingPlayer(){
        random_device rd;
        mt19937 g(rd());
        shuffle(players.begin(), players.end(), g);
        currentPlayerIndex = 0;

        cout << "The player list: " << endl;
        for (auto &player : players){
            cout << player.getName() << endl;
        }
    }

    // Move to the next player
    void Catan::nextPlayer() {
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    }

    // Move to the previous player
    void Catan::previousPlayer(){
        currentPlayerIndex = (currentPlayerIndex + players.size() - 1) % players.size();
    }

    // Print the winner of the game
    void Catan::printWinner(){
        for (auto &player : players){
            if (player.getPoints() >= 10){
                cout << "The winner is: " << player.getName() << endl;
                return;
            }
        }
        cout << "The game is not finished, no winner yet." << endl;
    }

    // Roll the dice and distribute resources
    void Catan::rollDice(Board &board){
        srand(time(0));
        int result = rand() % 6 + 1 + rand() % 6 + 1;
        cout << "The roll dice result is: " << result << endl;

        if (result == 7){
            for (auto &player : players){
                player.RolledAtSeven();
            }
            return;
        }

        for (auto &player : players){
            board.giveResources(player, result);
        }
    }

    // Place a settlement on the board
    void Catan::placeSettlement(Player &player, Board &board){
        int vertex_num;
        if (player.getNumOfSettlementsAndCities() < 2){
            cout << player.getName() << ", choose the number of vertex to place your settlement: ";
            while (!(cin >> vertex_num) || !board.isValidSettlementAtVertex(vertex_num)){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Error, enter a valid location for your settlement: ";
            }
            if (vertex_num < 0 || vertex_num > 53){
                cout << "Error, invalid vertex ID." << endl;
                return;
            }
            if (board.placeSettlement(vertex_num, player, true)){
                player.increaseNumOfSettlements();
                return;
            }
        }
        else{
            if (player.haveEnoughResources("settlement")){
                cout << player.getName() << ", choose where do you want to place your settlement: ";
                while (!(cin >> vertex_num) || !board.isValidSettlementAtVertex(vertex_num)){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Error, please enter a valid location for your settlement: ";
                }
                if (vertex_num < 0 || vertex_num > 53){
                    cout << "Invalid vertex ID." << endl;
                    return;
                }
                if (board.placeSettlement(vertex_num, player, false)){
                    player.increaseNumOfSettlements();
                    player.decreaseTheResources("settlement");
                    return;
                }
            }
            else{
                cout << "You don't have enough resources to place a settlement." << endl;
                return;
            }
        }
    }

    // Upgrade a settlement to a city
    void Catan::upgradeSettlement(Player &player, Board &board){
        int vertex_Num;
        if (player.haveEnoughResources("city")){
            cout << player.getName() << ", choose the settlement that you want to upgrade: ";
            while (!(cin >> vertex_Num)){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Error, please enter a valid location for your city: ";
            }
            if (board.upgradeSettlement(vertex_Num, player)){
                player.decreaseTheResources("city");
                player.increaseNumOfCities();
                return;
            }
        }
        else{
            cout << "No enough resources to upgrade settlement." << endl;
            return;
        }
    }

    // Place a road on the board
    void Catan::placeRoad(Player &player, Board &board){
        int edgeNume;

        if (player.haveEnoughResources("road")){
            cout << player.getName() << ", choose the edge num that you want to place your road: ";
            while (!board.isValidRoadAtEdge(edgeNume) || !(cin >> edgeNume)){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Error, please enter a valid location for your road: ";
            }
            if (edgeNume < 0 || edgeNume > 71){
                cout << "Invalid edge ID." << endl;
                return;
            }
            if (board.placeRoad(edgeNume, player)){
                player.decreaseTheResources("road");
                return;
            }
        }
        else{
            cout << "No enough resources to place road." << endl;
            return;
        }
    }

    // Trade resources with another player
    bool Catan::trade(Player &player){
        string name, giveResource, receiveResource;
        char choice;

        cout << "Do you want to trade a Knight card? (y/n): ";
        cin >> choice;

        if (choice == 'y'){
            cout << "Do you want to sell or buy a Knight card? (s/b): ";
            cin >> choice;

            if (choice == 's' && player.getAmountOfKnights() == 0){
                cout << "You don't have any Knight cards." << endl;
                return false;
            }

            cout << "Enter the name of the player you want to trade with: ";
            cin >> name;

            Player *other = findPlayer(name);
            if (other == nullptr){
                cout << "Player not found." << endl;
                return false;
            }

            if (other->getName() == player.getName()){
                cout << "You cannot trade with yourself." << endl;
                return false;
            }

            if (choice == 's'){ sellKnight(player, *other); }
            else if (choice == 'b'){ return buyKnight(player, *other); }
            else{
                cout << "Invalid choice." << endl;
                return false;
            }
        }
        else{
            cout << "Enter the name of the player you want to trade with: ";
            cin >> name;

            Player *other = findPlayer(name);

            if (other->getName() == player.getName()){
                cout << "You cannot trade with yourself." << endl;
                return false;
            }

            if (other == nullptr){
                cout << "Player not found." << endl;
                return false;
            }

            cout << "Enter the resource you want to give: ";
            cin >> giveResource;
            cout << "Enter the resource you want to receive: ";
            cin >> receiveResource;
            cout << "Enter the amount you want to give: ";
            int giveAmount;
            cin >> giveAmount;
            cout << "Enter the amount you want to receive: ";
            int receiveAmount;
            cin >> receiveAmount;

            player.trade(*other, giveResource, receiveResource, giveAmount, receiveAmount);
        }

        return false;
    }

    // Buy a development card
    void Catan::buyDevelopmentCard(Player &player){
        if (player.haveEnoughResources("development card")){
            player.haveEnoughResources("development card");
            srand(time(0));
            int card = rand() % 5 + 1;
            while (knightsLeft == 0 && card == 1 || vectoryPointLeft == 0 && card == 5){
                card = rand() % 5 + 1;
            }

            if (card == 1){
                player.addDevelopmentCard("knight");
                knightsLeft--;
                cout << "You have bought a knight card." << endl;
            }
            else if (card == 2){
                player.addDevelopmentCard("year of plenty");
                cout << "You have bought a year of plenty card." << endl;
            }
            else if (card == 3){
                player.addDevelopmentCard("monopoly");
                cout << "You have bought a monopoly card." << endl;
            }
            else if (card == 4){
                player.addDevelopmentCard("road building");
                cout << "You have bought a road building card." << endl;
            }
            else if (card == 5){
                player.addDevelopmentCard("victory point");
                cout << "You have bought a victory point card." << endl;
                vectoryPointLeft--;
            }

            cout << "You have bought a development card." << endl;
        }
        else{
            cout << "Insufficient resources to buy development card." << endl;
        }
    }

    // Play a development card
    void Catan::playDevelopmentCard(Player &player){
        if (player.getAmountOfDevCards() == 0){
            cout << "You do not have any development cards." << endl;
            return;
        }
        int chosenCard;
        cout << "Which development card do you want to play? (1-3): " << endl;
        cout << "1. Year of Plenty" << endl;
        cout << "2. Monopoly" << endl;
        cout << "3. Road Building" << endl;
        cout << "Enter your choice: ";
        while (!(cin >> chosenCard) || chosenCard < 1 || chosenCard > 3){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter a number between 1 and 3: ";
        }
        switch (chosenCard){
        case 1:
            playYearOfPlenty(player);
            break;
        case 2:
            playMonopoly(player);
            break;
        case 3:
            playRoadBuilding(player);
            break;
        }
    }

    // Sell a knight card to another player
    bool Catan::sellKnight(Player &player, Player &other){
        cout << "Enter the number of Knight cards you want to sell: ";
        int numOfCards;
        cin >> numOfCards;
        if (numOfCards > player.getAmountOfKnights()){
            cout << "You don't have that many Knight cards." << endl;
            return false;
        }
        cout << "What resource do you want in return? ";
        string resource;
        cin >> resource;
        cout << "How many " << resource << " do you want in return? ";
        int amount;
        cin >> amount;
        if (other.haveResources(resource, amount)){
            other.decreaseTheResources(resource, amount);
            player.addResource(resource, amount);
            player.addKnights(-numOfCards);
            other.addKnights(numOfCards);
            return true;
        }
        else{
            cout << "The other player doesn't have that many " << resource << "." << endl;
            return false;
        }
    }

    // Buy a knight card from another player
    bool Catan::buyKnight(Player &player, Player &other){
        int numOfKnights = other.getAmountOfKnights();
        if (numOfKnights == 0){
            cout << "The other player doesn't have any Knight cards." << endl;
            return false;
        }

        cout << "Enter the number of Knight cards you want to buy: ";
        int numOfCards;
        cin >> numOfCards;

        if (numOfCards > numOfKnights){
            cout << "The other player doesn't have that many Knight cards." << endl;
            return false;
        }

        cout << "What resource are you willing to pay? " << endl;
        string resource;
        cin >> resource;
        cout << "How many " << resource << " do you want to pay? ";
        int amount;
        cin >> amount;

        if (player.haveResources(resource, amount)){
            player.decreaseTheResources(resource, amount);
            other.addResource(resource, amount);
            player.addKnights(numOfCards);
            other.addKnights(-numOfCards);
            return true;
        }
        else{
            cout << "You don't have that many " << resource << "." << endl;
            return false;
        }
    }

    // Play the "Year of Plenty" development card
    void Catan::playYearOfPlenty(Player &player){
        if (player.haveEnoughResources("year of plenty")){
            player.decreaseTheResources("year of plenty");

            string resource1, resource2;
            cout << "Enter the first resource: ";
            cin >> resource1;
            cout << "Enter the second resource: ";
            cin >> resource2;

            player.addResource(resource1, 1);
            player.addResource(resource2, 1);
        }
        else{
            cout << "Insufficient resources to play year of plenty." << endl;
            return;
        }
    }

    // Play the "Monopoly" development card
    void Catan::playMonopoly(Player &player){
        if (player.haveEnoughResources("monopoly")){
            player.decreaseTheResources("monopoly");

            string resource;
            cout << "Enter the resource: ";
            cin >> resource;

            for (auto &other : players){
                if (other.getName() != player.getName()){
                    int amount = other.getAmountOfResources(resource);
                    player.addResource(resource, amount);
                    other.decreaseTheResources(resource, amount);
                    cout << "You got " << amount << " " << resource << " from " << other.getName() << "." << endl;
                }
            }
            cout << "Resources taken successfully." << endl;
        }
        else{
            cout << "Insufficient resources to play monopoly." << endl;
            return;
        }
    }

    // Play the "Road Building" development card
    void Catan::playRoadBuilding(Player &player){
        player.addResource("brick", 2);
        player.addResource("lumber", 2);
        placeRoad(player, board);
        placeRoad(player, board);
    }
}
