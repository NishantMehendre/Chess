/***************************************************/
/* Project1:                                       */
/* Move.c: Source file for Move functions in game  */
/* Author: King's Sacrifice                        */
/* Last Updated:                                   */
/***************************************************/

#include "Object.h"
#include "Move.h"
#include <stdlib.h>
#include <stdio.h>
#include "assert.h"

/* Legal Move */
int Is_Legal(t_Position *position1, t_Position *position2, t_Game *game){

/* Paramter: Rank File Game */
/* position 1 = game->Board[rank-65][file-1] */
/* position 2 = game->Board[rank-65][file-1] */

    /* Check if position1 and position2 exist */
    assert(position1);
    assert(position2);
    if(position1 == position2){
        return 0; /* Illegal move no movement */
    }

    /* Check for Pawn */
    if (position1->Piece->Type == Pawn){
            if (position1 -> Piece -> Player == White){
                if(position2 -> Rank - position1 -> Rank == 1 && position2 ->File - position1 ->File == 0 && position2 -> Piece == NULL){
                    game->PFlag_w = 1;
                    return 1; /* legal move, one step */
                }
                else if(position2->Rank - position1->Rank == 2 && position2->File - position1->File == 0 && position1->Rank == 2 && position2->Piece == NULL && game->Board[5][(int)(position1->File)-65]->Piece == NULL){
                    game->PFlag_w = 0;
                    game->xw = position2->x;
                    game->yw = position2->y;
                    return 1; /* legal move, 2 steps */
                }
                else if(position2 -> Piece != NULL && position2 -> Rank - position1 -> Rank == 1 && abs(position2 -> File - position1 -> File) == 1 && position2->Piece -> Player == Black){
                    game->PFlag_w = 1;
                    return 2; /* legal move, capture */
                }
                else if(game->PFlag_b == 0 && position2->x == game->xb && position1 ->Rank == 5 && game ->Board[abs(position1->Rank-8)][(int)(position2->File)-65]->Piece != NULL 
                        && game ->Board[abs(position1->Rank-8)][(int)(position2->File)-65]->Piece->Player == Black 
                        && game ->Board[abs(position1->Rank-8)][(int)(position2->File)-65]->Piece->Type == Pawn
                        && position2->Rank-position1->Rank == 1 && abs(position2 -> File - position1 -> File) == 1){
                    return 5; /* en passant */
                }
                else{
                    return 0; /* illegal move */
                }
            }
            else if (position1 -> Piece -> Player == Black){
                    if(position1 -> Rank - position2 -> Rank == 1 && position2 ->File - position1 ->File == 0 && position2 -> Piece == NULL){
                        game->PFlag_b = 1;
                        return 1; /* no capture, legal move, one step */
                    }
                    else if(position1->Rank - position2->Rank == 2 && position2->File - position1->File == 0 && position1->Rank == 7 && position2->Piece == NULL && game->Board[2][(int)(position1->File)-65]->Piece == NULL){
                        game->PFlag_b = 0;
                        game->xb = position2 ->x;
                        game->yb = position2->y;
                        return 1; /* two steps */
                    }
                    else if(position1 -> Rank - position2 -> Rank == 1 && abs(position2 ->  File - position1 -> File) == 1 && position2 -> Piece != NULL && position2 -> Piece -> Player == White){
                        game->PFlag_b = 1;
                        return 2; /* capture, legal move */
                    }
                    else if(game->PFlag_w == 0 && position2->x == game->xw && position1 ->Rank == 4 && game ->Board[abs(position1->Rank-8)][(int)(position2->File)-65]->Piece != NULL 
                        && game ->Board[abs(position1->Rank-8)][(int)(position2->File)-65]->Piece->Player == White 
                        && game ->Board[abs(position1->Rank-8)][(int)(position2->File)-65]->Piece->Type == Pawn
                        && position1->Rank-position2->Rank == 1 && abs(position2 -> File - position1 -> File) == 1){
                        //*p_flagb = 1;    
                        return 5; /* en passant */
                }
                    else{
                        return 0; /* illegal move */
                    }
            }

    }

    /* Check for Bishop */
    else if (position1 -> Piece -> Type == Bishop){
            if (abs(position1 -> Rank - position2 -> Rank) != abs(position1 -> File - position2 -> File) || (position2->Piece != NULL && position1-> Piece -> Player == position2 -> Piece -> Player)){
                    return 0; /*illegal move */
            }
            else{
                int checker_b = 0;
                /* white moves up and right, black moves down and left */
                if (position1 -> Rank < position2 -> Rank && position1 -> File < position2 -> File){
                        for (int i = (abs(position1 -> Rank-8))-1, j = ((int)(position1 -> File)-65)+1; ((i < abs(position1 -> Rank-8)) && i > abs(position2->Rank-8)) && (j < (int)(position2 -> File)-65); i--, j++){
                            if (game->Board[i][j] -> Piece != NULL){
                                checker_b +=1;
                                return 0; /* illegal move, piece in path*/   
                            }
                        }
                        if (checker_b == 0){
                            if (position2 -> Piece == NULL){
                                game->PFlag_b = 1;
                                game->PFlag_w = 1;
                                return 1; /* no capture, legal move*/
                            }
                            else if (position2 -> Piece -> Player != position1 -> Piece -> Player){
                                game->PFlag_b = 1;
                                game->PFlag_w = 1;
                                return 2; /* capture, legal move*/
                                
                            }
                        }

                }
                /* white moves up and left, black moves down and right */
                else if (position1 -> Rank < position2 -> Rank && position1 -> File > position2 -> File){
                        for (int i = abs(position1 -> Rank-8)-1, j = ((int)(position1 -> File)-65)-1; (i < abs(position1 -> Rank-8) && i > abs(position2->Rank-8)) && (j > (int)(position2 -> File)-65); i--, j--){
                            if (game->Board[i][j] -> Piece != NULL){
                                checker_b +=1;
                                return 0; /* illegal move, piece in path*/   
                            }
                        }
                        if (checker_b == 0){
                            if (position2->Piece == NULL){
                                game->PFlag_b = 1;
                                game->PFlag_w = 1;
                                return 1; /* no capture, legal move*/
                            }
                            else if (position2 -> Piece -> Player != position1 -> Piece -> Player){
                                game->PFlag_b = 1;
                                game->PFlag_w = 1;
                                return 2; /* capture, legal move*/
                            }
                        }
                        
                }

                /* white moves down and left, black moves up and right */
                else if (position1 -> Rank > position2 -> Rank && position1 -> File > position2 -> File){
                        for (int i = abs(position1 -> Rank-8)+1, j = ((int)(position1 -> File)-65)-1; (i < abs(position2 -> Rank-8) && i > abs(position1->Rank-8)) && (j > (int)(position2 -> File)-65); i++, j--){
                            if (game->Board[i][j]->Piece != NULL){
                                checker_b +=1;
                                game->PFlag_b = 1;
                                game->PFlag_w = 1;
                                return 0; /* illegal move, piece in path*/   
                            }
                        }
                        if (checker_b == 0){
                            if (position2 -> Piece == NULL){
                                game->PFlag_b = 1;
                                game->PFlag_w = 1;
                                return 1; /* no capture, legal move*/
                            }
                            else if (position2 -> Piece -> Player != position1 -> Piece -> Player){
                                game->PFlag_b = 1;
                                game->PFlag_w = 1;
                                return 2; /* capture, legal move*/
                            }
                        }
                        
                }

                /* white moves down and right, black moves up and left */
                else if (position1 -> Rank > position2 -> Rank && position1 -> File < position2 -> File){
                        for (int i = abs(position1 -> Rank-8)+1, j = ((int)(position1 -> File)-65)+1; (i < abs(position2 -> Rank-8) && i > abs(position1->Rank-8)) && (j < (int)(position2 -> File)-65); i++, j++){
                            if(position1 == game->Board[i][j]){
                                continue;
                            }
                            else if (game->Board[i][j] -> Piece != NULL){
                                checker_b +=1;
                                return 0; /* illegal move, piece in path*/   
                            }
                        }
                        if (checker_b == 0){
                            if (position2->Piece == NULL){
                                game->PFlag_b = 1;
                                game->PFlag_w = 1;
                                return 1; /* no capture, legal move*/
                            }
                            else if (position2 -> Piece -> Player != position1 -> Piece -> Player){
                                game->PFlag_b = 1;
                                game->PFlag_w = 1;
                                return 2; /* capture, legal move*/
                            }
                        }        
                }

                else return 0; /* illegal move */
            }
    }

    /* Check for Rook */
    else if (position1 -> Piece -> Type == Rook) {
        int checker_r = 0;
        
        if (position2 ->Piece != NULL && position1-> Piece -> Player == position2 -> Piece -> Player){
            return 0; /* illegal move */
        }

        else {

            /* white moves up, black moves down */
            if (position1 -> Rank < position2 -> Rank && position1 -> File == position2 -> File){
                for (int r = abs(position1 -> Rank-8)-1; r < abs(position1 -> Rank-8) && r > abs(position2->Rank-8); r--){
                    if (game->Board[r][(int)(position1 -> File)-65] -> Piece != NULL){
                        checker_r += 1;
                        return 0;  /* illegal move, piece in path */
                    }
                }
                if (checker_r == 0){
                    if (position2->Piece == NULL){
                        game->PFlag_b = 1;
                        game->PFlag_w = 1;
                        if (position1->Piece->Player == White){
                            if (position1 -> File == 'A')
                            game->CFlag_wlr = 1;
                            if (position1 -> File == 'H')
                            game->CFlag_wrr = 1;
                        }
                        if (position1->Piece->Player == Black){
                            if (position1->File == 'A')
                            game->CFlag_blr = 1;
                            if (position1->File == 'H')
                            game->CFlag_brr = 1;
                        }
                            
                        return 1; /* no capture, legal move*/   
                    }
                    else if (position2 -> Piece -> Player != position1 -> Piece -> Player){
                        game->PFlag_b = 1;
                        game->PFlag_w = 1;
                        if (position1->Piece->Player == White){
                            if (position1 -> File == 'A')
                            game->CFlag_wlr = 1;
                            if (position1 -> File == 'H')
                            game->CFlag_wrr = 1;
                        }
                        if (position1->Piece->Player == Black){
                            if (position1->File == 'A')
                            game->CFlag_blr = 1;
                            if (position1->File == 'H')
                            game->CFlag_brr = 1;
                        }
                        return 2; /* capture, legal move*/
                    }
                }
            }
            /* white moves down, black moves up */
            else if (position1 -> Rank > position2 -> Rank && position1 -> File == position2 -> File){
                for (int r = abs(position1 -> Rank-8)+1; r < abs(position2 -> Rank-8) && r > abs(position1->Rank-8); r++){
                    if (game->Board[r][(int)(position1 -> File)-65] -> Piece != NULL){
                        checker_r += 1;
                        return 0; /* illegal move, piece in path */
                    }
                }
                if (checker_r == 0){
                    if (position2->Piece == NULL){
                        game->PFlag_b = 1;
                        game->PFlag_w = 1;
                        if (position1->Piece->Player == White){
                            if (position1 -> File == 'A')
                            game->CFlag_wlr = 1;
                            if (position1 -> File == 'H')
                            game->CFlag_wrr = 1;
                        }
                        if (position1->Piece->Player == Black){
                            if (position1->File == 'A')
                            game->CFlag_blr = 1;
                            if (position1->File == 'H')
                            game->CFlag_brr = 1;
                        }
                        return 1; /* no capture, legal move*/
                    }
                    else if (position2 -> Piece -> Player != position1 -> Piece -> Player){
                        game->PFlag_b = 1;
                        game->PFlag_w = 1;
                        if (position1->Piece->Player == White){
                            if (position1 -> File == 'A')
                            game->CFlag_wlr = 1;
                            if (position1 -> File == 'H')
                            game->CFlag_wrr = 1;
                        }
                        if (position1->Piece->Player == Black){
                            if (position1->File == 'A')
                            game->CFlag_blr = 1;
                            if (position1->File == 'H')
                            game->CFlag_brr = 1;
                        }
                        return 2; /* capture, legal move*/
                    }
                }
            }
            /* white moves right, black moves left */
            else if (position1 -> Rank == position2 -> Rank && position1 -> File < position2 -> File){
                for (int r = ((int)(position1 -> File)-65)+1; r < (int)(position2 -> File)-65; r++){
                    if (game->Board[abs(position1 -> Rank-8)][r] -> Piece != NULL){
                        checker_r += 1;
                        return 0; /* illegal move, piece in path */
                    }
                }
                if (checker_r == 0){
                    if (position2->Piece == NULL){
                        game->PFlag_b = 1;
                        game->PFlag_w = 1;
                        if (position1->Piece->Player == White){
                            if (position1 -> File == 'A')
                            game->CFlag_wlr = 1;
                            if (position1 -> File == 'H')
                            game->CFlag_wrr = 1;
                        }
                        if (position1->Piece->Player == Black){
                            if (position1->File == 'A')
                            game->CFlag_blr = 1;
                            if (position1->File == 'H')
                            game->CFlag_brr = 1;
                        }
                        return 1; /* no capture, legal move*/
                    }
                    else if (position2 -> Piece -> Player != position1 -> Piece -> Player){
                        game->PFlag_b = 1;
                        game->PFlag_w = 1;
                        if (position1->Piece->Player == White){
                            if (position1 -> File == 'A')
                            game->CFlag_wlr = 1;
                            if (position1 -> File == 'H')
                            game->CFlag_wrr = 1;
                        }
                        if (position1->Piece->Player == Black){
                            if (position1->File == 'A')
                            game->CFlag_blr = 1;
                            if (position1->File == 'H')
                            game->CFlag_brr = 1;
                        }
                        return 2; /* capture, legal move*/
                    }
                }
            }
            /* white moves left, black moves right */
            else if (position1 -> Rank == position2 -> Rank && position1 -> File > position2 -> File){
                for (int r = ((int)(position1 -> File)-65)-1; r > (int)(position2 -> File)-65; r--){
                    if (game->Board[abs(position1 -> Rank-8)][r] -> Piece != NULL){
                        checker_r += 1;
                        return 0; /* illegal move, piece in path */
                    }
                }
                if (checker_r == 0){
                    if (position2->Piece == NULL){
                        game->PFlag_b = 1;
                        game->PFlag_w = 1;
                        if (position1->Piece->Player == White){
                            if (position1 -> File == 'A')
                            game->CFlag_wlr = 1;
                            if (position1 -> File == 'H')
                            game->CFlag_wrr = 1;
                        }
                        if (position1->Piece->Player == Black){
                            if (position1->File == 'A')
                            game->CFlag_blr = 1;
                            if (position1->File == 'H')
                            game->CFlag_brr = 1;
                        }
                        return 1; /* no capture, legal move*/
                    }
                    else if (position2 -> Piece -> Player != position1 -> Piece -> Player){
                        game->PFlag_b = 1;
                        game->PFlag_w = 1;
                        if (position1->Piece->Player == White){
                            if (position1 -> File == 'A')
                            game->CFlag_wlr = 1;
                            if (position1 -> File == 'H')
                            game->CFlag_wrr = 1;
                        }
                        if (position1->Piece->Player == Black){
                            if (position1->File == 'A')
                            game->CFlag_blr = 1;
                            if (position1->File == 'H')
                            game->CFlag_brr = 1;
                        }
                        return 2; /* capture, legal move*/
                    }
                }
            }
            else return 0; /* illegal move */    

        }
    }
    
    /* check for knight */
    else if (position1 -> Piece -> Type == Knight){
        printf("Check for knight.\n");
        if (position2->Piece != NULL && position1 -> Piece -> Player == position2 -> Piece -> Player){
            return 0; /* illegal move, same player capture */
        }
        else if ((abs(position1 -> Rank - position2 -> Rank) == 2 && abs(position1 -> File - position2 -> File) == 1) || (abs(position1 -> Rank - position2 -> Rank) == 1 && abs(position1 -> File - position2 -> File) == 2)){
            if (position2 -> Piece == NULL){
                game->PFlag_b = 1;
                game->PFlag_w = 1;
                return 1; /* no capture, legal move*/
            }
            else if (position2 -> Piece -> Player != position1 -> Piece -> Player){
                game->PFlag_b = 1;
                game->PFlag_w = 1;
                return 2; /* capture, legal move */
            }
        }
        else return 0; /* illegal move */
    }

    /* Check for Queen */
    if (position1 -> Piece -> Type == Queen){
        int checker_q = 0;
        if (position2 -> Piece != NULL && position1 -> Piece -> Player == position2 -> Piece -> Player){
            return 0; /* illegal move, same player capture */
        }
        
        /* white moves diagonally up and right, black moves diagonally down and left */
        else if (position1 -> Rank < position2 -> Rank && position1 -> File < position2 -> File){
            if (abs(position1 -> Rank - position2 -> Rank) != (int)(abs(position1 -> File - position2 -> File))){
                return 0;
            }
            for (int i = abs(position1 -> Rank-8)-1, j = ((int)(position1 -> File)-65)+1; ((i < abs(position1 -> Rank-8)) && i > abs(position2->Rank-8)) && (j < (int)(position2 -> File)-65); i--, j++){
                if (game->Board[i][j] -> Piece != NULL){
                    checker_q +=1;
                    return 0; /* illegal move, piece in path*/   
                }
            }
            if (checker_q == 0){
                if (position2->Piece == NULL){
                    game->PFlag_b = 1;
                    game->PFlag_w = 1;
                    return 1; /* no capture, legal move*/
                }
                else if (position2 -> Piece -> Player != position1 -> Piece -> Player){
                    game->PFlag_b = 1;
                    game->PFlag_w = 1;
                    return 2; /* capture, legal move*/
                }
            }
        }
        
        /* white moves diagonally up and left, black moves diagonally down and right */
        else if (position1 -> Rank < position2 -> Rank && position1 -> File > position2 -> File){
            if (abs(position1 -> Rank - position2 -> Rank) != (int)(abs(position1 -> File - position2 -> File))){
                return 0;
            }
            for (int i = abs(position1 -> Rank-8)-1, j = ((int)(position1 -> File)-65)-1; (i < abs(position1 -> Rank-8) && i > abs(position2->Rank-8)) && (j > (int)(position2 -> File)-65); i--, j--){
                if (game->Board[i][j] -> Piece != NULL){
                    checker_q +=1;
                    return 0; /* illegal move, piece in path*/   
                }
            }
            if (checker_q == 0){
                if (position2->Piece == NULL){
                    game->PFlag_b = 1;
                    game->PFlag_w = 1;
                    return 1; /* no capture, legal move*/
                }
                else if (position2 -> Piece -> Player != position1 -> Piece -> Player){
                    game->PFlag_b = 1;
                    game->PFlag_w = 1;
                    return 2; /* capture, legal move*/
                }
            }
                
        }

        /* white moves diagonally down and left, black moves diagonally up and right */
        else if (position1 -> Rank > position2 -> Rank && position1 -> File > position2 -> File){
            if (abs(position1 -> Rank - position2 -> Rank) != (int)(abs(position1 -> File - position2 -> File))){
                return 0;
            }
            for (int i = abs(position1 -> Rank-8)+1, j = ((int)(position1 -> File)-65)-1; (i < abs(position2 -> Rank-8) && i > abs(position1->Rank-8)) && (j > (int)(position2 -> File)-65); i++, j--){
                if (game->Board[i][j]->Piece != NULL){
                    checker_q +=1;
                    return 0; /* illegal move, piece in path*/   
                }
            }
            if (checker_q == 0){
                if (position2->Piece == NULL){
                    game->PFlag_b = 1;
                    game->PFlag_w = 1;
                    return 1; /* no capture, legal move*/
                }
                else if (position2 -> Piece -> Player != position1 -> Piece -> Player){
                    game->PFlag_b = 1;
                    game->PFlag_w = 1;
                    return 2; /* capture, legal move*/
                }
            }
                
        }

        /* white moves diagonally down and right, black moves diagonally up and left */
        else if (position1 -> Rank > position2 -> Rank && position1 -> File < position2 -> File){
            if (abs(position1 -> Rank - position2 -> Rank) != (int)(abs(position1 -> File - position2 -> File))){
                return 0;
            }
            for (int i = abs(position1 -> Rank-8)+1, j = ((int)(position1 -> File)-65)+1; (i < abs(position2 -> Rank-8) && i > abs(position1->Rank-8)) && (j < (int)(position2 -> File)-65); i++, j++){
                if(position1 == game->Board[i][j]){
                    continue;
                }
                else if (game->Board[i][j] -> Piece != NULL){
                    checker_q +=1;
                    return 0; /* illegal move, piece in path*/   
                }
            }
            if (checker_q == 0){
                if (position2->Piece == NULL){
                    game->PFlag_b = 1;
                    game->PFlag_w = 1;
                    return 1; /* no capture, legal move*/
                }
                else if (position2 -> Piece -> Player != position1 -> Piece -> Player){
                    game->PFlag_b = 1;
                    game->PFlag_w = 1;
                    return 2; /* capture, legal move*/
                }
            }        
        }

        /* white moves up, black moves down */
        else if (position1 -> Rank < position2 -> Rank && position1 -> File == position2 -> File){
            for (int i = abs(position1 -> Rank-8)-1; i < abs(position1 -> Rank-8) && i > abs(position2->Rank-8); i--){
                if (game->Board[i][(int)(position1 -> File)-65] -> Piece != NULL){
                    checker_q += 1;
                    return 0;  /* illegal move, piece in path */
                }
            }
            if (checker_q == 0){
                if (position2->Piece == NULL){
                    game->PFlag_b = 1;
                    game->PFlag_w = 1;
                    return 1; /* no capture, legal move*/
                }
                else if (position2 -> Piece -> Player != position1 -> Piece -> Player){
                    game->PFlag_b = 1;
                    game->PFlag_w = 1;
                    return 2; /* capture, legal move*/
                }
            }
        }
        /* white moves down, black moves up */
        else if (position1 -> Rank > position2 -> Rank && position1 -> File == position2 -> File){
            for (int i = abs(position1 -> Rank-8)+1; i < abs(position2 -> Rank-8) && i > abs(position1->Rank-8); i++){
                if (game->Board[i][(int)(position1 -> File)-65] -> Piece != NULL){
                    checker_q += 1;
                    return 0; /* illegal move, piece in path */
                }
            }
            if (checker_q == 0){
                if (position2->Piece == NULL){
                    game->PFlag_b = 1;
                    game->PFlag_w = 1;
                    return 1; /* no capture, legal move*/
                }
                else if (position2 -> Piece -> Player != position1 -> Piece -> Player){
                    game->PFlag_b = 1;
                    game->PFlag_w = 1;
                    return 2; /* capture, legal move*/
                }
            }
        }
        /* white moves right, black moves left */
        else if (position1 -> Rank == position2 -> Rank && position1 -> File < position2 -> File){
            for (int i = ((int)(position1 -> File)-65)+1; i < (int)(position2 -> File)-65; i++){
                if (game->Board[abs(position1 -> Rank-8)][i] -> Piece != NULL){
                    checker_q += 1;
                    return 0; /* illegal move, piece in path */
                }
            }
            if (checker_q == 0){
                if (position2->Piece == NULL){
                    game->PFlag_b = 1;
                    game->PFlag_w = 1;
                    return 1; /* no capture, legal move*/
                }
                else if (position2 -> Piece -> Player != position1 -> Piece -> Player){
                    game->PFlag_b = 1;
                    game->PFlag_w = 1;
                    return 2; /* capture, legal move*/
                }
            }
        }
        /* white moves left, black moves right */
        else if (position1 -> Rank == position2 -> Rank && position1 -> File > position2 -> File){
            for (int i = ((int)(position1 -> File)-65)-1; i > (int)(position2 -> File)-65; i--){
                if (game->Board[abs(position1 -> Rank-8)][i] -> Piece != NULL){
                    checker_q += 1;
                    return 0; /* illegal move, piece in path */
                }
            }
            if (checker_q == 0){
                if (position2->Piece == NULL){
                    game->PFlag_b = 1;
                    game->PFlag_w = 1;
                    return 1; /* no capture, legal move*/
                }
                else if (position2 -> Piece -> Player != position1 -> Piece -> Player){
                    game->PFlag_b = 1;
                    game->PFlag_w = 1;
                    return 2; /* capture, legal move*/
                }
            }
        }

        else return 0; /* illegal move */    
    } 

    /* Check for King */
    else if(position1->Piece->Type == King){
        /* Check if piece in path*/
        if(position2 -> Piece != NULL && position1->Piece->Player == position2->Piece->Player && abs(position2->File-position1->File) <= 1){
            return 0;
        }
        /* Check if another piece can attack King */
        else if((abs(position1->Rank-position2->Rank) == 0 && abs(position1->File-position2->File) == 1) || (abs(position1->Rank-position2->Rank) == 1 && abs(position1->File-position2->File) == 0) || (abs(position1->Rank-position2->Rank) == 1 && abs(position1->File-position2->File) == 1)
                || ((game->CFlag_wk == 0 && game->CFlag_wrr == 0) && position1->Piece->Player == White && position1 ->Rank - position2->Rank == 0 && position2 ->File - position1->File == 2 && game->Board[7][5]->Piece == NULL && game->Board[7][6]->Piece == NULL)
                || ((game->CFlag_bk == 0 && game->CFlag_brr == 0) && position1->Piece->Player == Black && position1 ->Rank - position2->Rank == 0 && position2 ->File - position1->File == 2 && game->Board[0][5]->Piece == NULL && game->Board[0][6]->Piece == NULL)
                || ((game->CFlag_wk == 0 && game->CFlag_wlr == 0) && position1->Piece->Player == White && position1 ->Rank - position2->Rank == 0 && position1 ->File - position2->File == 2 && game->Board[7][1]->Piece == NULL && game->Board[7][2]->Piece == NULL && game->Board[7][3]->Piece == NULL)
                || ((game->CFlag_bk == 0 && game->CFlag_blr == 0) && position1->Piece->Player == Black && position1 ->Rank - position2->Rank == 0 && position1 ->File - position2->File == 2 && game->Board[0][1]->Piece == NULL && game->Board[0][2]->Piece == NULL && game->Board[0][3]->Piece == NULL)){
            
            /* Ignore the opponent piece when checking if opponent can capture the position2 */
            t_Piece *tempPiece = NULL;
            tempPiece = position2->Piece;
            position2->Piece = NULL;

            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                    /* If opponent piece can move to that position, illegal move */
                    if(game->Board[i][j]->Piece != NULL && position1->Piece->Player != game->Board[i][j]->Piece->Player){
                        if(game->Board[i][j]->Piece ->Type == King)
                            continue;
                        else if(game->Board[i][j]->Piece->Type == Pawn && game->Board[i][j]->Piece->Player != position1->Piece->Player){
                            if(game->Board[i][j]->Piece->Player == White){
                                if(game->Board[i-1][j-1] == position2 || game->Board[i-1][j+1] == position2){            
                                    position2->Piece = tempPiece;
                                    tempPiece = NULL;
                                    return 0;
                                }
                            }
                            else if(game->Board[i][j]->Piece->Player == Black){
                                if(game->Board[i+1][j-1] == position2 || game->Board[i+1][j+1] == position2){        
                                    position2->Piece = tempPiece;
                                    tempPiece = NULL;
                                    return 0;
                                }
                            }
                        }
                        else if(Is_Legal(game->Board[i][j], position2, game) == 1){
                            position2->Piece = tempPiece;
                            tempPiece = NULL;
                            return 0; /* Illegal move */
                        }
                    }
                }
            }
            position2->Piece = tempPiece;
            tempPiece = NULL;

            if((game->CFlag_wk == 0 && game->CFlag_wrr == 0) && position1->Piece->Player == White && position1 ->Rank - position2->Rank == 0 && position2 ->File - position1->File == 2 && game->Board[abs(position2->Rank-8)][(int)(position2->File)-65+1]->Piece != NULL && game->Board[abs(position2->Rank-8)][(int)(position2->File)-65+1]->Piece ->Type == Rook){
                game->PFlag_b = 1;
                game->PFlag_w = 1;
                /*if (position1->Piece->Player == White)
                game->CFlag_wk = 1;
                if (position1->Piece->Player == Black)
                game->CFlag_bk = 1;*/
                printf("King side castle\n");
                return 3;    
            }
            else if((game->CFlag_bk == 0 && game->CFlag_brr == 0) && position1->Piece->Player == Black && position1 ->Rank - position2->Rank == 0 && position2 ->File - position1->File == 2 && game->Board[abs(position2->Rank-8)][(int)(position2->File)-65+1]->Piece != NULL && game->Board[abs(position2->Rank-8)][(int)(position2->File)-65+1]->Piece ->Type == Rook){
                game->PFlag_b = 1;
                game->PFlag_w = 1;
                /*if (position1->Piece->Player == White)
                game->CFlag_wk = 1;
                if (position1->Piece->Player == Black)
                game->CFlag_bk = 1;*/
                printf("King side castle\n");
                return 3;
            }
            else if((game->CFlag_wk == 0 && game->CFlag_wlr == 0) && position1->Piece->Player == White && position1 ->Rank - position2->Rank == 0 && position1 ->File - position2->File == 2 && game->Board[abs(position2->Rank-8)][(int)(position2->File)-65-2]->Piece != NULL && game->Board[abs(position2->Rank-8)][(int)(position2->File)-65-2]->Piece ->Type == Rook){
                game->PFlag_b = 1;
                game->PFlag_w = 1;
                /*if (position1->Piece->Player == White)
                game->CFlag_wk = 1;
                if (position1->Piece->Player == Black)
                game->CFlag_bk = 1;*/
                printf("Queen side castle\n");
                return 4;
            } 
            else if((game->CFlag_bk == 0 && game->CFlag_blr == 0) && position1->Piece->Player == Black && position1 ->Rank - position2->Rank == 0 && position1 ->File - position2->File == 2 && game->Board[abs(position2->Rank-8)][(int)(position2->File)-65-2]->Piece != NULL && game->Board[abs(position2->Rank-8)][(int)(position2->File)-65-2]->Piece ->Type == Rook){
                game->PFlag_b = 1;
                game->PFlag_w = 1;
                /*if (position1->Piece->Player == White)
                game->CFlag_wk = 1;
                if (position1->Piece->Player == Black)
                game->CFlag_bk = 1;*/
                printf("Queen side castle\n");
                return 4;
            }        
            else if(position2->Piece == NULL){
                game->PFlag_b = 1;
                game->PFlag_w = 1;
                if (position1->Piece->Player == White)
                game->CFlag_wk = 1;
                if (position1->Piece->Player == Black)
                game->CFlag_bk = 1;
                return 1;    
            }
            else if(position1->Piece->Player != position2->Piece->Player){
                game->PFlag_b = 1;
                game->PFlag_w = 1;
                if (position1->Piece->Player == White)
                game->CFlag_wk = 1;
                if (position1->Piece->Player == Black)
                game->CFlag_bk = 1;
                return 2;    
            }
            
        
        }
    return 0;
    }
