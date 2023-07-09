/**********************************************/
/* Project1: Chess                            */
/* Objects.c: Source file for game Objects    */
/* Author: King's Sacrifice                   */
/* Last Updated:                              */
/**********************************************/

#include <stdlib.h>
#include "Object.h"
#include "assert.h"

t_GameList *CreateGameList(void){

    t_GameList *list = NULL;
    list = (t_GameList *)malloc(sizeof(t_GameList));

    if(!list){
        return NULL;
    }
    list->Curr = NULL;

    return list;
}

void DeleteGameList(t_GameList *list){

    /* Check if the GameList exists */
    assert(list);
    assert(list->Curr);

    /* Delete all the Games in the GameList */
    t_Game *e = list->Curr;
    while(e){
        list->Curr = list->Curr->Prev;
        DeleteGame(e);
        e = list->Curr;
    }

    free(list);
}

/* Create Game */
t_Game *CreateGame(t_GameList *list, int flag){
    
    t_Game *game = NULL;
    game = (t_Game *)malloc(sizeof(t_Game));

    if(!game){
        return NULL;
    }

    game->List = list;
    game->Prev = NULL;
    game->Next = NULL;
    game->CFlag_wk = 0;
	game->CFlag_bk = 0;
	game->CFlag_wrr = 0;
	game->CFlag_wlr = 0;
	game->CFlag_brr = 0;
	game->CFlag_blr = 0;
	game->PFlag_w = 1;
	game->PFlag_b = 1;
	game->xw = 0;
	game->xb = 0;
	game->yw = 0;
	game->yb = 0;

    /* Initialize piece Player after USER selects Player1(White) and Player2(Black) in Main */

    int _rank = 8;
    int _x = 60;
    int _y = 60;
    
    /* Player choose white to start */
    if(flag == 0){
        for(int i = 0; i < 8; i++){
            _x = 60;
            for(int j = 0; j < 8; j++){
                /* Create position */
                game->Board[i][j] = (t_Position *)malloc(sizeof(t_Position));

                /* Set properties of positions */
                game->Board[i][j]->Rank = _rank;
                game->Board[i][j]->File = j + 65;
                game->Board[i][j]->x = _x;
                game->Board[i][j]->y = _y;
                _x+=65;

                if(i == 0 || i == 7){
                game->Board[i][j]->Piece = (t_Piece *)malloc(sizeof(t_Piece));
                game->Board[i][j]->Piece->Position = game->Board[i][j];
                    /* Set Player */
                    if(i == 0){
                        game->Board[i][j]->Piece->Player = Black;
                    }
                    else{
                        game->Board[i][j]->Piece->Player = White;
                    }
                    /* Set piece type */
                    if(j == 0 || j == 7){
                        game->Board[i][j]->Piece->Type = Rook;
                    }
                    else if(j == 1 || j == 6){
                        game->Board[i][j]->Piece->Type = Knight;
                    }
                    else if(j == 2 || j == 5){
                        game->Board[i][j]->Piece->Type = Bishop;
                    }
                    else if(j == 3){
                        game->Board[i][j]->Piece->Type = Queen;
                    }
                    else{
                        game->Board[i][j]->Piece->Type = King;
                    }
                }
                
                else if(i == 1 || i == 6){
                    /* Set pieces */
                    game->Board[i][j]->Piece = (t_Piece *)malloc(sizeof(t_Piece));
                    game->Board[i][j]->Piece->Position = game->Board[i][j];
                    /* Set Player */
                    if(i == 1){
                        game->Board[i][j]->Piece->Player = Black;
                    }
                    else{
                        game->Board[i][j]->Piece->Player = White;
                    }
                    game->Board[i][j]->Piece->Type = Pawn;
                }
                else{
                    game->Board[i][j]->Piece = NULL;
                }
            }
            _y+=65;
            _rank--;
        }
    }
    /* Player chooses black to start */
    else{
        _rank = 1;

        for(int i = 7; i > -1; i--){
        _x = 60;
        for(int j = 7; j > -1; j--){
            /* Create position */
            game->Board[i][j] = (t_Position *)malloc(sizeof(t_Position));

            /* Set properties of positions */
            game->Board[i][j]->Rank = _rank;
            game->Board[i][j]->File = j + 65;
            game->Board[i][j]->x = _x;
            game->Board[i][j]->y = _y;
            _x+=65;

            if(i == 0 || i == 7){
            game->Board[i][j]->Piece = (t_Piece *)malloc(sizeof(t_Piece));
            game->Board[i][j]->Piece->Position = game->Board[i][j];
                /* Set Player */
                if(i == 0){
                    game->Board[i][j]->Piece->Player = Black;
                }
                else{
                    game->Board[i][j]->Piece->Player = White;

                }
                /* Set piece type */
                if(j == 0 || j == 7){
                    game->Board[i][j]->Piece->Type = Rook;
                }
                else if(j == 1 || j == 6){
                    game->Board[i][j]->Piece->Type = Knight;
                }
                else if(j == 2 || j == 5){
                    game->Board[i][j]->Piece->Type = Bishop;
                }
                else if(j == 3){
                    game->Board[i][j]->Piece->Type = Queen;
                }
                else{
                    game->Board[i][j]->Piece->Type = King;
                }
            }
            
            else if(i == 1 || i == 6){
                /* Set pieces */
                game->Board[i][j]->Piece = (t_Piece *)malloc(sizeof(t_Piece));
                game->Board[i][j]->Piece->Position = game->Board[i][j];
                /* Set Player */
                if(i == 1){
                    game->Board[i][j]->Piece->Player = Black;
                }
                else{
                    game->Board[i][j]->Piece->Player = White;
                }
                game->Board[i][j]->Piece->Type = Pawn;
            }
            else{
                game->Board[i][j]->Piece = NULL;
            }
        }
        _y+=65;
        _rank++;
    }
    }
    list->Curr = game;
    return game;
}

