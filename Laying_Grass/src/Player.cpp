#include "Player.hpp"
#include "Board.hpp"
#include "Cell.hpp"
#include "Piece.hpp"
#include <iostream>
#include <random>
#include <algorithm>
#include <queue>
using namespace std;

Player::Player()
{
    int color_choice;
    cout << "What is your name?";
    cin >> Name;
    do{
    cout << "choose a color:\n";
    cout << "1:red 2:green 3:yellow\n";
    cout << "4:blue 5:magenta 6:cyan\n";
    if (!(cin >> color_choice)) {
            cout << "Invalid input. Please enter a number between 1 and 6.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
    }while(color_choice<1 || color_choice>6);
    Color_Code= 30+color_choice;
    Exchange_Coupon=1;
}

Player::~Player()
{
    //dtor
}

string Player::get_name(){return Name;}
int Player::get_color(){return Color_Code;}
int Player::get_coupon(){return Exchange_Coupon;}


