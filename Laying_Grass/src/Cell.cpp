#include "Player.hpp"
#include "Board.hpp"
#include "Cell.hpp"
#include "Piece.hpp"
#include <iostream>
#include <random>
#include <algorithm>
#include <queue>
using namespace std;

//Cell

Cell::Cell() : coor_x(0), coor_y(0) {}

Cell::Cell(int x, int y) : coor_x(x), coor_y(y) {}

Cell::~Cell(){/*dtor*/}

int Cell::get_x(){return coor_x;}

int Cell::get_y(){return coor_y;}
/*
Cell::set_x(int x){coor_x=x;}

Cell::set_y(int y){coor_y=y;}*/

void Cell::print_a_cell(){}

Player* Cell::get_owner(){ return nullptr;}


//Empty_Cell

Empty_Cell::Empty_Cell(int x, int y) : Cell(x, y) {}

Empty_Cell::~Empty_Cell(){/*dtor*/}

void Empty_Cell::print_a_cell(){cout << ".";}



//Tile cell
Tile_Cell::Tile_Cell(int x, int y,Player* Owner,Piece* Tiles) : Cell(x, y) {
    owner=Owner;
    Tile=Tiles;
}
Tile_Cell::~Tile_Cell(){/*dtor*/}

void Tile_Cell::print_a_cell() {
    char lowerChar = tolower(owner->get_name()[0]);
    cout << "\033[" << owner->get_color() << "m" << lowerChar << "\033[0m";
}

Player* Tile_Cell::get_owner(){return owner;}

//any cell
Any_Cell::Any_Cell(int x, int y,Player* Owner) : Cell(x, y) {
    owner=Owner;
}

Any_Cell::~Any_Cell(){/*dtor*/}

void Any_Cell::print_a_cell() {
    char upperChar = toupper(owner->get_name()[0]);
    cout << "\033[" << owner->get_color() << "m" << upperChar << "\033[0m";
}

Player* Any_Cell::get_owner(){return owner;}