/* Delete Game */
void DeleteGame(t_Game *game){

    /* Check if Game exists */
    assert(game);
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            DeletePosition(game->Board[i][j]);
        }
    }
    game->List = NULL;
    game->Next = NULL;
    free(game);
}

/* Delete Position */
void DeletePosition(t_Position *position){

    assert(position);

    if(position->Piece){
        free(position->Piece);
    }
    position->Piece = NULL;
    free(position);
}

/* Copy Game */
t_Game *CopyGame(t_Game *game){

    /* Check if game exists */
    assert(game);
    t_Game *newGame = CreateGame(game->List, 0);
    newGame->CFlag_wk = game->CFlag_wk;
	newGame->CFlag_bk = game->CFlag_bk;
	newGame->CFlag_wrr = game->CFlag_wrr;
	newGame->CFlag_wlr = game->CFlag_wlr;
	newGame->CFlag_brr = game->CFlag_brr;
	newGame->CFlag_blr = game->CFlag_blr;
	newGame->PFlag_w = game->PFlag_w;
	newGame->PFlag_b = game->PFlag_b;
	newGame->xw = game->xw;
	newGame->xb = game->xb;
	newGame->yw = game->yw;
	newGame->yb = game->yb;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            /* Create position */
            newGame->Board[i][j] = (t_Position *)malloc(sizeof(t_Position));

            /* Set properties of positions */
            newGame->Board[i][j]->Rank = game->Board[i][j]->Rank;
            newGame->Board[i][j]->File = game->Board[i][j]->File;
            newGame->Board[i][j]->x = game->Board[i][j]->x;
            newGame->Board[i][j]->y = game->Board[i][j]->y;

            /* Copy Pieces properties */
            newGame->Board[i][j]->Piece = NULL;
            if (game->Board[i][j]->Piece != NULL){
                newGame->Board[i][j]->Piece = (t_Piece *)malloc(sizeof(t_Piece));
                newGame->Board[i][j]->Piece->Player = game->Board[i][j]->Piece->Player;
                newGame->Board[i][j]->Piece->Type = game->Board[i][j]->Piece->Type;
                newGame->Board[i][j]->Piece->Position = newGame->Board[i][j];
            }
        }
    }
    newGame->Prev = game;
    game->Next = newGame;
    game->List->Curr = newGame;

    return newGame;
}

t_Position *getPosition(int x, int y, t_Game *game){
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if ((game -> Board[i][j] ->x <= x && x <= game -> Board[i][j]->x +65)
                && (game -> Board[i][j]->y <= y && y <= game -> Board[i][j]->y+65)){
                    return game -> Board[i][j];
                }
        }
    }
    return NULL;
}

t_Game *CurrentGame(t_GameList *gameList){
    return gameList->Curr;
}