return 0;
}
/* Move Piece */
void movePiece(t_Position *position1, t_Position *position2, t_Game *game){
	/* Check if position1 and position2 exist */
	assert(position1);
	assert(position2);

	if(Is_Legal(position1, position2, game) == 0){
		/* Pop-up window */
		/* Error: Illegal move */
	}

	else if(Is_Legal(position1, position2, game) == 1){

		/* Change the properties of new positoin */
		position2->Piece = position1->Piece;
		position2->Piece->Position = position2;

		/* Change the properties of initial position */
		position1->Piece = NULL;
	}
    else if(Is_Legal(position1, position2, game) == 3){

        /*game->Board[abs(position1->Rank-8)][(int)(position1->File)-65+2]->Piece = position1->Piece;
        game->Board[abs(position1->Rank-8)][(int)(position1->File)-65+2]->Piece -> Position = game->Board[abs(position1->Rank-8)][(int)(position1->File)-65+2];*/
        position2->Piece = position1->Piece;
        position2->Piece->Position = position2;
        game->Board[abs(position1->Rank-8)][(int)(position1->File)-65+1]->Piece = game->Board[abs(position1->Rank-8)][(int)(position2->File)-65+1]->Piece;
        game->Board[abs(position1->Rank-8)][(int)(position1->File)-65+1]->Piece -> Position = game->Board[abs(position1->Rank-8)][(int)(position1->File)-65+1];
        position1->Piece = NULL;
        game->Board[abs(position1->Rank-8)][(int)(position2->File)-65+1] ->Piece = NULL;
        

    }
    else if(Is_Legal(position1, position2, game) == 4){

        position2->Piece = position1 ->Piece;
        position2->Piece->Position = position2;
        game->Board[abs(position1->Rank-8)][(int)(position1->File)-65-1]->Piece = game->Board[abs(position1->Rank-8)][(int)(position2->File)-65-2]->Piece;
        game->Board[abs(position1->Rank-8)][(int)(position1->File)-65-1]->Piece -> Position = game->Board[abs(position1->Rank-8)][(int)(position1->File)-65-1];
        position1->Piece = NULL;
        game->Board[abs(position1->Rank-8)][(int)(position2->File)-65-2] ->Piece = NULL;
    }
    else if(Is_Legal(position1, position2, game) == 5){
        position2->Piece = position1->Piece;
		position2->Piece->Position = position2;

		/* Change properties of position1 */
		position1->Piece = NULL;
        game->Board[abs(position1->Rank-8)][(int)(position2->File)-65]->Piece = NULL;
    }

	else{

		/* Change properties of position2 */
		// TODO: Add piece of position2 to graveyard
        free(position2->Piece);
		position2->Piece = position1->Piece;
		position2->Piece->Position = position2;

		/* Change properties of position1 */
		position1->Piece = NULL;
	}
}

