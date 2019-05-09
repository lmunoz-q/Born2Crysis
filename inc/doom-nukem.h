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
# include "menu.h"

typedef enum		e_hosttype
{
	B2C_HOSTTYPE_SOLO,
	B2C_HOSTTYPE_HOST,
	B2C_HOSTTYPE_CLIENT
}					t_hosttype;

/*
** ex: B2C_GAMETYPE_PVP | B2C_GAMETYPE_TEAM for teams that kill each others
** ex: B2C_GAMETYPE_PVP for FFA (free for all)
** ex: B2C_GAMETYPE_PVE | B2C_GAMETYPE_TEAM (with only one team) for wave survival
** ex: B2C_GAMETYPE_PVE for survival
** etc...
*/

typedef enum		e_gametype
{
	B2C_GAMETYPE_PVE =  0b00000001, //players can damage npc
	B2C_GAMETYPE_PVP =  0b00000010, //players can damage other players
	B2C_GAMETYPE_TEAM = 0b00000100  //a team manager is active
};

/*
** threads:
** - main (monitor inputs and send them to the client thread, print the graphic buffer to the screen)
** - client (convert input to messages to the host, convert messages from the host to modifications on the players, entities and map)
** - graphic (print on a buffer the map, players, entities and hud)
** - server (receive commands from clients, simulate physics, send back the status of the world to clients)
*/

typedef enum		e_thread
{
	B2C_THREAD_CLIENT,
	B2C_THREAD_GRAPHIC,
	B2C_THREAD_SERVER
}					t_thread;

typedef struct		s_e
{
	t_libui_window	*win;
	SDL_Thread		*thread[3];
}					t_e;

# define DELTATIME		1.0 / 64.0


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
