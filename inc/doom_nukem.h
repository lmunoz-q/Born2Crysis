/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 19:43:15 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/09/04 19:41:16 by mfischer         ###   ########.fr       */
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
# include <mflib.h>
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
# include "bmml.h"
# include "perlin.h"

# define DELTATIME		1.0 / 64.0
# define WIN_RADIUS		15

typedef struct		s_sound
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
	t_bool				endscreen_running;
	t_editor_interface	editor;
	t_sound				sound;
	t_mesh				*endscreen;
    TTF_Font			*font;
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
void				run_end_screen(t_e	*e);
void				update(t_e *e);

void				render(t_e *e);
void				render_endscreen(t_e *e);

t_e					*get_env();
t_e					*set_env(t_e *e);

/*
** UPDATE FUNCS
*/
void				player_update(t_e *e);
void				camera_update(t_e	*e);
void				win_condition(t_e *e);

/*
** UTILS
*/

void				hud(t_e *e);

/*
** SOUND
*/

void				start_sound(t_sound	*sound);

/*
** PLAYER / EIDOS
*/

int					update_player(t_world *world, t_player *player);
int					eidos_rewind(t_player_entity *player);

#endif
