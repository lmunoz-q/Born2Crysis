#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

/*
** ##MAIN HEADER##
** only includes very general setup functions for the game,
** resource loading and unloading and trash collection after
** closing the software.
*/

/*
** libraries
*/
# include <libui.h>
# include <SDL2/SDL.h>
# include "mflib.h"

/*
** headers
*/
# include "utilities.h"

# define DELTATIME		1.0/64.0

typedef struct		s_progstats
{
	int				fps;
}					t_progstats;

typedef struct		s_e
{
	t_libui_window	*win;
	SDL_Thread		*thread[3];
	t_progstats		stats;
	t_bool			game_running;
}					t_e;

#include "menu.h"

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
