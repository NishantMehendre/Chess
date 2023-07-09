/***************************************************/
/* Project1:                                       */
/* Main.c: Source file for game program flow       */
/* Author: King's Sacrifice                        */
/* Last Updated:                                   */
/***************************************************/

#include <stdio.h>
#include "stdlib.h"
#include "SDL/SDL.h"
#include "Object.h"
#include "Move.h"
#include "AI.h"



//#define WAIT		// wait some time to show the image 
#define EVENTS		// process events and wait for window close

int main(int argc, char *argv[])
{
	/* User player */
	int player_Flag = 0;
	int modeCounter = 0;
	printf("Choose White(Enter 0) or Black(Enter 1): ");
	scanf("%d", &player_Flag);
	printf("Choose the mode (1: Player vs Player) (2: AI vs Player)");
	scanf("%d", &modeCounter);

	SDL_Surface *screen;	//This pointer will reference the backbuffer
	SDL_Surface *image;	//This pointer will reference our bitmap sprite
	SDL_Surface *temp;	//This pointer will temporarily reference our bitmap sprite
	SDL_Surface *wp;	//This pointer will reference out piece bmp
	SDL_Surface *wr;	//This pointer will reference out piece bmp
	SDL_Surface *wkn;	//This pointer will reference out piece bmp
	SDL_Surface *wb;	//This pointer will reference out piece bmp
	SDL_Surface *wq;	//This pointer will reference out piece bmp
	SDL_Surface *wk;	//This pointer will reference out piece bmp
	SDL_Surface *bp;	//This pointer will reference out piece bmp
	SDL_Surface *br;	//This pointer will reference out piece bmp
	SDL_Surface *bkn;	//This pointer will reference out piece bmp
	SDL_Surface *bb;	//This pointer will reference out piece bmp
	SDL_Surface *bq;	//This pointer will reference out piece bmp
	SDL_Surface *bk;	//This pointer will reference out piece bmp
	SDL_Surface *undo;  //This pointer will reference undo button bmp
	SDL_Surface *forfeit;
	SDL_Surface *draw;
	SDL_Surface *draw_confirm;

	SDL_Rect src, dest;
	SDL_Rect wp1_dest/*, wp2_dest, wp3_dest, wp4_dest, wp5_dest, wp6_dest , wp7_dest , wp8_dest*/; 	//all rectangles for white pawns
	SDL_Rect wr1_dest, /*wr2_dest,*/ wkn1_dest, /*wkn2_dest,*/ wb1_dest, /*wb2_dest,*/ wq_dest, wk_dest;		//These rectangles will describe the destination regions of our white pieces
	SDL_Rect bp1_dest/*, bp2_dest, bp3_dest, bp4_dest, bp5_dest, bp6_dest , bp7_dest , bp8_dest*/; 	//all rectangles for black pawns
	SDL_Rect br1_dest, /*br2_dest,*/ bkn1_dest, /*bkn2_dest,*/ bb1_dest, /*bb2_dest,*/ bq_dest, bk_dest;	//These rectangles will describe the destination regions of our black pieces
	SDL_Rect undo_dest; //These rectangles will describe the destination regions of our black pieces
	SDL_Rect forfeit_dest;
	SDL_Rect draw_dest;
	SDL_Rect draw_confirm_dest;
	//int x;
#ifdef EVENTS
	SDL_Event event;	/* Event structure */
	int Running;
#endif
	
	//Opens file for game log
	FILE *Log;
	Log  = fopen ("ChessLog.txt", "w");
	

	//prints to file
	fprintf(Log, "*****CHESS LOG*****\n");



	//We must first initialize the SDL video component, and check for success
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		return 1;
	}
	
	//When this program exits, SDL_Quit must be called
	atexit(SDL_Quit);
	
	//Set the video mode to a window of size 320 by 240 pixels with 32 bits per pixel
	screen = SDL_SetVideoMode(740, 740, 32, SDL_ANYFORMAT /*SDL_DOUBLEBUF | SDL_FULLSCREEN*/);
	if (screen == NULL) {
		printf("Unable to set video mode: %s\n", SDL_GetError());
		return 1;
	}

	/*************************************************
	Loading all images
	*************************************************/

	//Load the bitmap into a temporary surface, and check for success
	if(player_Flag == 0){
		temp = SDL_LoadBMP("Board.bmp");
	}
	else{
		temp = SDL_LoadBMP("Board_rotated.bmp");
	}
	if (temp == NULL) {
		printf("Unable to load bitmap board: %s\n", SDL_GetError());
		return 1;
	}
	
	wp = SDL_LoadBMP("w_pawn.bmp");
	if (wp == NULL) {
		printf("Unable to load bitmap wp: %s\n", SDL_GetError());
		return 1;
	}
	wr = SDL_LoadBMP("w_rook.bmp");
	if (wr == NULL) {
		printf("Unable to load bitmap wr: %s\n", SDL_GetError());
		return 1;
	}

	wkn = SDL_LoadBMP("w_knight.bmp");
	if (wkn == NULL) {
		printf("Unable to load bitmap wkn: %s\n", SDL_GetError());
		return 1;
	}

	wb = SDL_LoadBMP("w_bishop.bmp");
	if (wb == NULL) {
		printf("Unable to load bitmap wb: %s\n", SDL_GetError());
		return 1;
	}

	wq = SDL_LoadBMP("w_queen.bmp");
	if (wq == NULL) {
		printf("Unable to load bitmap wq: %s\n", SDL_GetError());
		return 1;
	}

	wk = SDL_LoadBMP("w_king.bmp");
	if (wk == NULL) {
		printf("Unable to load bitmap wk: %s\n", SDL_GetError());
		return 1;
	}

	bp = SDL_LoadBMP("b_pawn.bmp");
	if (bp == NULL) {
		printf("Unable to load bitmap bp: %s\n", SDL_GetError());
		return 1;
	}

	br = SDL_LoadBMP("b_rook.bmp");
	if (br == NULL) {
		printf("Unable to load bitmap br: %s\n", SDL_GetError());
		return 1;
	}

	bkn = SDL_LoadBMP("b_knight.bmp");
	if (bkn == NULL) {
		printf("Unable to load bitmap bkn: %s\n", SDL_GetError());
		return 1;
	}

	bb = SDL_LoadBMP("b_bishop.bmp");
	if (bb == NULL) {
		printf("Unable to load bitmap bb: %s\n", SDL_GetError());
		return 1;
	}

	bq = SDL_LoadBMP("b_queen.bmp");
	if (bq == NULL) {
		printf("Unable to load bitmap bq: %s\n", SDL_GetError());
		return 1;
	}

	bk = SDL_LoadBMP("b_king.bmp");
	if (bq == NULL) {
		printf("Unable to load bitmap bk: %s\n", SDL_GetError());
		return 1;
	}

	undo = SDL_LoadBMP("button_undo.bmp");
	if (undo == NULL){
		printf("Unable to load bitmap undo: %s\n", SDL_GetError());
		return 1;
	}
	
	forfeit = SDL_LoadBMP("button_forfeit.bmp");
	if (forfeit == NULL){
		printf("Unable to load bitmap forfeit: %s\n", SDL_GetError());
		return 1;
	}

	draw = SDL_LoadBMP("button_draw.bmp");
	if (draw == NULL){
		printf("Unable to load bitmap draw: %s\n", SDL_GetError());
		return 1;
	}

	draw_confirm = SDL_LoadBMP("propose_draw.bmp");
	if (draw_confirm == NULL){
		printf("Unable to load draw confirmation: %s\n", SDL_GetError());
		return 1;
	}

	

		
	/****************************
	Colorkey all pieces
	*****************************/

	//Color key piece image	//piece->format in map rgb
    SDL_SetColorKey( wp, SDL_SRCCOLORKEY, SDL_MapRGB( wp->format, 0xFF, 0x00, 0xFF ) );
	SDL_SetColorKey( wr, SDL_SRCCOLORKEY, SDL_MapRGB( wr->format, 0xFF, 0x00, 0xFF ) );
	SDL_SetColorKey( wkn, SDL_SRCCOLORKEY, SDL_MapRGB( wkn->format, 0xFF, 0x00, 0xFF ) );
	SDL_SetColorKey( wb, SDL_SRCCOLORKEY, SDL_MapRGB( wb->format, 0xFF, 0x00, 0xFF ) );
	SDL_SetColorKey( wq, SDL_SRCCOLORKEY, SDL_MapRGB( wq->format, 0xFF, 0x00, 0xFF ) );
	SDL_SetColorKey( wk, SDL_SRCCOLORKEY, SDL_MapRGB( wk->format, 0xFF, 0x00, 0xFF ) );
	SDL_SetColorKey( bp, SDL_SRCCOLORKEY, SDL_MapRGB( bp->format, 0xFF, 0x00, 0xFF ) );
	SDL_SetColorKey( br, SDL_SRCCOLORKEY, SDL_MapRGB( br->format, 0xFF, 0x00, 0xFF ) );
	SDL_SetColorKey( bkn, SDL_SRCCOLORKEY, SDL_MapRGB( bkn->format, 0xFF, 0x00, 0xFF ) );
	SDL_SetColorKey( bb, SDL_SRCCOLORKEY, SDL_MapRGB( bb->format, 0xFF, 0x00, 0xFF ) );
	SDL_SetColorKey( bq, SDL_SRCCOLORKEY, SDL_MapRGB( bq->format, 0xFF, 0x00, 0xFF ) );
	SDL_SetColorKey( bk, SDL_SRCCOLORKEY, SDL_MapRGB( bk->format, 0xFF, 0x00, 0xFF ) );
	SDL_SetColorKey( temp, SDL_SRCCOLORKEY, SDL_MapRGB( temp->format, 0xFF, 0x00, 0xFF ) );


	//Convert the surface to the appropriate display format
	image = SDL_DisplayFormat(temp);
	
	//Release the temporary surface
	SDL_FreeSurface(temp);
	/***********************************************
	Construct rectangles for all image surfaces
	***********************************************/
	//Construct the source rectangle for our chess board blit
	src.x = 0;
	src.y = 0;
	src.w = image->w;	//Use image->w to display the entire width of the image
	src.h = image->h;	//Use image->h to display the entire height of the image
	
	//Construct the destination rectangle for our chess board blit
	dest.x = 0;		//Display the image at the (X,Y) coordinates (0,0)
	dest.y = 0;
	dest.w = image->w;	//Ensure the destination is large enough for the image's entire width/height
	dest.h = image->h;

	undo_dest.x = 0;
	undo_dest.y = 680;
	forfeit_dest.x = 250;
	forfeit_dest.y = 680;
	draw_dest.x = 500;
	draw_dest.y = 680;
	draw_confirm_dest.x = 120;
	draw_confirm_dest.y = 200;
	//Update the window at the modified region
	SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h); 
	
	
	
