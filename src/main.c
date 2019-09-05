/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 13:47:53 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/04 15:05:37 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** TEMPORARY TESTS DO NOT TOUCH OR MAREK WILL SPANK YOU!
*/

void			init_test_world(t_e *e, char *path)
{
	SDL_RWops	*io;
	Uint64		size;
	t_map_file	*data;

	if (!(io = SDL_RWFromFile(path, "rb")))
		return ;
	size = 0;
	SDL_RWread(io, &size, 1, 8);
	data = SDL_malloc(size);
	data->total_size = size;
	SDL_RWread(io, &data->nb_textures, 1, size - 8);
	SDL_RWclose(io);
	e->world = map_file_to_world(data);
	SDL_free(data);
}

t_error_type	debug_bmml_func(t_processor *p, char *data)
{
	(void)p;
	printf("Process: debug: %p\n", (void*)data);
	return (ET_OK);
}

int				printerror(char *s)
{
	mf_printf(s);
	return (-1);
}

void			addrs(t_e *env)
{
	add_address_to_library(&env->world.lib, "env", (char*)env);
	add_address_to_library(&env->world.lib, "world", (char*)&env->world);
	add_address_to_library(&env->world.lib, "player", (char*)&env->main_player);
	add_address_to_library(&env->world.lib, "player_body",
						(char*)&env->main_player.entity.body);
}

int				main(int argc, char **argv)
{
	t_e		env;

	env.world = (t_world){.nb_textures = 0};
	if (argc != 2)
		return (printerror("doom-nukem takes at least one argument...\n"));
	start_sound(&env.sound);
	libui_init();
	set_world(&env.world);
	init_library(&env.world.lib);
	addrs(&env);
	add_extern_function_to_library(&env.world.lib, "debug", debug_bmml_func);
	init_test_world(&env, argv[1]);
	env.editor.path = argv[1];
	if (!(init_world(&env.world)))
		return (FALSE);
	if (!(env_init(&env)))
		return (-1);
	init_player(&env.main_player, &env.world);
	launch_main_menu(&env);
	env_destroy(&env);
	libui_close();
	return (0);
}
