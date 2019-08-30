/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 19:43:15 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/08/30 13:03:57 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <SDL2/SDL_mixer.h>

/*
** headers
*/

# include "typedefs.h"
# include "menu.h"
# include "utilities.h"
# include "graphics.h"
# include "world.h"
# include "camera.h"
# include "player.h"
# include "editor.h"
# include "event_handler.h"
# include "key_funcs.h"
# include "objparser.h"
# include "object_manager.h"
# include "map_file.h"

typedef enum		e_hosttype
{
	B2C_HOSTTYPE_SOLO,
	B2C_HOSTTYPE_HOST,
	B2C_HOSTTYPE_CLIENT
}					t_hosttype;

/*
** ex: B2C_GAMETYPE_PVP | B2C_GAMETYPE_TEAM for teams that kill each others
** ex: B2C_GAMETYPE_PVP for FFA (free for all)
** ex: B2C_GAMETYPE_PVE | B2C_GAMETYPE_TEAM (with only one team) for wave
** survival
** ex: B2C_GAMETYPE_PVE for survival
** etc...
*/

typedef enum		e_gametype
{
	B2C_GAMETYPE_PVE =  0b00000001, //players can damage npc
	B2C_GAMETYPE_PVP =  0b00000010, //players can damage other players
	B2C_GAMETYPE_TEAM = 0b00000100  //a team manager is active
}					t_gametype;

/*
** threads:
** - main (monitor inputs and send them to the client thread,
**   print the graphic buffer to the screen)
** - client (convert input to messages to the host, convert messages from the
**   host to modifications on the players, entities and map)
** - graphic (print on a buffer the map, players, entities and hud)
** - server (receive commands from clients, simulate physics,
**   send back the status of the world to clients)
*/

typedef enum		e_thread
{
	B2C_THREAD_CLIENT,
	B2C_THREAD_GRAPHIC,
	B2C_THREAD_SERVER
}					t_thread;

# define DELTATIME		1.0 / 64.0
# define WIN_RADIUS		15

typedef struct 		s_sound
{
	Mix_Chunk		*sound;
	Mix_Chunk		*step;
}					t_sound;

typedef struct		s_progstats
{
	int				fps;
	t_bool			win;
}					t_progstats;

struct				s_e
{
	t_libui_window		*win;
	SDL_Thread			*thread[3];
	t_progstats			stats;
	t_world				world;
	t_player			main_player;
	t_camera			camera;
	t_input_map			input_map;
	t_bool				game_running;
	t_bool				editor_running;
	t_editor_interface	editor;
	t_sound				sound;
};

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

t_bool				init_game_state(t_e *e);
void				run_game(t_e *e);
void				update(t_e *e);

void				render(t_e *e);

/*
** UPDATE FUNCS
*/
void				player_update(t_e *e);
void				camera_update(t_e	*e);
void        		win_condition(t_e *e);

/*
** UTILS
*/

void				start_sound(t_sound	*sound);

/*
** SOUND
*/


#endif
