#include <iostream>
#ifndef PLAYER_HPP
#define PLAYER_HPP


class Player
{
    public:
        Player();
        virtual ~Player();
        std::string get_name();
        int get_color();
        int get_coupon();
    protected:

    private:
        std::string Name;
        int Color_Code;
        int Exchange_Coupon;
};

#endif // PLAYER_HPP