/*
 En Passant 
int En_Passant(t_Position *position1, t_Position *position2){

} */

/* Check */
/* 0 -> Game continues normally */
/* 1 -> Check */
/* 2 -> CheckMate */
/*int Check(t_Piece *piece, t_Game *game, int castling_flag){
	assert(piece->Type == King);
    int a, b;

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if (piece->Position == game->Board[i][j]){
                a = i;
                b = j;
            }
        }
    }
	
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(game->Board[i][j]->Piece->Player != piece->Player){
				if(Is_Legal(game->Board[i][j], piece->Position, game, castling_flag) == 2){


					if((a-1 > 0 && a+1 < 7) && (b-1 > 0 && b+1 < 7)){
						if(Is_Legal(piece->Position, game->Board[a-1][b-1], game, castling_flag) > 0){
                            return 1;
                        }
                        else if(Is_Legal(piece->Position, game->Board[a][b-1], game, castling_flag) > 0){
                            return 1;
                        }
                        else if(Is_Legal(piece->Position, game->Board[a+1][b-1], game, castling_flag) > 0){
                            return 1;
                        }
                        else if(Is_Legal(piece->Position, game->Board[a-1][b], game, castling_flag) > 0){
                            return 1;
                        }
                        else if(Is_Legal(piece->Position, game->Board[a+1][b], game, castling_flag) > 0){
                            return 1;
                        }
                        else if(Is_Legal(piece->Position, game->Board[a-1][b+1], game, castling_flag) > 0){
                            return 1;
                        }
                        else if(Is_Legal(piece->Position, game->Board[a][b+1], game, castling_flag) > 0){
                            return 1;
                        }
                        else if(Is_Legal(piece->Position, game->Board[a+1][b+1], game, castling_flag) > 0){
                            return 1;
                        }
					}
					else{

						return 2;
					}
				}
			}
		}
	}


	return 0;
}*/

