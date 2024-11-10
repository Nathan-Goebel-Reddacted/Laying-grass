#include "Player.hpp"
#include "Board.hpp"
#include "Cell.hpp"
#include "Piece.hpp"
#include <iostream>
#include <random>
#include <algorithm>
#include <queue>
using namespace std;

Board::Board(int nb_player,queue<Player>* Play_Order){
    //resize board
    if(nb_player < 5){board_length=20;
    }else {board_length=30;}
    board.resize(board_length,vector<Cell*>(board_length));
    // generate empty board
    for(int x=0;x<board_length;x++){
        for(int y=0;y<board_length;y++){
            board[x][y] = new Empty_Cell(x, y);
        }
    }
for (int i = 0; i < nb_player; i++) {
    print_board();
    int x, y;
    bool validMove = false;

    while (!validMove) {
        char column;
        cout << "Ou veux-tu commencer, " << Play_Order->front().get_name() << "? (a-" << (char)('a' + board_length - 1) << ")" << endl;
        cin >> column;
        if (column >= 'a' && column < 'a' + board_length) {
            x = column - 'a';
        } else {
            cout << "Coordonnée invalide. Veuillez entrer une lettre valide." << endl;
            continue;
        }
        cout << "Entrez la ligne (0 à " << board_length - 1 << "): ";
        cin >> y;
        if (y < 0 || y >= board_length) {
            cout << "Coordonnées hors du plateau. Veuillez réessayer." << endl;
            continue;
        }
        if (dynamic_cast<Empty_Cell*>(board[x][y]) != nullptr) {
            delete board[x][y];
            board[x][y] = new Any_Cell(x, y, &Play_Order->front());
            validMove = true;
        } else {
            cout << "Cette case est déjà occupée. Veuillez choisir une autre case." << endl;
        }
    }
    Player temp = Play_Order->front();
    Play_Order->pop();
    Play_Order->push(temp);
    }
    //place bonus
}

Board::~Board(){
    for (int x = 0; x < board_length; ++x) {
        for (int y = 0; y < board_length; ++y) {
            delete board[x][y];
        }
    }
}

Cell* Board::Get_Cell(int x,int y){return board[x][y];}

int Board::Get_Board_Length(){return board_length;}

void Board::print_board() {
    cout << "   ";
    for (int x = 0; x < board_length; x++) {
        cout << static_cast<char>('A' + x) << " ";
    }
    cout << endl;
    for (int y = 0; y < board_length; y++) {
        if (y+1<11){cout << y << "  ";
        }else{cout << y << " ";}
        for (int x = 0; x < board_length; x++) {
            Get_Cell(x, y)->print_a_cell();
            cout << " ";
        }
        cout << endl;
    }
}

bool Board::place_piece(Piece* piece, int start_x, int start_y,Player* curr_player) {
 // Get piece's shape matrix
    auto shape = piece->get_shape();
    int piece_height = shape.size();
    int piece_width = shape[0].size();
    int correction = 1 + (shape.size() / 2);
    bool adjacent_to_same_owner = false;

    // Loop through the shape matrix of the piece
    for (int i = 0; i < piece_height; ++i) {
        for (int j = 0; j < piece_width; ++j) {
            if (shape[i][j] == 1) { // Only place cells where shape is '1'
                int board_x = start_x + j;
                int board_y = start_y + i;

                // Check if within board limits
                if (board_x >= 0 && board_x < board_length && board_y >= 0 && board_y < board_length) {
                    int corrected_x = board_x - correction;
                    int corrected_y = board_y - correction;

                    // Check adjacency for pieces owned by the same player
                    if (!adjacent_to_same_owner) {
                        // Check left, right, top, bottom neighbors
                        if (
                            (corrected_x > 0 && dynamic_cast<Tile_Cell*>(board[corrected_x - 1][corrected_y])
                             && board[corrected_x - 1][corrected_y]->get_owner() == curr_player) ||
                            (corrected_x < board_length - 1 && dynamic_cast<Tile_Cell*>(board[corrected_x + 1][corrected_y]) &&
                             board[corrected_x + 1][corrected_y]->get_owner() == curr_player) ||
                            (corrected_y > 0 && dynamic_cast<Tile_Cell*>(board[corrected_x][corrected_y - 1]) &&
                             board[corrected_x][corrected_y - 1]->get_owner() == curr_player) ||
                            (corrected_y < board_length - 1 && dynamic_cast<Tile_Cell*>(board[corrected_x][corrected_y + 1])
                             && board[corrected_x][corrected_y + 1]->get_owner() == curr_player)) {
                            adjacent_to_same_owner = true;
                        }
                    }

                    // Check if the cell at corrected_x, corrected_y is an Empty_Cell
                    if (dynamic_cast<Empty_Cell*>(board[corrected_x][corrected_y]) != nullptr) {
                        // Clean up old Empty_Cell and place new Tile_Cell
                        delete board[corrected_x][corrected_y];
                        board[corrected_x][corrected_y] = new Tile_Cell(corrected_x, corrected_y, curr_player, piece);
                    } else {
                        cout << "There is an obstacle in the path" << endl;
                        return false;
                    }
                } else {
                    cout << "Out of the map" << endl;
                    return false;
                }
            }
        }
    }

    // If no adjacent cells with the same owner are found, placement fails
    if (!adjacent_to_same_owner) {
        cout << "Piece must be adjacent to another piece of the same owner" << endl;
        return false;
    }

    return true;
}
