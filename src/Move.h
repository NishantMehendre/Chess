/***************************************************/
/* Project1:                                       */
/* Move.h: header file for Move functions in game  */
/* Author: King's Sacrifice                        */ 
/* Last Updated:                                   */
/***************************************************/

#ifndef MOVE_H
#define MOVE_H

#include "Object.h"

/* Get Position1 */
/* Get Position2 */
/* Legal Move */
int Is_Legal(t_Position *position1, t_Position *position2, t_Game *game);

void movePiece(t_Position *position1, t_Position *position2, t_Game *game);

/* Check */
int Check(int player_count, t_Game *game);

/* Checkmate */
int Checkmate(int player_count, t_Game *game);

/* Stalemate */
int Stalemate(int player_count, t_Game *game);
int StalemateAI(int player_count, t_Game *game);
/* GameOver */
int insufficientMaterial(t_Game *game);

void Undo(t_GameList *gameList);

#endif


