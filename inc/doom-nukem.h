#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

/*
** ##MAIN HEADER##
** only includes very general setup functions for the game,
** resource loading and unloading and trash collection after
** closing the software.
*/

# include <libui.h>
# include <SDL2/SDL.h>
# include "mflib.h"

typedef struct s_e
{
	t_libui_window *win;
	SDL_Thread *	thread[3];
} t_e;

#include "menu.h"

# define DELTATIME		1.0/64.0


# define MAX_SCREENS	100
# define SCREENS		1
# define INTRO_SCREEN	0
# define MENU_SCREEN	1
# define GAME_SCREEN	2
# define CREDIT_SCREEN	3

/*
**	Initialize the environment structure
*/
t_bool				env_init(t_e *e);

/*
** destroy and clean the environment
*/
void				env_destroy(t_e *e);

/*
** GAME RUN LOOP
*/
void				run_game(t_e *e);

#endif
