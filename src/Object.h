/**********************************************/
/* Project1: Chess                            */
/* Objects.h: header file for Objects in game */
/* Author: King's Sacrifice                   */
/* Last Updated:                              */
/**********************************************/

#ifndef OBJECT_H
#define OBJECT_H

typedef struct GameList t_GameList;
typedef struct Game t_Game;
typedef struct Positions t_Position;
typedef struct Pieces t_Piece;
typedef struct wp_flag t_wp_flag;
typedef struct bp_flag t_bp_flag;

/* Player */
typedef enum{
	White,
	Black
} t_Player;

/* Type */
typedef enum{
	Pawn,
	Knight,
	Bishop,
	Rook,
	Queen,
	King
} t_Type;

/* Game List */
typedef struct GameList{
	t_Game *Curr;
};

/* Game Board */
struct Game{
	t_GameList *List;
	/* Contains pointers to each position */
	t_Position *Board[8][8];
	t_Game *Prev;
	t_Game *Next;
	int CFlag_wk;
	int CFlag_bk;
	int CFlag_wrr;
	int CFlag_wlr;
	int CFlag_brr;
	int CFlag_blr;
	int PFlag_w;
	int PFlag_b;
	int xw;
	int xb;
	int yw;
	int yb;
};

/* Position */
struct Positions{
	t_Piece *Piece;
	int Rank;
	char File;
	int x, y;
};

/* Game Piece */
struct Pieces{
	t_Position *Position;
	t_Player Player;
	t_Type Type;
};

struct wp_flag{
    int p_flagw;
    int x;
	int y;
};

struct bp_flag{
    int p_flagb;
    int x;
	int y;
};

/* Graveyard 
t_Pieces Graveyard[16];
*/

#endif /* OBJECT_H */

t_GameList *CreateGameList(void);

void DeleteGameList(t_GameList *list);

t_Game *CreateGame(t_GameList *list, int flag);

void DeleteGame(t_Game *game);

void DeletePosition(t_Position *position);

t_Game *CopyGame(t_Game *game);

t_Position *getPosition(int x, int y, t_Game *game);

t_Game *CurrentGame(t_GameList *gameList);