//******************************************//
//  GAVIN DASSATTI                          //
//  CS 2401                                 //
//  PROJECT 6C                              //
//                                          //
//  IMPLEMENTATION FOR THE PIECE CLASS.     //
//  INCLUDES FUNCTIONS THAT DISPLAY OR      //
//  UPDATE GAME PIECES ON THE BOARD.        //
//******************************************//

#include <iostream>
#include <cstdlib>
#include <string>
#include "piece.h"
#include "colors.h"
using namespace std;


void piece::output()const{

    if(color_field == EMPTY){
        cout << "   ";
    }else if(color_field == WHTE){
        cout << B_WHITE << BLACK << " X " << RESET;
    }else{
        cout << B_BLACK << WHITE << " X " << RESET;
    }

}

void piece::set_color(color_state new_color){
    color_field = new_color;
}

void piece::set_empty(){
    color_field = EMPTY;
}

void piece::flip(){

    if(color_field == WHTE){
        color_field = BLK;
    }else{
        color_field = WHTE;
    }

}