#ifndef BOARD_HPP
#define BOARD_HPP
#include <iostream>
#include <random>
#include <algorithm>
#include <queue>
#include "Player.hpp"
#include "Board.hpp"
#include "Cell.hpp"
#include "Piece.hpp"

class Board
{
    public:
        Board(int nb_player,std::queue<Player>* Play_Order);
        virtual ~Board();
        Cell* Get_Cell(int x,int y);
        int Get_Board_Length();
        void print_board();
        bool place_piece(Piece* piece, int start_x, int start_y,Player* curr_player);
    protected:

    private:
        int board_length;
        std::vector<std::vector<Cell*>> board;
};

#endif // BOARD_HPP