/* Check */
/* Return 1 -> check */
/* Return 0 -> no check*/
int Check(int player_count, t_Game *game){
    
    t_Position *WhiteKing = NULL;
    t_Position *BlackKing = NULL;
    
    /* Store the location of the Kings */
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            /* White King */
            if(game->Board[i][j]->Piece && game->Board[i][j]->Piece->Player == White && game->Board[i][j]->Piece->Type == King){
                WhiteKing = game->Board[i][j];
            }
            /* Black King */
            else if(game->Board[i][j]->Piece && game->Board[i][j]->Piece->Player == Black && game->Board[i][j]->Piece->Type == King){
                BlackKing = game->Board[i][j];
            }
        }
    }

    /* Check if King is under attack */
    for(int i = 0; i < 8; i ++){
        for(int j = 0; j < 8; j++){
            /* If piece exists at current location */
            if(game->Board[i][j]->Piece){
                /* Check for white */
                if(player_count%2 == 0 && WhiteKing->Piece->Player != game->Board[i][j]->Piece->Player && Is_Legal(game->Board[i][j], WhiteKing, game) == 2){
                    return 1;
                }
                /* Check for black */
                else if(player_count%2 != 0 && BlackKing->Piece->Player != game->Board[i][j]->Piece->Player && Is_Legal(game->Board[i][j], BlackKing, game) == 2){ 
                    return 1;
                }
            }
        }
    }

    return 0;
}

