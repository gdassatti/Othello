//**********************************************//
//  GAVIN DASSATTI                              //
//  CS 2401                                     //
//  PROJECT 6C                                  //
//                                              //
//  IMPLEMENATATION FILE FOR THE OTHELLO CLASS. //
//  THIS CLASS DISPLAYS A BOARD FOR THE GAME &  //
//  UPDATES IT BASED ON USER INPUT.             //
//**********************************************//

#include "othello.h"
#include "piece.h"
#include "game.h"
#include "colors.h"
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// Restart function sets the first four pieces in place
void Othello::restart(){
    
    for(int i = 0; i < DIMENSION; ++i){

        for(int j = 0; j < DIMENSION; ++j){

            if(i == 3 && j == 3){
                board[i][j].set_color(piece::WHTE);
            }
            else if(i == 3 && j == 4){
                board[i][j].set_color(piece::BLK);
            }
            else if(i == 4 && j == 3){
                board[i][j].set_color(piece::BLK);
            }
            else if(i == 4 && j == 4){
                board[i][j].set_color(piece::WHTE);
            }
            else{
                board[i][j].set_empty();
            }

        }

    }

    main_savitch_14::game::restart();

}

// Displays the status of the board after every
// move and updates accordingly
void Othello::display_status()const{

    cout << endl;
    cout << "    1   2   3   4   5   6   7   8 " << endl;

    for(int i = 0; i < DIMENSION; ++i){

        cout << "  ---------------------------------" << endl;
        cout << char('A' + i) << " ";

        for(int j = 0; j < DIMENSION; ++j){

            cout << "|";
            board[i][j].output();

        }

        cout << "|" << endl;

    }

    cout << "  ---------------------------------" << endl;

}

// Reads in the players move and updates the pieces if
// one player flanks the other
void Othello::make_move(const std::string& move){ 
    
    if(move[0] == 'P'){
        main_savitch_14::game::make_move(move);
        return;
    }

    int row, col;
    row = int(toupper(move[0]) - 'A');
    col = int(move[1] - '1');

    game::who mover = game::next_mover();
    piece::color_state target;
    if(mover == HUMAN){
        target = piece::BLK;
    }else{
        target = piece::WHTE;
    }

    board[row][col].set_color(target);


    // Search and state change functions flip
    // searches for a flank and flips the pieces 
    // accordingly
    if(look_left(row, col, target)){
        change_left(row, col, target);
    }
    if(look_up_left(row, col, target)){
        change_up_left(row, col, target);
    }
    if(look_up(row, col, target)){
        change_up(row, col, target);
    }
    if(look_up_right(row, col, target)){
        change_up_right(row, col, target);
    }
    if(look_right(row, col, target)){
        change_right(row, col, target);
    }
    if(look_down_right(row, col, target)){
        change_down_right(row, col, target);
    }
    if(look_down(row, col, target)){
        change_down(row, col, target);
    }
    if(look_down_left(row, col, target)){
        change_down_left(row, col, target);
    }

    main_savitch_14::game::make_move(move);

}

// Checks if the move is a legal move
bool Othello::is_legal(const std::string& move)const{ 

    game::who mover = game::next_mover();

    if(move[0] == 'P' && can_player_pass(mover)){
        return true;
    }

    piece::color_state target;
    if(mover == HUMAN){
        target = piece::BLK;
    } else {
        target = piece::WHTE;
    }

    int row = int(toupper(move[0]) - 'A');
    int col = int(move[1] - '1');

    if(row > 8||row < 0||col > 8||col < 0){
        return false;
    }
    if(board[row][col].color() != piece::EMPTY){
        return false;
    }

    return(
        look_left(row, col, target) || look_up_left(row, col, target) ||
        look_up(row, col, target) || look_up_right(row, col, target) ||
        look_right(row, col, target) || look_down_right(row, col, target) ||
        look_down(row, col, target) || look_down_left(row, col, target)
    );

}

// Prompts the user to enter the move
// and reads it in
string Othello::get_user_move()const{

    string move;
    game::who mover = game::next_mover();

    if(mover == HUMAN){
        display_message("Black's Turn\n");
    }else{
        display_message("White's Turn\n");
    }

    if(can_player_pass(mover)){
        display_message("No available moves\n");
        move = "P0";
    } else {
        move = main_savitch_14::game::get_user_move();
    }

    return move;
}

