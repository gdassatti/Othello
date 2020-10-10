//**********************************************//
//  GAVIN DASSATTI                              //
//  CS 2401                                     //
//  PROJECT 6C                                  //
//                                              //
//  HEADER FILE FOR THE OTHELLO CLASS. THIS     //
//  CLASS IS A CHILD OF THE GAME CLASS. THIS    //
//  FILE CONTAINS VIRTUAL AND HELPER FUNCTIONS  //
//  USED TO CONDUCT A GAME OF OTHELLO IN THE    //
//  TERMINAL.                                   //
//**********************************************//

#include "game.h"
#include "piece.h"
#include <iostream>
#include <string>
#include <queue>

#ifndef OTHELLO_H
#define OTHELLO_H


class Othello : public main_savitch_14::game{

    public:

        //*******************//
        // VIRTUAL FUNCTIONS //
        //*******************//

        // Sets the game board in it's original position
        void restart();

        // Displays and updates the board after every move
        void display_status()const;

        // Reads in a string containing the move and makes it
        void make_move(const std::string& move);

        // Returns whether or not the move is legal in the game
        bool is_legal(const std::string& move)const;

        // Overridden to prompt the user to enter their move
        std::string get_user_move()const;

        // Returns whether or not the game has ended
        bool is_game_over()const;

        // Returns the winner of the game
        main_savitch_14::game::who winning()const;

        // Counts the pieces on the board and returns the net score
        int evaluate()const;

        // Pushes all possible moves for the computer into a queue
        void compute_moves(std::queue<std::string>& moves)const;

        // Returns a clone of the game in progress
        game* clone()const{return new Othello(*this);}


        //******************//
        // HELPER FUNCTIONS //
        //******************//

        bool can_player_pass(game::who player)const;
        bool is_legal_previous(const std::string& move)const;


        //*********************//
        // SEARCHING FUNCTIONS //
        //*********************//

        bool look_left(int row, int col, piece::color_state target)const;
        bool look_up_left(int row, int col, piece::color_state target)const;
        bool look_up(int row, int col, piece::color_state target)const;
        bool look_up_right(int row, int col, piece::color_state target)const;
        bool look_right(int row, int col, piece::color_state target)const;
        bool look_down_right(int row, int col, piece::color_state target)const;
        bool look_down(int row, int col, piece::color_state target)const;
        bool look_down_left(int row, int col, piece::color_state target)const;


        //************************//
        // STATE CHANGE FUNCTIONS //
        //************************//

        void change_left(int row, int col, piece::color_state target);
        void change_up_left(int row, int col, piece::color_state target);
        void change_up(int row, int col, piece::color_state target);
        void change_up_right(int row, int col, piece::color_state target);
        void change_right(int row, int col, piece::color_state target);
        void change_down_right(int row, int col, piece::color_state target);
        void change_down(int row, int col, piece::color_state target);
        void change_down_left(int row, int col, piece::color_state target);
        
    private:

        static const int DIMENSION = 8;
        piece board[DIMENSION][DIMENSION];

};

#endif