int Checkmate(int player_count, t_Game *game){
    //Check for Checkmate 
    t_Piece *tempb = NULL;
    t_Piece *tempw = NULL;
    for(int i = 0; i < 8; i ++){
        for(int j = 0; j < 8; j++){
            // If piece exists at current location 
            if(game->Board[i][j]->Piece){
                // Check for white 
                if(player_count%2 == 0 && game->Board[i][j]->Piece->Player == White){
                    for (int a = 0; a < 8; a++){
                        for (int b = 0; b < 8; b++){
                            if(Is_Legal(game->Board[i][j], game->Board[a][b], game) > 0){
                                if(game->Board[a][b]->Piece){
                                tempb = game->Board[a][b]->Piece;
                                tempb->Position = game->Board[a][b];
                                }
                                game->Board[a][b]->Piece = game->Board[i][j]->Piece;
                                game->Board[a][b]->Piece->Position = game->Board[a][b];
                                if(Check(player_count, game) == 0){
                                    game->Board[a][b]->Piece = tempb;
                                    if(game->Board[a][b]->Piece)
                                        game->Board[a][b]->Piece->Position = game->Board[a][b];
                                    tempb = NULL;
                                    return 0; 
                                }
                                game->Board[a][b]->Piece = tempb;
                                if(game->Board[a][b]->Piece)
                                    game->Board[a][b]->Piece->Position = game->Board[a][b];
                                tempb = NULL;
                                 
                            }
                         
                        }
                    }
                }
                // Check for black 
                else if(player_count%2 != 0 && game->Board[i][j]->Piece->Player  == Black){ 
                    for (int c = 0; c < 8; c++){
                        for (int d = 0; d < 8; d++){
                            if(Is_Legal(game->Board[i][j], game->Board[c][d], game) > 0){
                                if(game->Board[c][d]->Piece){
                                tempw = game->Board[c][d]->Piece;
                                tempw->Position = game->Board[c][d];
                                }
                                game->Board[c][d]->Piece = game->Board[i][j]->Piece;
                                game->Board[c][d]->Piece->Position = game->Board[c][d];
                                if(Check(player_count, game) == 0){
                                    game->Board[c][d]->Piece = tempw;
                                    if(game->Board[c][d]->Piece)
                                        game->Board[c][d]->Piece->Position = game->Board[c][d];
                                    tempw = NULL;
                                    return 0; 
                                }
                                game->Board[c][d]->Piece = tempw;
                                if(game->Board[c][d]->Piece)
                                    game->Board[c][d]->Piece->Position = game->Board[c][d];
                                tempw = NULL;
                                 
                            }
                            
                        }
                    }
                }
            }
        }
    }
    return 1;
}