#ifdef WAIT
	//Wait for 5s so we can see the image
	SDL_Delay(5000);
#endif

#ifdef EVENTS
	//Process events
	Running = 1;
	printf("Running!\n");
	
	/*Create game list*/
	t_GameList *game_list = CreateGameList();

	/*Create game*/
	t_Game *new_game = CreateGame(game_list, player_Flag);
	SDL_BlitSurface(image, &src, screen, &dest);
	SDL_BlitSurface(undo, &src, screen, &undo_dest);
	SDL_BlitSurface(forfeit, &src, screen, &forfeit_dest);
	SDL_BlitSurface(draw, &src, screen, &draw_dest);
	
	//Update the window at the modified region
	SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
	
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
				/*blit the images*/ 
			if(new_game->Board[i][j]->Piece != NULL && new_game->Board[i][j]->Piece->Player == White){
				if(new_game->Board[i][j]->Piece->Type == Pawn){
					wp1_dest.x = new_game->Board[i][j]->x;
					wp1_dest.y = new_game->Board[i][j]->y;
					SDL_BlitSurface(wp, NULL, screen, &wp1_dest);
				}
				else if(new_game->Board[i][j]->Piece->Type == Knight){
					wkn1_dest.x = new_game->Board[i][j]->x;
					wkn1_dest.y = new_game->Board[i][j]->y;
					SDL_BlitSurface(wkn, NULL, screen, &wkn1_dest);
				}
				else if(new_game->Board[i][j]->Piece->Type == Bishop){
					wb1_dest.x = new_game->Board[i][j]->x;
					wb1_dest.y = new_game->Board[i][j]->y;
					SDL_BlitSurface(wb, NULL, screen, &wb1_dest);
				}
				else if(new_game->Board[i][j]->Piece->Type == Rook){
					wr1_dest.x = new_game->Board[i][j]->x;
					wr1_dest.y = new_game->Board[i][j]->y;
					SDL_BlitSurface(wr, NULL, screen, &wr1_dest);
				}
				else if(new_game->Board[i][j]->Piece->Type == Queen){
					wq_dest.x = new_game->Board[i][j]->x;
					wq_dest.y = new_game->Board[i][j]->y;
					SDL_BlitSurface(wq, NULL, screen, &wq_dest);
				}
				else if(new_game->Board[i][j]->Piece->Type == King){
					wk_dest.x = new_game->Board[i][j]->x;
					wk_dest.y = new_game->Board[i][j]->y;
					SDL_BlitSurface(wk, NULL, screen, &wk_dest);
				}	
			}
			if(new_game->Board[i][j]->Piece != NULL && new_game->Board[i][j]->Piece->Player == Black){
				if(new_game->Board[i][j]->Piece->Type == Pawn){
					bp1_dest.x = new_game->Board[i][j]->x;
					bp1_dest.y = new_game->Board[i][j]->y;
					SDL_BlitSurface(bp, NULL, screen, &bp1_dest);
				}
				else if(new_game->Board[i][j]->Piece->Type == Knight){
					bkn1_dest.x = new_game->Board[i][j]->x;
					bkn1_dest.y = new_game->Board[i][j]->y;
					SDL_BlitSurface(bkn, NULL, screen, &bkn1_dest);
				}
				else if(new_game->Board[i][j]->Piece->Type == Bishop){
					bb1_dest.x = new_game->Board[i][j]->x;
					bb1_dest.y = new_game->Board[i][j]->y;
					SDL_BlitSurface(bb, NULL, screen, &bb1_dest);
				}
				else if(new_game->Board[i][j]->Piece->Type == Rook){
					br1_dest.x = new_game->Board[i][j]->x;
					br1_dest.y = new_game->Board[i][j]->y;
					SDL_BlitSurface(br, NULL, screen, &br1_dest);
				}
				else if(new_game->Board[i][j]->Piece->Type == Queen){
					bq_dest.x = new_game->Board[i][j]->x;
					bq_dest.y = new_game->Board[i][j]->y;
					SDL_BlitSurface(bq, NULL, screen, &bq_dest);
				}
				else if(new_game->Board[i][j]->Piece->Type == King){
					bk_dest.x = new_game->Board[i][j]->x;
					bk_dest.y = new_game->Board[i][j]->y;
					SDL_BlitSurface(bk, NULL, screen, &bk_dest);
				}	
			}

		}
	}
	SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
		
	int player_count = 0;
	int draw_flag = 0;

	/* Castling */
	/*int castling_flagbk = 0;
	int checkerbk = 0;
	int castling_flagwk = 0;
	int checkerwk = 0;
	int castling_flagbrl = 0;
	int checkerbrl = 0;
	int castling_flagwrl = 0;
	int checkerwrl = 0;
	int castling_flagwrr = 0;
	int checkerwrr = 0;
	int castling_flagbrr = 0;
	int checkerbrr = 0;*/

	
	
	if(modeCounter == 1){
		while(Running && SDL_WaitEvent(&event))
		{	
			int x1, y1, x2, y2;
			t_Position *position1, *position2;
			/*printf("Received event.type = %d\n", event.type);*/
			switch(event.type)
			{ /* Process the appropriate event type */
				case SDL_KEYDOWN:  /* Handle a KEYDOWN event */
				{	//printf("Oh! Key pressed!\n");
					break;
				}
				case SDL_MOUSEBUTTONDOWN:
				{	
					if(player_count %2 == 0){
						printf("WHITE'S TURN\n");
						//prints to file Log
						fprintf(Log, "WHITE'S TURN\n");

					}
					else{
						printf("BLACK'S TURN\n");
						printf("BLACK'S TURN\n");
						fprintf(Log, "BLACK'S TURN\n");

					}

					//printf("Oh! Mouse button %d pressed!\n",event.button.button);
					x1 = event.button.x;
					y1 = event.button.y;

					if (x1 > 0 && x1 < 180 && y1 > 680 && y1 < 730){
						//printf("Undo button pressed\n");
						break;
					}

					else if (x1 > 250 && x1 < 450 && y1 > 680 && y1 < 730){
						//printf("Forfeit button pressed\n");
						break;
					}

					else if (x1 > 500 && x1 < 700 && y1 > 680 && y2 < 730){
						//printf("Draw button pressed\n");
						break;
					}

					else{ 
					position1 = getPosition(x1, y1, new_game);
					break;
					}	
					
					
				}
				default: /* ignore any other events */
				{	
					break;
				}
			} /* hctiws */
			switch(event.type)
			{ /* Process the appropriate event type */
				case SDL_KEYDOWN:  /* Handle a KEYDOWN event */
				{	//printf("Oh! Key pressed!\n");
					break;
				}
				case SDL_MOUSEBUTTONUP:
				{	
					x2 = event.button.x;
					y2 = event.button.y;

					if (position1 == NULL){
						printf("Position not on board\n");
						break;
					}
					if (x1 > 0 && x1 < 180 && y1 > 680 && y1 < 730 && x1 == x2 && y1 == y2){
						printf("Undo button pressed\n");
						/* Undo only when ur turn */
						Undo(game_list);
						Undo(game_list);
						Undo(game_list);

						if(CurrentGame(game_list)){
							new_game = CurrentGame(game_list);
							t_Game *tempGame = NULL;
							tempGame = CopyGame(new_game);
							new_game = tempGame;
						}
						else{
							new_game = CreateGame(game_list, player_Flag);
						}
						SDL_BlitSurface(image, &src, screen, &dest);
						SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
						for(int i = 0; i < 8; i++){
							for(int j = 0; j < 8; j++){
								/*blit the images*/ 
								if(new_game->Board[i][j]->Piece != NULL && new_game->Board[i][j]->Piece->Player == White){
									if(new_game->Board[i][j]->Piece->Type == Pawn){
										wp1_dest.x = new_game->Board[i][j]->x;
										wp1_dest.y = new_game->Board[i][j]->y;
										SDL_BlitSurface(wp, NULL, screen, &wp1_dest);
									}
									else if(new_game->Board[i][j]->Piece->Type == Knight){
										wkn1_dest.x = new_game->Board[i][j]->x;
										wkn1_dest.y = new_game->Board[i][j]->y;
										SDL_BlitSurface(wkn, NULL, screen, &wkn1_dest);
									}
									else if(new_game->Board[i][j]->Piece->Type == Bishop){
										wb1_dest.x = new_game->Board[i][j]->x;
										wb1_dest.y = new_game->Board[i][j]->y;
										SDL_BlitSurface(wb, NULL, screen, &wb1_dest);
									}
									else if(new_game->Board[i][j]->Piece->Type == Rook){
										wr1_dest.x = new_game->Board[i][j]->x;
										wr1_dest.y = new_game->Board[i][j]->y;
										SDL_BlitSurface(wr, NULL, screen, &wr1_dest);
									}
									else if(new_game->Board[i][j]->Piece->Type == Queen){
										wq_dest.x = new_game->Board[i][j]->x;
										wq_dest.y = new_game->Board[i][j]->y;
										SDL_BlitSurface(wq, NULL, screen, &wq_dest);
									}
									else if(new_game->Board[i][j]->Piece->Type == King){
										wk_dest.x = new_game->Board[i][j]->x;
										wk_dest.y = new_game->Board[i][j]->y;
										SDL_BlitSurface(wk, NULL, screen, &wk_dest);
									}	
								}
								if(new_game->Board[i][j]->Piece != NULL && new_game->Board[i][j]->Piece->Player == Black){
									if(new_game->Board[i][j]->Piece->Type == Pawn){
										bp1_dest.x = new_game->Board[i][j]->x;
										bp1_dest.y = new_game->Board[i][j]->y;
										SDL_BlitSurface(bp, NULL, screen, &bp1_dest);
									}
									else if(new_game->Board[i][j]->Piece->Type == Knight){
										bkn1_dest.x = new_game->Board[i][j]->x;
										bkn1_dest.y = new_game->Board[i][j]->y;
										SDL_BlitSurface(bkn, NULL, screen, &bkn1_dest);
									}
									else if(new_game->Board[i][j]->Piece->Type == Bishop){
										bb1_dest.x = new_game->Board[i][j]->x;
										bb1_dest.y = new_game->Board[i][j]->y;
										SDL_BlitSurface(bb, NULL, screen, &bb1_dest);
									}
									else if(new_game->Board[i][j]->Piece->Type == Rook){
										br1_dest.x = new_game->Board[i][j]->x;
										br1_dest.y = new_game->Board[i][j]->y;
										SDL_BlitSurface(br, NULL, screen, &br1_dest);
									}
									else if(new_game->Board[i][j]->Piece->Type == Queen){
										bq_dest.x = new_game->Board[i][j]->x;
										bq_dest.y = new_game->Board[i][j]->y;
										SDL_BlitSurface(bq, NULL, screen, &bq_dest);
									}
									else if(new_game->Board[i][j]->Piece->Type == King){
										bk_dest.x = new_game->Board[i][j]->x;
										bk_dest.y = new_game->Board[i][j]->y;
										SDL_BlitSurface(bk, NULL, screen, &bk_dest);
									}	
								}

							}
						}
						SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
						break;
					} 

					if (x1 > 250 && x1 < 450 && y1 > 680 && y1 < 730 && x1 == x2 && y1 == y2){
						printf("Forfeit button pressed\n");
						if (player_count % 2 == 0)
							printf("White forfeits. Black wins!\n");
						else
							printf("Black forfeits. White wins!\n");
							
							Running = 0;
							break;
					}

					if ((draw_flag == 0 && x1 > 500 && x1 < 700 && y1 > 680 && y1 < 730 && x1 == x2 && y1 == y2) || draw_flag == 1){
						if (draw_flag == 0){
							SDL_BlitSurface(draw_confirm, NULL, screen, &draw_confirm_dest);
							SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
							draw_flag = 1;
							break;
						}
						else{
							if (x1 > 500 && x1 < 700 && y1 > 680 && y1 < 730 && x1 == x2 && y1 == y2){
								printf("It's a draw!\n");
								
								Running = 0;
								draw_flag = 0;
								break;
							}
							else{
								SDL_BlitSurface(image, &src, screen, &dest);
								SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
								for(int i = 0; i < 8; i++){
									for(int j = 0; j < 8; j++){
										/*blit the images*/ 
										if(new_game->Board[i][j]->Piece != NULL && new_game->Board[i][j]->Piece->Player == White){
											if(new_game->Board[i][j]->Piece->Type == Pawn){
												wp1_dest.x = new_game->Board[i][j]->x;
												wp1_dest.y = new_game->Board[i][j]->y;
												SDL_BlitSurface(wp, NULL, screen, &wp1_dest);
											}
											else if(new_game->Board[i][j]->Piece->Type == Knight){
												wkn1_dest.x = new_game->Board[i][j]->x;
												wkn1_dest.y = new_game->Board[i][j]->y;
												SDL_BlitSurface(wkn, NULL, screen, &wkn1_dest);
											}
											else if(new_game->Board[i][j]->Piece->Type == Bishop){
												wb1_dest.x = new_game->Board[i][j]->x;
												wb1_dest.y = new_game->Board[i][j]->y;
												SDL_BlitSurface(wb, NULL, screen, &wb1_dest);
											}
											else if(new_game->Board[i][j]->Piece->Type == Rook){
												wr1_dest.x = new_game->Board[i][j]->x;
												wr1_dest.y = new_game->Board[i][j]->y;
												SDL_BlitSurface(wr, NULL, screen, &wr1_dest);
											}
											else if(new_game->Board[i][j]->Piece->Type == Queen){
												wq_dest.x = new_game->Board[i][j]->x;
												wq_dest.y = new_game->Board[i][j]->y;
												SDL_BlitSurface(wq, NULL, screen, &wq_dest);
											}
											else if(new_game->Board[i][j]->Piece->Type == King){
												wk_dest.x = new_game->Board[i][j]->x;
												wk_dest.y = new_game->Board[i][j]->y;
												SDL_BlitSurface(wk, NULL, screen, &wk_dest);
											}	
										}
										if(new_game->Board[i][j]->Piece != NULL && new_game->Board[i][j]->Piece->Player == Black){
											if(new_game->Board[i][j]->Piece->Type == Pawn){
												bp1_dest.x = new_game->Board[i][j]->x;
												bp1_dest.y = new_game->Board[i][j]->y;
												SDL_BlitSurface(bp, NULL, screen, &bp1_dest);
											}
											else if(new_game->Board[i][j]->Piece->Type == Knight){
												bkn1_dest.x = new_game->Board[i][j]->x;
												bkn1_dest.y = new_game->Board[i][j]->y;
												SDL_BlitSurface(bkn, NULL, screen, &bkn1_dest);
											}
											else if(new_game->Board[i][j]->Piece->Type == Bishop){
												bb1_dest.x = new_game->Board[i][j]->x;
												bb1_dest.y = new_game->Board[i][j]->y;
												SDL_BlitSurface(bb, NULL, screen, &bb1_dest);
											}
											else if(new_game->Board[i][j]->Piece->Type == Rook){
												br1_dest.x = new_game->Board[i][j]->x;
												br1_dest.y = new_game->Board[i][j]->y;
												SDL_BlitSurface(br, NULL, screen, &br1_dest);
											}
											else if(new_game->Board[i][j]->Piece->Type == Queen){
												bq_dest.x = new_game->Board[i][j]->x;
												bq_dest.y = new_game->Board[i][j]->y;
												SDL_BlitSurface(bq, NULL, screen, &bq_dest);
											}
											else if(new_game->Board[i][j]->Piece->Type == King){
												bk_dest.x = new_game->Board[i][j]->x;
												bk_dest.y = new_game->Board[i][j]->y;
												SDL_BlitSurface(bk, NULL, screen, &bk_dest);
											}	
										}

									}
								}
								SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
								draw_flag = 0;
								break;
							}	
						}
					}

					if(position1->Piece == NULL){
						printf("Empty position.\n");
					break;
					}
					else if((player_count%2 == 0 && position1 -> Piece -> Player == Black) || (player_count%2 != 0 && position1 -> Piece -> Player == White)){
						printf("Not your move!\n");
					break;
					}
					else{
					//printf("Oh! Mouse button %d pressed!\n",event.button.button);
					position2 = getPosition(x2, y2, new_game);	
					}

				if(Is_Legal(position1, position2, new_game) > 0){
					
					/*if(position1->Piece->Type == King && position1->Piece->Player==Black){
						checkerbk+=1;
					}
					else if((int)(position1->File)-65 == 7 && position1->Piece->Type == Rook && position1->Piece->Player == Black){
						checkerbrr+=1;
					}
					else if(position1->Piece->Type == King && position1->Piece->Player==White){
						checkerwk+=1;
					}
					else if((int)(position1->File)-65 == 7 && position1->Piece->Type == Rook && position1->Piece->Player == White){
						checkerwrr+=1;
					}
					else if((int)(position1->File)-65 == 0 && position1->Piece->Type == Rook && position1->Piece->Player == Black){
						checkerbrl+=1;
					}
					else if((int)(position1->File)-65 == 0 && position1->Piece->Type == Rook && position1->Piece->Player == White){
						checkerwrl+=1;
					}*/

					movePiece(position1, position2, new_game);
					if(Check(player_count, new_game) > 0){
						
						new_game = NULL;
						Undo(game_list);
						new_game = CurrentGame(game_list);
						printf("Illegal Move! King under attack!\n");

						t_Game *tempGame = NULL;
						tempGame = CopyGame(new_game);
						new_game = tempGame;
						break;
					}
					printf("legal move\n");
					printf("From %c%d\n",
						position1->File, position1->Rank);
					fprintf(Log, "From %c%d\n",
						position1->File, position1->Rank);
					printf("To %c%d\n",
						position2->File, position2->Rank); 
					fprintf(Log, "To %c%d\n",
						position2->File, position2->Rank);
					if(position2->Piece->Player == Black && position2->Rank == 1 && position2->Piece->Type == Pawn){
						int pawnPromotion = 4;
						position2->Piece->Type = pawnPromotion;
					}
					else if(position2->Piece->Player == White && position2->Rank == 8 && position2->Piece->Type == Pawn){
						int pawnPromotion = 4;
						position2->Piece->Type = pawnPromotion;
					}

					/*if(checkerbk > 0){
						castling_flagbk+=1;
					}
					else if (checkerbrr>0){
						castling_flagbrr+=1;
					}
					else if (checkerwrr>0){
						castling_flagwrr+=1;
					}
					else if (checkerwk>0){
						castling_flagwk+=1;
					}
					else if (checkerwrl>0){
						castling_flagwrl+=1;
					}
					else if (checkerbrl>0){
						castling_flagbrl+=1;
					}*/
					
					SDL_BlitSurface(image, &src, screen, &dest);
					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
					for(int i = 0; i < 8; i++){
						for(int j = 0; j < 8; j++){
							/*blit the images*/ 
							if(new_game->Board[i][j]->Piece != NULL && new_game->Board[i][j]->Piece->Player == White){
								if(new_game->Board[i][j]->Piece->Type == Pawn){
									wp1_dest.x = new_game->Board[i][j]->x;
									wp1_dest.y = new_game->Board[i][j]->y;
									SDL_BlitSurface(wp, NULL, screen, &wp1_dest);
								}
								else if(new_game->Board[i][j]->Piece->Type == Knight){
									wkn1_dest.x = new_game->Board[i][j]->x;
									wkn1_dest.y = new_game->Board[i][j]->y;
									SDL_BlitSurface(wkn, NULL, screen, &wkn1_dest);
								}
								else if(new_game->Board[i][j]->Piece->Type == Bishop){
									wb1_dest.x = new_game->Board[i][j]->x;
									wb1_dest.y = new_game->Board[i][j]->y;
									SDL_BlitSurface(wb, NULL, screen, &wb1_dest);
								}
								else if(new_game->Board[i][j]->Piece->Type == Rook){
									wr1_dest.x = new_game->Board[i][j]->x;
									wr1_dest.y = new_game->Board[i][j]->y;
									SDL_BlitSurface(wr, NULL, screen, &wr1_dest);
								}
								else if(new_game->Board[i][j]->Piece->Type == Queen){
									wq_dest.x = new_game->Board[i][j]->x;
									wq_dest.y = new_game->Board[i][j]->y;
									SDL_BlitSurface(wq, NULL, screen, &wq_dest);
								}
								else if(new_game->Board[i][j]->Piece->Type == King){
									wk_dest.x = new_game->Board[i][j]->x;
									wk_dest.y = new_game->Board[i][j]->y;
									SDL_BlitSurface(wk, NULL, screen, &wk_dest);
								}	
							}
							if(new_game->Board[i][j]->Piece != NULL && new_game->Board[i][j]->Piece->Player == Black){
								if(new_game->Board[i][j]->Piece->Type == Pawn){
									bp1_dest.x = new_game->Board[i][j]->x;
									bp1_dest.y = new_game->Board[i][j]->y;
									SDL_BlitSurface(bp, NULL, screen, &bp1_dest);
								}
								else if(new_game->Board[i][j]->Piece->Type == Knight){
									bkn1_dest.x = new_game->Board[i][j]->x;
									bkn1_dest.y = new_game->Board[i][j]->y;
									SDL_BlitSurface(bkn, NULL, screen, &bkn1_dest);
								}
								else if(new_game->Board[i][j]->Piece->Type == Bishop){
									bb1_dest.x = new_game->Board[i][j]->x;
									bb1_dest.y = new_game->Board[i][j]->y;
									SDL_BlitSurface(bb, NULL, screen, &bb1_dest);
								}
								else if(new_game->Board[i][j]->Piece->Type == Rook){
									br1_dest.x = new_game->Board[i][j]->x;
									br1_dest.y = new_game->Board[i][j]->y;
									SDL_BlitSurface(br, NULL, screen, &br1_dest);
								}
								else if(new_game->Board[i][j]->Piece->Type == Queen){
									bq_dest.x = new_game->Board[i][j]->x;
									bq_dest.y = new_game->Board[i][j]->y;
									SDL_BlitSurface(bq, NULL, screen, &bq_dest);
								}
								else if(new_game->Board[i][j]->Piece->Type == King){
									bk_dest.x = new_game->Board[i][j]->x;
									bk_dest.y = new_game->Board[i][j]->y;
									SDL_BlitSurface(bk, NULL, screen, &bk_dest);
								}	
							}

						}
					}
					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
					player_count+=1;
				/* Insufficient materials: Draw */
				if(insufficientMaterial(new_game) == 1){
					printf("It is a draw!\n");
					break;
					Running = 0;
				}
				else if(Checkmate(player_count, new_game) == 1){
					if(player_count%2 == 0)
						printf("Checkmate Black wins!\n");
					else
						printf("Checkmate White wins\n");
					break;
					Running = 0;		
				}
				else if(Stalemate(player_count, new_game) == 1){
					printf("Stalemate It's a draw!\n");
					break;
					Running = 0;		
				}
				else{
					

					t_Game *tempGame = NULL;
					tempGame = CopyGame(new_game);
					new_game = tempGame;
				}
				}

						break;
				}
				case SDL_QUIT:
				{	
					Running = 0;
					break;
				}
				default: /* ignore any other events */
				{	/*printf("Oops, unknown event!\n");*/
					break;
				}
			}
	/* hctiws */
		} /* elihw */
	}

	if (modeCounter == 2){
		while(Running && SDL_WaitEvent(&event))
	{	
		int x1, y1, x2, y2;
		t_Position *position1, *position2;
		/*printf("Received event.type = %d\n", event.type);*/
		if (player_count%2 == player_Flag){
		switch(event.type)
		{ /* Process the appropriate event type */
			case SDL_KEYDOWN:  /* Handle a KEYDOWN event */
			{	//printf("Oh! Key pressed!\n");
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{	
				if(player_count %2 == 0){
					printf("WHITE'S TURN\n");
				}
				else{
					printf("BLACK'S TURN\n");
				}

				//printf("Oh! Mouse button %d pressed!\n",event.button.button);
				x1 = event.button.x;
				y1 = event.button.y;

				if (x1 > 0 && x1 < 180 && y1 > 680 && y1 < 730){
					//printf("Undo button pressed\n");
					break;
				}

				else if (x1 > 250 && x1 < 450 && y1 > 680 && y1 < 730){
					//printf("Forfeit button pressed\n");
					break;
				}

				else if (x1 > 500 && x1 < 700 && y1 > 680 && y2 < 730){
					//printf("Draw button pressed\n");
					break;
				}

				else{ 
				position1 = getPosition(x1, y1, new_game);
				break;
				}	
				
				
			}
			default: /* ignore any other events */
			{	
				break;
			}
		} /* hctiws */
		switch(event.type)
		{ /* Process the appropriate event type */
			case SDL_KEYDOWN:  /* Handle a KEYDOWN event */
			{	//printf("Oh! Key pressed!\n");
				break;
			}
			case SDL_MOUSEBUTTONUP:
			{	
				x2 = event.button.x;
				y2 = event.button.y;

				if (position1 == NULL){
					printf("Position not on board\n");
					break;
				}
				if (x1 > 0 && x1 < 180 && y1 > 680 && y1 < 730 && x1 == x2 && y1 == y2){
					printf("Undo button pressed\n");
					/* Undo only when ur turn */
					Undo(game_list);
					Undo(game_list);
					Undo(game_list);

					if(CurrentGame(game_list)){
						new_game = CurrentGame(game_list);
						t_Game *tempGame = NULL;
						tempGame = CopyGame(new_game);
						new_game = tempGame;
					}
					else{
						new_game = CreateGame(game_list, player_Flag);
					}
					SDL_BlitSurface(image, &src, screen, &dest);
					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
					for(int i = 0; i < 8; i++){
						for(int j = 0; j < 8; j++){
							/*blit the images*/ 
							if(new_game->Board[i][j]->Piece != NULL && new_game->Board[i][j]->Piece->Player == White){
								if(new_game->Board[i][j]->Piece->Type == Pawn){
									wp1_dest.x = new_game->Board[i][j]->x;
									wp1_dest.y = new_game->Board[i][j]->y;
									SDL_BlitSurface(wp, NULL, screen, &wp1_dest);
								}
								else if(new_game->Board[i][j]->Piece->Type == Knight){
									wkn1_dest.x = new_game->Board[i][j]->x;
									wkn1_dest.y = new_game->Board[i][j]->y;
									SDL_BlitSurface(wkn, NULL, screen, &wkn1_dest);
								}
								else if(new_game->Board[i][j]->Piece->Type == Bishop){
									wb1_dest.x = new_game->Board[i][j]->x;
									wb1_dest.y = new_game->Board[i][j]->y;
									SDL_BlitSurface(wb, NULL, screen, &wb1_dest);
								}
								else if(new_game->Board[i][j]->Piece->Type == Rook){
									wr1_dest.x = new_game->Board[i][j]->x;
									wr1_dest.y = new_game->Board[i][j]->y;
									SDL_BlitSurface(wr, NULL, screen, &wr1_dest);
								}
								else if(new_game->Board[i][j]->Piece->Type == Queen){
									wq_dest.x = new_game->Board[i][j]->x;
									wq_dest.y = new_game->Board[i][j]->y;
									SDL_BlitSurface(wq, NULL, screen, &wq_dest);
								}
								else if(new_game->Board[i][j]->Piece->Type == King){
									wk_dest.x = new_game->Board[i][j]->x;
									wk_dest.y = new_game->Board[i][j]->y;
									SDL_BlitSurface(wk, NULL, screen, &wk_dest);
								}	
							}
							if(new_game->Board[i][j]->Piece != NULL && new_game->Board[i][j]->Piece->Player == Black){
								if(new_game->Board[i][j]->Piece->Type == Pawn){
									bp1_dest.x = new_game->Board[i][j]->x;
									bp1_dest.y = new_game->Board[i][j]->y;
									SDL_BlitSurface(bp, NULL, screen, &bp1_dest);
								}
								else if(new_game->Board[i][j]->Piece->Type == Knight){
									bkn1_dest.x = new_game->Board[i][j]->x;
									bkn1_dest.y = new_game->Board[i][j]->y;
									SDL_BlitSurface(bkn, NULL, screen, &bkn1_dest);
								}
								else if(new_game->Board[i][j]->Piece->Type == Bishop){
									bb1_dest.x = new_game->Board[i][j]->x;
									bb1_dest.y = new_game->Board[i][j]->y;
									SDL_BlitSurface(bb, NULL, screen, &bb1_dest);
								}
								else if(new_game->Board[i][j]->Piece->Type == Rook){
									br1_dest.x = new_game->Board[i][j]->x;
									br1_dest.y = new_game->Board[i][j]->y;
									SDL_BlitSurface(br, NULL, screen, &br1_dest);
								}
								else if(new_game->Board[i][j]->Piece->Type == Queen){
									bq_dest.x = new_game->Board[i][j]->x;
									bq_dest.y = new_game->Board[i][j]->y;
									SDL_BlitSurface(bq, NULL, screen, &bq_dest);
								}
								else if(new_game->Board[i][j]->Piece->Type == King){
									bk_dest.x = new_game->Board[i][j]->x;
									bk_dest.y = new_game->Board[i][j]->y;
									SDL_BlitSurface(bk, NULL, screen, &bk_dest);
								}	
							}

						}
					}
					SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
					break;
				} 

				if (x1 > 250 && x1 < 450 && y1 > 680 && y1 < 730 && x1 == x2 && y1 == y2){
					printf("Forfeit button pressed\n");
					if (player_count % 2 == 0)
						printf("White forfeits. Black wins!\n");
					else
						printf("Black forfeits. White wins!\n");
						Running = 0;
						break;
				}

				if ((draw_flag == 0 && x1 > 500 && x1 < 700 && y1 > 680 && y1 < 730 && x1 == x2 && y1 == y2) || draw_flag == 1){
					if (draw_flag == 0){
						SDL_BlitSurface(draw_confirm, NULL, screen, &draw_confirm_dest);
						SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
						draw_flag = 1;
						break;
					}
					else{
						if (x1 > 500 && x1 < 700 && y1 > 680 && y1 < 730 && x1 == x2 && y1 == y2){
							Running = 0;
							draw_flag = 0;
							break;
						}
						else{
							SDL_BlitSurface(image, &src, screen, &dest);
							SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
							for(int i = 0; i < 8; i++){
								for(int j = 0; j < 8; j++){
									/*blit the images*/ 
									if(new_game->Board[i][j]->Piece != NULL && new_game->Board[i][j]->Piece->Player == White){
										if(new_game->Board[i][j]->Piece->Type == Pawn){
											wp1_dest.x = new_game->Board[i][j]->x;
											wp1_dest.y = new_game->Board[i][j]->y;
											SDL_BlitSurface(wp, NULL, screen, &wp1_dest);
										}
										else if(new_game->Board[i][j]->Piece->Type == Knight){
											wkn1_dest.x = new_game->Board[i][j]->x;
											wkn1_dest.y = new_game->Board[i][j]->y;
											SDL_BlitSurface(wkn, NULL, screen, &wkn1_dest);
										}
										else if(new_game->Board[i][j]->Piece->Type == Bishop){
											wb1_dest.x = new_game->Board[i][j]->x;
											wb1_dest.y = new_game->Board[i][j]->y;
											SDL_BlitSurface(wb, NULL, screen, &wb1_dest);
										}
										else if(new_game->Board[i][j]->Piece->Type == Rook){
											wr1_dest.x = new_game->Board[i][j]->x;
											wr1_dest.y = new_game->Board[i][j]->y;
											SDL_BlitSurface(wr, NULL, screen, &wr1_dest);
										}
										else if(new_game->Board[i][j]->Piece->Type == Queen){
											wq_dest.x = new_game->Board[i][j]->x;
											wq_dest.y = new_game->Board[i][j]->y;
											SDL_BlitSurface(wq, NULL, screen, &wq_dest);
										}
										else if(new_game->Board[i][j]->Piece->Type == King){
											wk_dest.x = new_game->Board[i][j]->x;
											wk_dest.y = new_game->Board[i][j]->y;
											SDL_BlitSurface(wk, NULL, screen, &wk_dest);
										}	
									}
									if(new_game->Board[i][j]->Piece != NULL && new_game->Board[i][j]->Piece->Player == Black){
										if(new_game->Board[i][j]->Piece->Type == Pawn){
											bp1_dest.x = new_game->Board[i][j]->x;
											bp1_dest.y = new_game->Board[i][j]->y;
											SDL_BlitSurface(bp, NULL, screen, &bp1_dest);
										}
										else if(new_game->Board[i][j]->Piece->Type == Knight){
											bkn1_dest.x = new_game->Board[i][j]->x;
											bkn1_dest.y = new_game->Board[i][j]->y;
											SDL_BlitSurface(bkn, NULL, screen, &bkn1_dest);
										}
										else if(new_game->Board[i][j]->Piece->Type == Bishop){
											bb1_dest.x = new_game->Board[i][j]->x;
											bb1_dest.y = new_game->Board[i][j]->y;
											SDL_BlitSurface(bb, NULL, screen, &bb1_dest);
										}
										else if(new_game->Board[i][j]->Piece->Type == Rook){
											br1_dest.x = new_game->Board[i][j]->x;
											br1_dest.y = new_game->Board[i][j]->y;
											SDL_BlitSurface(br, NULL, screen, &br1_dest);
										}
										else if(new_game->Board[i][j]->Piece->Type == Queen){
											bq_dest.x = new_game->Board[i][j]->x;
											bq_dest.y = new_game->Board[i][j]->y;
											SDL_BlitSurface(bq, NULL, screen, &bq_dest);
										}
										else if(new_game->Board[i][j]->Piece->Type == King){
											bk_dest.x = new_game->Board[i][j]->x;
											bk_dest.y = new_game->Board[i][j]->y;
											SDL_BlitSurface(bk, NULL, screen, &bk_dest);
										}	
									}

								}
							}
							SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
							draw_flag = 0;
							break;
						}	
					}
				}

				if(position1->Piece == NULL){
					printf("Empty position.\n");
				break;
				}
				else if((player_count%2 == 0 && position1 -> Piece -> Player == Black) || (player_count%2 != 0 && position1 -> Piece -> Player == White)){
					printf("Not your move!\n");
				break;
				}
				else{
				//printf("Oh! Mouse button %d pressed!\n",event.button.button);
				position2 = getPosition(x2, y2, new_game);	
				}

			if(Is_Legal(position1, position2, new_game) > 0){
				
				/*if(position1->Piece->Type == King && position1->Piece->Player==Black){
					checkerbk+=1;
				}
				else if((int)(position1->File)-65 == 7 && position1->Piece->Type == Rook && position1->Piece->Player == Black){
					checkerbrr+=1;
				}
				else if(position1->Piece->Type == King && position1->Piece->Player==White){
					checkerwk+=1;
				}
				else if((int)(position1->File)-65 == 7 && position1->Piece->Type == Rook && position1->Piece->Player == White){
					checkerwrr+=1;
				}
				else if((int)(position1->File)-65 == 0 && position1->Piece->Type == Rook && position1->Piece->Player == Black){
					checkerbrl+=1;
				}
				else if((int)(position1->File)-65 == 0 && position1->Piece->Type == Rook && position1->Piece->Player == White){
					checkerwrl+=1;
				}*/

				movePiece(position1, position2, new_game);
				if(Check(player_count, new_game) > 0){
					
					new_game = NULL;
					Undo(game_list);
					new_game = CurrentGame(game_list);
					printf("Illegal Move! King under attack!\n");

					t_Game *tempGame = NULL;
					tempGame = CopyGame(new_game);
					new_game = tempGame;
					break;
				}
				printf("legal move\n");
				printf("From %c%d.\n",
					position1->File, position1->Rank);
				printf("To %c%d\n",
					position2->File, position2->Rank); 

				/*if(checkerbk > 0){
					castling_flagbk+=1;
				}
				else if (checkerbrr>0){
					castling_flagbrr+=1;
				}
				else if (checkerwrr>0){
					castling_flagwrr+=1;
				}
				else if (checkerwk>0){
					castling_flagwk+=1;
				}
				else if (checkerwrl>0){
					castling_flagwrl+=1;
				}
				else if (checkerbrl>0){
					castling_flagbrl+=1;
				}*/
				
				SDL_BlitSurface(image, &src, screen, &dest);
				SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
				for(int i = 0; i < 8; i++){
					for(int j = 0; j < 8; j++){
				 		/*blit the images*/ 
						if(new_game->Board[i][j]->Piece != NULL && new_game->Board[i][j]->Piece->Player == White){
							if(new_game->Board[i][j]->Piece->Type == Pawn){
								wp1_dest.x = new_game->Board[i][j]->x;
								wp1_dest.y = new_game->Board[i][j]->y;
								SDL_BlitSurface(wp, NULL, screen, &wp1_dest);
							}
							else if(new_game->Board[i][j]->Piece->Type == Knight){
								wkn1_dest.x = new_game->Board[i][j]->x;
								wkn1_dest.y = new_game->Board[i][j]->y;
								SDL_BlitSurface(wkn, NULL, screen, &wkn1_dest);
							}
							else if(new_game->Board[i][j]->Piece->Type == Bishop){
								wb1_dest.x = new_game->Board[i][j]->x;
								wb1_dest.y = new_game->Board[i][j]->y;
								SDL_BlitSurface(wb, NULL, screen, &wb1_dest);
							}
							else if(new_game->Board[i][j]->Piece->Type == Rook){
								wr1_dest.x = new_game->Board[i][j]->x;
								wr1_dest.y = new_game->Board[i][j]->y;
								SDL_BlitSurface(wr, NULL, screen, &wr1_dest);
							}
							else if(new_game->Board[i][j]->Piece->Type == Queen){
								wq_dest.x = new_game->Board[i][j]->x;
								wq_dest.y = new_game->Board[i][j]->y;
								SDL_BlitSurface(wq, NULL, screen, &wq_dest);
							}
							else if(new_game->Board[i][j]->Piece->Type == King){
								wk_dest.x = new_game->Board[i][j]->x;
								wk_dest.y = new_game->Board[i][j]->y;
								SDL_BlitSurface(wk, NULL, screen, &wk_dest);
							}	
						}
						if(new_game->Board[i][j]->Piece != NULL && new_game->Board[i][j]->Piece->Player == Black){
							if(new_game->Board[i][j]->Piece->Type == Pawn){
								bp1_dest.x = new_game->Board[i][j]->x;
								bp1_dest.y = new_game->Board[i][j]->y;
								SDL_BlitSurface(bp, NULL, screen, &bp1_dest);
							}
							else if(new_game->Board[i][j]->Piece->Type == Knight){
								bkn1_dest.x = new_game->Board[i][j]->x;
								bkn1_dest.y = new_game->Board[i][j]->y;
								SDL_BlitSurface(bkn, NULL, screen, &bkn1_dest);
							}
							else if(new_game->Board[i][j]->Piece->Type == Bishop){
								bb1_dest.x = new_game->Board[i][j]->x;
								bb1_dest.y = new_game->Board[i][j]->y;
								SDL_BlitSurface(bb, NULL, screen, &bb1_dest);
							}
							else if(new_game->Board[i][j]->Piece->Type == Rook){
								br1_dest.x = new_game->Board[i][j]->x;
								br1_dest.y = new_game->Board[i][j]->y;
								SDL_BlitSurface(br, NULL, screen, &br1_dest);
							}
							else if(new_game->Board[i][j]->Piece->Type == Queen){
								bq_dest.x = new_game->Board[i][j]->x;
								bq_dest.y = new_game->Board[i][j]->y;
								SDL_BlitSurface(bq, NULL, screen, &bq_dest);
							}
							else if(new_game->Board[i][j]->Piece->Type == King){
								bk_dest.x = new_game->Board[i][j]->x;
								bk_dest.y = new_game->Board[i][j]->y;
								SDL_BlitSurface(bk, NULL, screen, &bk_dest);
							}	
						}

					}
				}
				SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
				player_count+=1;
			/* Insufficient materials: Draw */
			if(insufficientMaterial(new_game) == 1){
				printf("It is a draw!\n");
				break;
				Running = 0;
			}
			else if(Checkmate(player_count, new_game) == 1){
				if(player_count%2 == 0)
					printf("Checkmate Black wins!\n");
				else
					printf("Checkmate White wins\n");
				break;
				Running = 0;		
			}
			else if(Stalemate(player_count, new_game) == 1){
				printf("Stalemate It's a draw!\n");
				break;
				Running = 0;		
			}
			else{
				

				t_Game *tempGame = NULL;
				tempGame = CopyGame(new_game);
				new_game = tempGame;
			}
			}

					break;
			}
			case SDL_QUIT:
			{	printf("Quit event received!\n");
				Running = 0;
				break;
			}
			default: /* ignore any other events */
			{	/*printf("Oops, unknown event!\n");*/
				break;
			}
		}
	}
	if(player_count%2 != player_Flag){
		ComputerMove(new_game, player_Flag);
		t_Game *tempGame = NULL;
		tempGame = CopyGame(new_game);
		new_game = tempGame;

		if(insufficientMaterial(new_game) == 1){
				printf("It is a draw!\n");
				break;
				Running = 0;
			}
		else if(Checkmate(player_count, new_game) == 1){
				if(player_count%2 == 0)
					printf("Checkmate Black wins!\n");
				else
					printf("Checkmate White wins\n");
				break;
				Running = 0;		
			}
		
		else if(StalemateAI(player_count, new_game) == 1){
			printf("Stalemate It's a draw!\n");
			break;
			Running = 0;		
			}

		SDL_BlitSurface(image, &src, screen, &dest);
		SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
		for(int i = 0; i < 8; i++){
			for(int j = 0; j < 8; j++){
				/*blit the images*/ 
				if(new_game->Board[i][j]->Piece != NULL && new_game->Board[i][j]->Piece->Player == White){
					if(new_game->Board[i][j]->Piece->Type == Pawn){
						wp1_dest.x = new_game->Board[i][j]->x;
						wp1_dest.y = new_game->Board[i][j]->y;
						SDL_BlitSurface(wp, NULL, screen, &wp1_dest);
					}
					else if(new_game->Board[i][j]->Piece->Type == Knight){
						wkn1_dest.x = new_game->Board[i][j]->x;
						wkn1_dest.y = new_game->Board[i][j]->y;
						SDL_BlitSurface(wkn, NULL, screen, &wkn1_dest);
					}
					else if(new_game->Board[i][j]->Piece->Type == Bishop){
						wb1_dest.x = new_game->Board[i][j]->x;
						wb1_dest.y = new_game->Board[i][j]->y;
						SDL_BlitSurface(wb, NULL, screen, &wb1_dest);
					}
					else if(new_game->Board[i][j]->Piece->Type == Rook){
						wr1_dest.x = new_game->Board[i][j]->x;
						wr1_dest.y = new_game->Board[i][j]->y;
						SDL_BlitSurface(wr, NULL, screen, &wr1_dest);
					}
					else if(new_game->Board[i][j]->Piece->Type == Queen){
						wq_dest.x = new_game->Board[i][j]->x;
						wq_dest.y = new_game->Board[i][j]->y;
						SDL_BlitSurface(wq, NULL, screen, &wq_dest);
					}
					else if(new_game->Board[i][j]->Piece->Type == King){
						wk_dest.x = new_game->Board[i][j]->x;
						wk_dest.y = new_game->Board[i][j]->y;
						SDL_BlitSurface(wk, NULL, screen, &wk_dest);
					}	
				}
				if(new_game->Board[i][j]->Piece != NULL && new_game->Board[i][j]->Piece->Player == Black){
					if(new_game->Board[i][j]->Piece->Type == Pawn){
						bp1_dest.x = new_game->Board[i][j]->x;
						bp1_dest.y = new_game->Board[i][j]->y;
						SDL_BlitSurface(bp, NULL, screen, &bp1_dest);
					}
					else if(new_game->Board[i][j]->Piece->Type == Knight){
						bkn1_dest.x = new_game->Board[i][j]->x;
						bkn1_dest.y = new_game->Board[i][j]->y;
						SDL_BlitSurface(bkn, NULL, screen, &bkn1_dest);
					}
					else if(new_game->Board[i][j]->Piece->Type == Bishop){
						bb1_dest.x = new_game->Board[i][j]->x;
						bb1_dest.y = new_game->Board[i][j]->y;
						SDL_BlitSurface(bb, NULL, screen, &bb1_dest);
					}
					else if(new_game->Board[i][j]->Piece->Type == Rook){
						br1_dest.x = new_game->Board[i][j]->x;
						br1_dest.y = new_game->Board[i][j]->y;
						SDL_BlitSurface(br, NULL, screen, &br1_dest);
					}
					else if(new_game->Board[i][j]->Piece->Type == Queen){
						bq_dest.x = new_game->Board[i][j]->x;
						bq_dest.y = new_game->Board[i][j]->y;
						SDL_BlitSurface(bq, NULL, screen, &bq_dest);
					}
					else if(new_game->Board[i][j]->Piece->Type == King){
						bk_dest.x = new_game->Board[i][j]->x;
						bk_dest.y = new_game->Board[i][j]->y;
						SDL_BlitSurface(bk, NULL, screen, &bk_dest);
					}	
				}

			}
		}
		SDL_UpdateRect(screen, dest.x, dest.y, dest.w, dest.h);
		player_count++;

	}
 /* hctiws */
	} /* elihw */
	}
#endif

	//Release the surface
	

	//closes file
	fclose(Log);
	//Return success!SDL_FreeSurface(image);
	SDL_FreeSurface(screen);
	SDL_FreeSurface(wb);
	SDL_FreeSurface(bb);
	SDL_FreeSurface(wp);
	SDL_FreeSurface(bp);
	SDL_FreeSurface(wr);
	SDL_FreeSurface(br);
	SDL_FreeSurface(wkn);
	SDL_FreeSurface(bkn);
	SDL_FreeSurface(wq);
	SDL_FreeSurface(bq);
	SDL_FreeSurface(wk);
	SDL_FreeSurface(bk);
	SDL_FreeSurface(undo);
	SDL_FreeSurface(forfeit);
	SDL_FreeSurface(draw);
	SDL_FreeSurface(draw_confirm);
	SDL_Quit();
	DeleteGameList(game_list);
	return 0;
}



/* Draw board function */