// Checks if the game is over
bool Othello::is_game_over()const{

    game::who mover = game::next_mover();
    if(can_player_pass(mover) && can_player_pass(opposite(mover))){
        return true;
    }

    return false;

}

// Returns the winning player
main_savitch_14::game::who Othello::winning()const{

    int score = evaluate();

    if(score > 0){

        return HUMAN;

    }
    else if(score < 0){

        return COMPUTER;

    }
    else{

        return NEUTRAL;

    }

}

// Counts the pieces on the board
// If the score is positive player one wins
// and player two wins if the score is negative
int Othello::evaluate()const{
    
    int score = 0;

    for(int i = 0; i < DIMENSION; ++i){

        for(int j = 0; j < DIMENSION; ++j){

            if(board[i][j].color() == piece::BLK){

                ++score;

            }else if(board[i][j].color() == piece::WHTE){

                --score;

            }

        }

    }

    return score;

}

void Othello::compute_moves(std::queue<std::string>& moves)const{
    
    char row = 'A';
    char col = '1';
    string tmp = "  ";

    for(int i = 0; i < DIMENSION; ++i){

        for(int j = 0; j < DIMENSION; ++j){

            tmp[0] = char(row + i);
            tmp[1] = char(col + j);

            if(board[i][j].color() == piece::EMPTY){

                if(game::next_mover() == COMPUTER){

                    if(is_legal(tmp)){

                        moves.push(tmp);

                    }

                } else {

                    if(is_legal_previous(tmp)){

                        moves.push(tmp);

                    }
                }
            }
        }
    }
}

//******************//
// HELPER FUNCTIONS //
//******************//

bool Othello::can_player_pass(game::who player)const{

    char row = 'A';
    char col = '1';
    string tmp = "  ";

    for(int i = 0; i < DIMENSION; ++i){

        for(int j = 0; j < DIMENSION; ++j){

            tmp[0] = char(row + i);
            tmp[1] = char(col + j);

            if(board[i][j].color() == piece::EMPTY){

                if(player == game::next_mover()){

                    if(is_legal(tmp)){

                        return false;

                    }
                    
                }else{

                    if(is_legal_previous(tmp)){

                        return false;

                    }
                }
            }
        }
    }
    return true;
}

bool Othello::is_legal_previous(const string& move) const{

    game::who mover = game::last_mover();
    piece::color_state target;

    if(mover == HUMAN){
        target = piece::BLK;
    }else{
        target = piece::WHTE;
    }

    int row = int(toupper(move[0]) - 'A');
    int col = int(move[1] - '1');

    if(row > 8||row < 0||col > 8||col < 0){
        return false;
    }
    if(board[row][col].color() != piece::EMPTY){
        return false;
    }

    return(
        look_left(row, col, target) || look_up_left(row, col, target) ||
        look_up(row, col, target) || look_up_right(row, col, target) ||
        look_right(row, col, target) || look_down_right(row, col, target) ||
        look_down(row, col, target) || look_down_left(row, col, target)
    );

}

//*********************//
// SEARCHING FUNCTIONS //
//*********************//

bool Othello::look_left(int row, int col, piece::color_state target)const{

    for(int tmp_col = col - 1; tmp_col >= 0; --tmp_col){

        if(board[row][tmp_col].color() == piece::EMPTY){

            return false;

        }else if(board[row][tmp_col].color() == target){

            return (col - tmp_col > 1);

        }
    }

    return false;

}

bool Othello::look_up_left(int row, int col, piece::color_state target)const{

    for(
        int tmp_col = col - 1, tmp_row = row - 1;
        tmp_col >= 0 && tmp_row >= 0;
        --tmp_col, --tmp_row
    ){

        if(board[tmp_row][tmp_col].color() == piece::EMPTY){

            return false;

        }else if(board[tmp_row][tmp_col].color() == target){

            return (col - tmp_col > 1);

        }
    }

    return false;

}

bool Othello::look_up(int row, int col, piece::color_state target)const{

    for(int tmp_row = row - 1; tmp_row >= 0; --tmp_row){

        if(board[tmp_row][col].color() == piece::EMPTY){

            return false;

        }else if(board[tmp_row][col].color() == target){

            return (row - tmp_row > 1);

        }
    }

    return false;

}