int StalemateAI(int player_count, t_Game *game){
    t_Piece *tempb = NULL;
    t_Piece *tempw = NULL;

    if (Check(player_count, game) == 0){
        for(int i = 0; i < 8; i ++){
            for(int j = 0; j < 8; j++){
                // If piece exists at current location 
                if(game->Board[i][j]->Piece){
                    // Check for White 
                    if(player_count%2 == 0 && game->Board[i][j]->Piece->Player == White){
                        for (int a = 0; a < 8; a++){
                            for (int b = 0; b < 8; b++){
                                if(Is_Legal(game->Board[i][j], game->Board[a][b], game) > 0){
                                   if(game->Board[a][b]->Piece){
                                        tempw = game->Board[a][b]->Piece;
                                        tempw->Position = game->Board[a][b];
                                    }
                                    game->Board[a][b]->Piece = game->Board[i][j]->Piece;
                                    game->Board[a][b]->Piece->Position = game->Board[a][b]; 
                                    game->Board[i][j]->Piece = NULL;
                                    if(Check(player_count, game) == 0){
                                        game->Board[i][j]->Piece = game->Board[a][b]->Piece;
                                        game->Board[i][j]->Piece->Position = game->Board[i][j];
                                        game->Board[a][b]->Piece = tempw;
                                        if(game->Board[a][b]->Piece)
                                            game->Board[a][b]->Piece->Position = game->Board[a][b];
                                        tempw = NULL;
                                        return 0;
                                    }
                                    game->Board[i][j]->Piece = game->Board[a][b]->Piece;
                                    game->Board[i][j]->Piece->Position = game->Board[i][j];
                                    game->Board[a][b]->Piece = tempw;
                                    if(game->Board[a][b]->Piece)
                                        game->Board[a][b]->Piece->Position = game->Board[a][b];
                                    tempw = NULL;
                                }

                                
                            }
                        }
                    }
                    // Check for Black
                    else if(player_count % 2 != 0 && game->Board[i][j]->Piece->Player == Black){
                        for (int a = 0; a < 8; a++){
                            for (int b = 0; b < 8; b++){
                                if(Is_Legal(game->Board[i][j], game->Board[a][b], game) > 0){
                                    if(game->Board[a][b]->Piece){
                                            tempb = game->Board[a][b]->Piece;
                                            tempb->Position = game->Board[a][b];
                                        }
                                        game->Board[a][b]->Piece = game->Board[i][j]->Piece;
                                        game->Board[a][b]->Piece->Position = game->Board[a][b]; 
                                        game->Board[i][j]->Piece = NULL;
                                        if(Check(player_count, game) == 0){
                                            game->Board[i][j]->Piece = game->Board[a][b]->Piece;
                                            game->Board[i][j]->Piece->Position = game->Board[i][j];
                                            game->Board[a][b]->Piece = tempw;
                                            if(game->Board[a][b]->Piece)
                                                game->Board[a][b]->Piece->Position = game->Board[a][b];
                                            tempb = NULL;
                                        return 0;
                                        }
                                        game->Board[i][j]->Piece = game->Board[a][b]->Piece;
                                        game->Board[i][j]->Piece->Position = game->Board[i][j];
                                        game->Board[a][b]->Piece = tempw;
                                        if(game->Board[a][b]->Piece)
                                            game->Board[a][b]->Piece->Position = game->Board[a][b];
                                        tempb = NULL;
                                }
                            }
                        }
                    }
                }
            }
        }
        return 1;
    }
    return 0;

}

