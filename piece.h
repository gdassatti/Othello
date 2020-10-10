//**************************************************//
//  GAVIN DASSATTI                                  //
//  CS 2401                                         //
//  PROJECT 6C                                      //
//                                                  //
//  HEADER FILE FOR THE PIECE CLASS. THIS CLASS     //
//  REPRESENTS A GAME PIECE ON THE GAME BOARD.      //
//  INCLUDES FUNCTIONS USED TO DISPLAY OR UPDATE    //
//  PIECES ON THE BOARD.                            //
//**************************************************//

#include <iostream>
#include <string>
#include "game.h"

#ifndef PIECE_H
#define PIECE_H

class piece{

    public:

        enum color_state {EMPTY, BLK, WHTE};
        piece() { color_field = EMPTY; }


        void output()const;

        color_state color() const{ return color_field; }

        void set_color(color_state new_color);

        void set_empty();

        void flip();

    private:

        color_state color_field;

};

#endif