bool Othello::look_up_right(int row, int col, piece::color_state target)const{

    for(
        int tmp_col = col + 1, tmp_row = row - 1;
        tmp_col < DIMENSION && tmp_row >= 0;
        ++tmp_col, --tmp_row
    ){

        if(board[tmp_row][tmp_col].color() == piece::EMPTY){

            return false;

        }else if(board[tmp_row][tmp_col].color() == target){

            return (tmp_col - col > 1);

        }
    }

    return false;

}

bool Othello::look_right(int row, int col, piece::color_state target)const{

    for(int tmp_col = col + 1; tmp_col < DIMENSION; ++tmp_col){

        if(board[row][tmp_col].color() == piece::EMPTY){

            return false;

        }else if(board[row][tmp_col].color() == target){

            return (tmp_col - col > 1);

        }
    }

    return false;

}

bool Othello::look_down_right(int row, int col, piece::color_state target)const{

    for(
        int tmp_col = col + 1, tmp_row = row + 1;
        tmp_col < DIMENSION && tmp_row < DIMENSION;
        ++tmp_col, ++tmp_row
    ){

        if(board[tmp_row][tmp_col].color() == piece::EMPTY){

            return false;

        }else if(board[tmp_row][tmp_col].color() == target){

            return (tmp_col - col > 1);

        }
    }

    return false;

}

bool Othello::look_down(int row, int col, piece::color_state target)const{

    for(int tmp_row = row + 1; tmp_row < DIMENSION; ++tmp_row){

        if(board[tmp_row][col].color() == piece::EMPTY){

            return false;

        }else if(board[tmp_row][col].color() == target){

            return (tmp_row - row > 1);

        }
    }

    return false;

}

bool Othello::look_down_left(int row, int col, piece::color_state target)const{

    for(
        int tmp_col = col - 1, tmp_row = row + 1;
        tmp_col >= 0 && tmp_row < DIMENSION;
        --tmp_col, ++tmp_row
    ){

        if(board[tmp_row][tmp_col].color() == piece::EMPTY){

            return false;

        }else if(board[tmp_row][tmp_col].color() == target){

            return (col - tmp_col > 1);

        }
    }

    return false;

}

//************************//
// STATE CHANGE FUNCTIONS //
//************************//

void Othello::change_left(int row, int col, piece::color_state target){

    int tmp_col = col - 1;
    while(board[row][tmp_col].color() != target){

        board[row][tmp_col].flip();
        --tmp_col;

    }

}

void Othello::change_up_left(int row, int col, piece::color_state target){

    int tmp_col = col - 1;
    int tmp_row = row - 1;
    while(board[tmp_row][tmp_col].color() != target){

        board[tmp_row][tmp_col].flip();
        --tmp_row;
        --tmp_col;

    }

}

void Othello::change_up(int row, int col, piece::color_state target){

    int tmp_row = row - 1;
    while(board[tmp_row][col].color() != target){

        board[tmp_row][col].flip();
        --tmp_row;

    }

}

void Othello::change_up_right(int row, int col, piece::color_state target){

    int tmp_col = col + 1;
    int tmp_row = row - 1;
    while(board[tmp_row][tmp_col].color() != target){

        board[tmp_row][tmp_col].flip();
        ++tmp_col;
        --tmp_row;

    }

}

void Othello::change_right(int row, int col, piece::color_state target){

    int tmp_col = col + 1;
    while(board[row][tmp_col].color() != target){

        board[row][tmp_col].flip();
        ++tmp_col;

    }

}

void Othello::change_down_right(int row, int col, piece::color_state target){

    int tmp_col = col + 1;
    int tmp_row = row + 1;
    while(board[tmp_row][tmp_col].color() != target){

        board[tmp_row][tmp_col].flip();
        ++tmp_col;
        ++tmp_row;

    }

}

void Othello::change_down(int row, int col, piece::color_state target){

    int tmp_row = row + 1;
    while(board[tmp_row][col].color() != target){

        board[tmp_row][col].flip();
        ++tmp_row;

    }

}

void Othello::change_down_left(int row, int col, piece::color_state target){

    int tmp_col = col - 1;
    int tmp_row = row + 1;
    while(board[tmp_row][tmp_col].color() != target){

        board[tmp_row][tmp_col].flip();
        --tmp_col;
        ++tmp_row;

    }
}