/* Stalemate */
/* Returns 1 if Stalemate */
/* Returns 0 if Not */
int Stalemate(int player_count, t_Game *game){
    /* Check for White */
    if(player_count%2 == 0){
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                if(game->Board[i][j]->Piece && game->Board[i][j]->Piece->Player == White){
                    for(int k = 0; k < 8; k++){
                        for(int l = 0; l < 8; l++){
                            if(Is_Legal(game->Board[i][j], game->Board[k][l], game) > 0){
                                t_Game *tempGame = CopyGame(game);
                                movePiece(tempGame->Board[i][j], tempGame->Board[k][l], tempGame);
                                if(Check(player_count, tempGame) == 0){
                                    //DeleteGame(tempGame);
                                    return 0;
                                }
                                DeleteGame(tempGame);
                            }
                        }
                    }
                }
            }
        }
    }
    
    /* Check for Black */
    if(player_count%2 == 1){
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                if(game->Board[i][j]->Piece && game->Board[i][j]->Piece->Player == Black){
                    for(int k = 0; k < 8; k++){
                        for(int l = 0; l < 8; l++){
                            if(Is_Legal(game->Board[i][j], game->Board[k][l], game) > 0){
                                t_Game *tempGame = CopyGame(game);
                                movePiece(tempGame->Board[i][j], tempGame->Board[k][l], tempGame);
                                if(Check(player_count, tempGame) == 0){
                                    DeleteGame(tempGame);
                                    return 0;
                                }
                                DeleteGame(tempGame);
                            }
                        }
                    }
                }
            }
        }
    }

    if(Checkmate(player_count, game) > 0){
        return 0;
    }

    return 1;
}

