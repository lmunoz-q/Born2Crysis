/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 13:47:53 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/20 15:22:48 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "doom-nukem.h"

/*
** TEMPORARY TESTS DO NOT TOUCH OR MAREK WILL SPANK YOU!
*/
void	init_test_world(t_e *e)
{
	t_polygon	*p;

	e->world.sectornum = 2;
	e->world.sectors = (t_sector *)malloc(sizeof(t_sector) * 2);
	e->world.sectors[0].id = 0;
	e->world.sectors[0].objectnum = 0;
	e->world.sectors[0].meshnum = 1;
	e->world.sectors[0].mesh = (t_mesh *)malloc(sizeof(t_mesh));
	mat4_init(e->world.sectors[0].mesh->matrix);
	//mat4_rotate_pitch(e->world.sectors->mesh->matrix, 180.0);
	e->world.sectors[0].lights.light_count = 0;
	//mat4_translate(e->world.sectors->mesh->matrix, 0, 0, 2);
	e->world.sectors[0].mesh->polygonnum = 10;
	e->world.sectors[0].mesh->polygons = (t_polygon *)malloc(sizeof(t_polygon) * 10);
	p = e->world.sectors[0].mesh->polygons;
	vec4_copy(p[0].v01, (double [4]){-20, -1, -20, 1});
	vec4_copy(p[0].v12, (double [4]){-20, -1, 20, 1});
	vec4_copy(p[0].v20, (double [4]){20, -1, -20, 1});
	vec2_copy(p[0].v01_uv, (double [2]){-3, -3});
	vec2_copy(p[0].v12_uv, (double [2]){-3, 1});
	vec2_copy(p[0].v20_uv, (double [2]){1, -3});
	p[0].tex_id = load_texture_from_bmp("assets/lava.bmp", TX_REPEAT);
	vec4_copy(p[1].v01, (double [4]){-20, -1, 20, 1});
	vec4_copy(p[1].v12, (double [4]){20, -1, 20, 1});
	vec4_copy(p[1].v20, (double [4]){20, -1, -20, 1});
	vec2_copy(p[1].v01_uv, (double [2]){-3, 1});
	vec2_copy(p[1].v12_uv, (double [2]){1, 1});
	vec2_copy(p[1].v20_uv, (double [2]){1, -3});
	p[1].tex_id = p[0].tex_id;
	vec4_copy(p[2].v01, (double [4]){-20, 8, -20, 1});
	vec4_copy(p[2].v12, (double [4]){-20, -1, -20, 1});
	vec4_copy(p[2].v20, (double [4]){20, -1, -20, 1});
	vec2_copy(p[2].v01_uv, (double [2]){-4, 0});
	vec2_copy(p[2].v12_uv, (double [2]){-4, 1});
	vec2_copy(p[2].v20_uv, (double [2]){1, 1});
	p[2].tex_id = load_texture_from_bmp("assets/redbrick.bmp", TX_REPEAT);
	vec4_copy(p[3].v01, (double [4]){20, 8, -20, 1});
	vec4_copy(p[3].v12, (double [4]){-20, 8, -20, 1});
	vec4_copy(p[3].v20, (double [4]){20, -1, -20, 1});
	vec2_copy(p[3].v01_uv, (double [2]){1, 0});
	vec2_copy(p[3].v12_uv, (double [2]){-4, 0});
	vec2_copy(p[3].v20_uv, (double [2]){1, 1});
	p[3].tex_id = p[2].tex_id;
	vec4_copy(p[4].v01, (double [4]){20, 8, -20, 1});
	vec4_copy(p[4].v12, (double [4]){20, -1, -20, 1});
	vec4_copy(p[4].v20, (double [4]){20, -1, 20, 1});
	vec2_copy(p[4].v01_uv, (double [2]){-4, 0});
	vec2_copy(p[4].v12_uv, (double [2]){-4, 1});
	vec2_copy(p[4].v20_uv, (double [2]){1, 1});
	p[4].tex_id = p[2].tex_id;
	vec4_copy(p[5].v01, (double [4]){20, 8, 20, 1});
	vec4_copy(p[5].v12, (double [4]){20, 8, -20, 1});
	vec4_copy(p[5].v20, (double [4]){20, -1, 20, 1});
	vec2_copy(p[5].v01_uv, (double [2]){1, 0});
	vec2_copy(p[5].v12_uv, (double [2]){-4, 0});
	vec2_copy(p[5].v20_uv, (double [2]){1, 1});
	p[5].tex_id = p[2].tex_id;
	vec4_copy(p[6].v01, (double [4]){-20, 8, 20, 1});
	vec4_copy(p[6].v12, (double [4]){20, -1, 20, 1});
	vec4_copy(p[6].v20, (double [4]){-20, -1, 20, 1});
	vec2_copy(p[6].v01_uv, (double [2]){-4, 0});
	vec2_copy(p[6].v12_uv, (double [2]){1, 1});
	vec2_copy(p[6].v20_uv, (double [2]){-4, 1});
	p[6].tex_id = p[2].tex_id;
	vec4_copy(p[7].v01, (double [4]){-20, 8, 20, 1});
	vec4_copy(p[7].v12, (double [4]){20, 8, 20, 1});
	vec4_copy(p[7].v20, (double [4]){20, -1, 20, 1});
	vec2_copy(p[7].v01_uv, (double [2]){-4, 0});
	vec2_copy(p[7].v12_uv, (double [2]){1, 0});
	vec2_copy(p[7].v20_uv, (double [2]){1, 1});
	p[7].tex_id = p[2].tex_id;
	vec4_copy(p[8].v01, (double [4]){-20, 8, -20, 1});
	vec4_copy(p[8].v12, (double [4]){-20, -1, 20, 1});
	vec4_copy(p[8].v20, (double [4]){-20, -1, -20, 1});
	vec2_copy(p[8].v01_uv, (double [2]){-4, 0});
	vec2_copy(p[8].v12_uv, (double [2]){1, 1});
	vec2_copy(p[8].v20_uv, (double [2]){-4, 1});
	p[8].tex_id = p[2].tex_id;
	vec4_copy(p[9].v01, (double [4]){-20, 8, -20, 1});
	vec4_copy(p[9].v12, (double [4]){-20, 8, 20, 1});
	vec4_copy(p[9].v20, (double [4]){-20, -1, 20, 1});
	vec2_copy(p[9].v01_uv, (double [2]){-4, 0});
	vec2_copy(p[9].v12_uv, (double [2]){1, 0});
	vec2_copy(p[9].v20_uv, (double [2]){1, 1});
	p[9].tex_id = p[2].tex_id;
}

int main()
{
	t_e		env;

	libui_init();
	if (!(env_init(&env)))
		return (-1);
	init_test_world(&env);
	launch_main_menu(&env);
	//load threads
	//run func (state manager or whatever the fuck you want to call it!
	//unload funcs
	//destroy funcs
	env_destroy(&env);
	libui_close();
	return (0);
}
