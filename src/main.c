/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 13:47:53 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/26 20:10:31 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** TEMPORARY TESTS DO NOT TOUCH OR MAREK WILL SPANK YOU!
*/
void	init_test_world(t_e *e)
{
		SDL_RWops	*io;
		Uint64		size;
		t_map_file	*data;

		if (!(io = SDL_RWFromFile("test.b2cm", "rb")))
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

int main(void)
{
	t_e		env;

	env.world = (t_world){};
	start_sound(&env.sound);
	libui_init();
	set_world(&env.world);
	init_test_world(&env);
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
