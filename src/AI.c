/***************************************************/
/* Project1:                                       */
/* AI.c: Source file for Chess AI                  */
/* Author: King's Sacrifice                        */
/* Last Updated:                                   */
/***************************************************/

#include "Object.h"
#include "Move.h"
#include <stdlib.h>
#include <stdio.h>
#include "assert.h"

int ComputerMove(t_Game *game, int player_Flag){
    /* AI Player BLACK*/
    if(player_Flag == 0){
        
        /* See if King is under check */
        if(Check(1, game) > 0){
            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                    if(game->Board[i][j]->Piece && game->Board[i][j]->Piece->Player == Black){
                        for(int k = 0; k < 8; k++){
                            for(int l = 0; l < 8; l++){
                                /* Check if move is legal */
                                if(Is_Legal(game->Board[i][j], game->Board[k][l], game) > 0){
                                    t_Game *tempGame = CopyGame(game);
                                    movePiece(tempGame->Board[i][j], tempGame->Board[k][l], tempGame);
                                    /* CHeck if King no more under attack */
                                    if(Check(1, tempGame) == 0 && Checkmate(1, tempGame) == 0){
                                        movePiece(game->Board[i][j], game->Board[k][l], game);
                                        if(game->Board[k][l] == Black && game->Board[k][l]->Rank == 1 && game->Board[k][l]->Piece->Type == Pawn){
					                    int pawnPromotion = 4;
					                    game->Board[k][l]->Piece->Type = pawnPromotion;
				                    }
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
        else{
            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                    if(game->Board[i][j]->Piece && game->Board[i][j]->Piece->Player == Black){
                        for(int k = 0; k < 8; k++){
                            for(int l = 0; l < 8; l++){
                                if(Is_Legal(game->Board[i][j], game->Board[k][l], game) > 0){
                                    t_Game *tempGame = CopyGame(game);
                                    movePiece(tempGame->Board[i][j], tempGame->Board[k][l], tempGame);
                                    /* CHeck if King no more under attack */
                                    if(Check(1, tempGame) == 0 && Checkmate(1, tempGame) == 0){
                                        movePiece(game->Board[i][j], game->Board[k][l], game);
                                        if(game->Board[k][l]->Rank == 1 && game->Board[k][l]->Piece->Type == Pawn){
                                            game->Board[k][l]->Piece->Type = Queen;
                                        }
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
    }
    /* White */
    else{
  /* See if King is under check */
        if(Check(1, game) > 0){
            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                    if(game->Board[i][j]->Piece && game->Board[i][j]->Piece->Player == Black){
                        for(int k = 0; k < 8; k++){
                            for(int l = 0; l < 8; l++){
                                /* Check if move is legal */
                                if(Is_Legal(game->Board[i][j], game->Board[k][l], game) > 0){
                                    t_Game *tempGame = CopyGame(game);
                                    movePiece(tempGame->Board[i][j], tempGame->Board[k][l], tempGame);
                                    /* CHeck if King no more under attack */
                                    if(Check(1, tempGame) == 0 && Checkmate(1, tempGame) == 0){
                                        movePiece(game->Board[i][j], game->Board[k][l], game);
                                        if(game->Board[k][l] == White && game->Board[k][l]->Rank == 8 && game->Board[k][l]->Piece->Type == Pawn){
					                    int pawnPromotion = 4;
					                    game->Board[k][l]->Piece->Type = pawnPromotion;
				                    }
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
        else{
            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                    if(game->Board[i][j]->Piece && game->Board[i][j]->Piece->Player == White){
                        for(int k = 0; k < 8; k++){
                            for(int l = 0; l < 8; l++){
                                if(Is_Legal(game->Board[i][j], game->Board[k][l], game) > 0){
                                    t_Game *tempGame = CopyGame(game);
                                    movePiece(tempGame->Board[i][j], tempGame->Board[k][l], tempGame);
                                    /* CHeck if King no more under attack */
                                    if(Check(1, tempGame) == 0 && Checkmate(1, tempGame) == 0){
                                        movePiece(game->Board[i][j], game->Board[k][l], game);
                                        if(game->Board[k][l]->Rank == 8 && game->Board[k][l]->Piece->Type == Pawn){
                                            game->Board[k][l]->Piece->Type = Queen;
                                        }
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
    }
}