/* Insufficien Materials check*/
/* Returns 1 if game is over (draw), 0 otherwise */
int insufficientMaterial(t_Game *game){

	/* Check if insufficient materials */
    int wBishop = 0, wKnight = 0, bBishop = 0, bKnight = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            
            /* Check if a piece exists at position */
            if(game->Board[i][j]->Piece == NULL){
                continue;
            }
            /* If Sufficient Materials exist */
            /* Game continues */
            if(game->Board[i][j]->Piece->Type == Pawn || game->Board[i][j]->Piece->Type == Rook || game->Board[i][j]->Piece->Type == Queen){
                return 0;
            }

            /* Count the number of Bishops each player has */
            else if(game->Board[i][j]->Piece->Type == Bishop){
                if(game->Board[i][j]->Piece->Player == White){
                    wBishop += 1;
                }
                else{
                    bBishop += 1;
                }
            }

            /* Count the number of Horses each player has */
            else if(game->Board[i][j]->Piece->Type == Knight){
                if(game->Board[i][j]->Piece->Player == White){
                    wKnight += 1;
                    }
                else{
                    bKnight += 1;
                }
            }
        }
    }
    
    /* If sufficient materials, game continues */
    if(wBishop == 2 || wKnight == 2 || bBishop == 2 || bKnight == 2 || (bBishop == 1 && bKnight == 1) || (wBishop == 1 && wKnight == 1)){
        return 0;
    }

    /* Game ends in a draw */
    return 1;
}

void Undo(t_GameList *gameList){
    assert(gameList->Curr);
    t_Game *temp = gameList->Curr;
    gameList->Curr = gameList->Curr->Prev;
    DeleteGame(temp);
}
