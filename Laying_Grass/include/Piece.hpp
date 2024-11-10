#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include <random>
#include <algorithm>
#include <queue>
#ifndef PIECE_HPP
#define PIECE_HPP


class Piece
{
    public:
        Piece(int ID);
        ~Piece();
        void shape_rotate();
        void shape_flip();

        std::vector<std::vector<int>>& get_shape();
        void set_position(int x, int y);

        int get_x();
        int get_y();

        static std::vector<std::vector<int>> get_shape_by_id(int id);

        void display();
    protected:

    private:
        int id;
        std::vector<std::vector<int>> shape;
        int coor_x;
        int coor_y;

};

#endif // PIECE_HPP
