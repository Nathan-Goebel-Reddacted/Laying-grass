#ifndef CELL_HPP
#define CELL_HPP
#include <iostream>
#include <random>
#include <algorithm>
#include <queue>
#include <string>
#include "Player.hpp"
#include "Board.hpp"
#include "Cell.hpp"
#include "Piece.hpp"

class Cell
{
    public:
        Cell();
        Cell(int x,int y);
        virtual ~Cell();
        virtual void print_a_cell()=0;
        int get_x();
        int get_y();
        /*set_x(int x);
        set_y(int y);*/
        virtual Player* get_owner();
    protected:

    private:
        int coor_x;
        int coor_y;
};

class Empty_Cell : public Cell
{
    public:
        Empty_Cell(int x, int y);
        ~Empty_Cell();
        void print_a_cell();
    protected:

    private:
};

class Tile_Cell : public Cell
{
    public:
        Tile_Cell(int x, int y,Player* owner,Piece* Tiles);
        ~Tile_Cell();
        void print_a_cell();
        Player* get_owner();

    protected:

    private:
        Player* owner;
        Piece* Tile;
};

class Any_Cell : public Cell
{
    public:
        Any_Cell(int x, int y,Player* owner);
        ~Any_Cell();
        void print_a_cell();
        Player* get_owner();
    protected:

    private:
        Player* owner;
};




#endif // CELL_HPP















