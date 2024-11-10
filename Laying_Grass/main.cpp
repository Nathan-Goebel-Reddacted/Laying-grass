#include <iostream>
#include <random>
#include <algorithm>
#include <queue>
#include <vector>
#include <deque>
#include "Player.hpp"
#include "Board.hpp"
#include "Cell.hpp"
#include "Piece.hpp"

using namespace std;

void Turn_sequence(queue<Player>& Play_Order, deque<Piece>& Draw_bag, Board& Curr_Board);
void display_next_pieces(deque<Piece>& Draw_bag, int count);
void place_a_tile(Piece curr_piece, queue<Player>& Play_Order, Board& Curr_Board, Player& curr_player);
void exchange_tile(deque<Piece>& Draw_bag,Piece& curr_piece);

int main() {
    int nb_piece;
    random_device rd;
    mt19937 g(rd());

    int nb_player;
    // Initialize player
    do {
        cout << "Hello world!\nPlease enter the number of players: ";
        cin >> nb_player;
    } while (nb_player < 2 || nb_player > 9);

    vector<Player> player_List;
    for (int i = 0; i < nb_player; ++i) {
        player_List.push_back(Player());
    }
    shuffle(player_List.begin(), player_List.end(), g);

    queue<Player> Play_Order;
    for (auto& player : player_List) {
        Play_Order.push(player);
    }

    // Initialize board
    Board Curr_Board(nb_player, &Play_Order);
    Curr_Board.print_board();

    // Initialize pieces
    nb_piece = round(nb_player * 10.67);
    vector<int> all_pieces(69);
    iota(all_pieces.begin(), all_pieces.end(), 1);
    shuffle(all_pieces.begin(), all_pieces.end(), g);

    deque<Piece> Draw_bag;
    for (int i = 0; i < nb_piece; i++) {
        Draw_bag.push_back(Piece(all_pieces[i]));
    }

    cout << "Game starts!" << endl;
    Turn_sequence(Play_Order, Draw_bag, Curr_Board);

    return 0;
}

void Turn_sequence(queue<Player>& Play_Order, deque<Piece>& Draw_bag, Board& Curr_Board) {
    int turn_limit = 9 * Play_Order.size();

    for (int i = 0; i < turn_limit; ++i) {
        Player& curr_player = Play_Order.front();
        Piece curr_piece = Draw_bag.front();
        Draw_bag.pop_front();


        cout << curr_player.get_name() << "'s Turn - Round " << i + 1 << endl;
        cout << "Current tile:" << endl;
        curr_piece.display();

        cout << "Next tiles:" << endl;
        display_next_pieces(Draw_bag, 5);
        Curr_Board.print_board();

        char choice_var;
        do {
            cout << "TAKE A TILE (T)" << endl;
            cout << "EXCHANGE A TILE (" << curr_player.get_coupon() << " available) (E)" << endl;
            cout << "DISPLAY QUEUE (D)" << endl;
            cin >> choice_var;
            choice_var = toupper(choice_var);

            if (choice_var != 'T' && choice_var != 'E' && choice_var != 'D') {
                cout << "No valid entry" << endl;
            }
        } while (choice_var != 'T' && choice_var != 'E' && choice_var != 'D');

        switch (choice_var) {
            case 'T':
                place_a_tile(curr_piece, Play_Order, Curr_Board, curr_player);
                break;
            case 'E':
                exchange_tile(Draw_bag,curr_piece);
                break;
            case 'D':
                cout << "Next tiles:" << endl;
                display_next_pieces(Draw_bag, 5);
                break;

        }
    }
}

void display_next_pieces(deque<Piece>& Draw_bag, int count) {
    int max_pieces = min(count, static_cast<int>(Draw_bag.size()));
    int max_rows = 0;

    for (int j = 0; j < max_pieces; ++j) {
        max_rows = max(max_rows, static_cast<int>(Draw_bag[j].get_shape().size()));
    }

    for (size_t row = 0; row < static_cast<size_t>(max_rows); ++row) {
        for (int j = 0; j < max_pieces; ++j) {
            const auto& shape = Draw_bag[j].get_shape();
            if (row < shape.size()) {
                for (int cell : shape[row]) {
                    cout << (cell ? "#" : " ");
                }
            } else {
                cout << string(shape[0].size(), ' ');
            }
            cout << "   ";
        }
        cout << endl;
    }
}

void place_a_tile(Piece curr_piece, queue<Player>& Play_Order, Board& Curr_Board, Player& curr_player) {
    int board_length = Curr_Board.Get_Board_Length();
    char choice_var;
    do {
        curr_piece.display();
        cout << "FLIP TILE (F)" << endl;
        cout << "ROTATE TILE (R)" << endl;
        cout << "PLACE TILE (P)" << endl;
        cin >> choice_var;
        choice_var = toupper(choice_var);

        if (choice_var != 'F' && choice_var != 'R' && choice_var != 'P') {
            cout << "No valid entry" << endl;
        }
    } while (choice_var != 'F' && choice_var != 'R' && choice_var != 'P');

    switch (choice_var) {
        case 'F':
            curr_piece.shape_flip();
            break;
        case 'R':
            curr_piece.shape_rotate();
            break;
        case 'P': {
            bool validMove = false;
            while (!validMove) {
                char column;
                int x, y;
                cout << "Enter column, " << curr_player.get_name() << "? (a-" << (char)('a' + board_length - 1) << "): ";
                cin >> column;

                if (column >= 'a' && column < 'a' + board_length) {
                    x = column - 'a';
                } else {
                    cout << "Invalid entry." << endl;
                    continue;
                }

                cout << "Enter row (0 to " << board_length - 1 << "): ";
                cin >> y;

                if (y < 0 || y >= board_length) {
                    cout << "Out of bounds, try again." << endl;
                    continue;
                }

                validMove = Curr_Board.place_piece(&curr_piece,x,y,&curr_player);
                if (!validMove) {
                    cout << "Move not valid, try again." << endl;
                }
            }
            break;
        }
    }
    Play_Order.push(curr_player);
    Play_Order.pop();
}

void exchange_tile(deque<Piece>& Draw_bag,Piece& curr_piece){
    int choice_var;
    do{
        cout << "what piece you want(1-5)";
        cin >> choice_var;
    }while(choice_var<1 || choice_var>5);
    for (int i=0;i<choice_var;i++){
        Draw_bag.push_back(Draw_bag.front());
        Draw_bag.pop_front();
    }
    curr_piece = Draw_bag.front();
}
