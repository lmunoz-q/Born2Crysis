/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 13:47:53 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/17 13:49:38 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "doom-nukem.h"

/*
** TEMPORARY TESTS DO NOT TOUCH OR MAREK WILL SPANK YOU!
*/
void	init_test_world(t_e *e)
{
	t_polygon	*p;
	t_obj		*tmp;
	t_obj		*tmp2;

	e->world.sectornum = 1;
	e->world.sectors = (t_sector *)malloc(sizeof(t_sector));
	e->world.sectors->id = 0;
	e->world.sectors->objectnum = 0;
	e->world.sectors->meshnum = 1;
	e->world.sectors->mesh = (t_mesh *)malloc(sizeof(t_mesh));
	mat4_init(e->world.sectors->mesh->matrix);
	//mat4_rotate_pitch(e->world.sectors->mesh->matrix, 180.0);
	mat4_scale(e->world.sectors->mesh->matrix, 10, 10, 10);
	//mat4_translate(e->world.sectors->mesh->matrix, 0, 0, 2);
	e->world.sectors->mesh->polygonnum = 4;
	e->world.sectors->mesh->polygons = (t_polygon *)malloc(sizeof(t_polygon) * 4);
	p = e->world.sectors->mesh->polygons;
	vec4_copy(p[0].v01, (double [4]){-1, 1, -1, 1});
	vec4_copy(p[0].v12, (double [4]){1, 1, -1, 1});
	vec4_copy(p[0].v20, (double [4]){1, -1, -1, 1});
	vec2_copy(p[0].v01_uv, (double [2]){-1, 1});
	vec2_copy(p[0].v12_uv, (double [2]){1, 1});
	vec2_copy(p[0].v20_uv, (double [2]){1, -1});
	p[0].tex_id = load_texture_from_bmp("assets/lava.bmp", TX_REPEAT);
	vec4_copy(p[1].v01, (double [4]){1, -1, -1, 1});
	vec4_copy(p[1].v12, (double [4]){1, 1, -1, 1});
	vec4_copy(p[1].v20, (double [4]){1, 1, 1, 1});
	vec2_copy(p[1].v01_uv, (double [2]){0, 0});
	vec2_copy(p[1].v12_uv, (double [2]){1, 1});
	vec2_copy(p[1].v20_uv, (double [2]){0, 1});
	p[1].tex_id = load_texture_from_bmp("assets/house_tex.bmp", TX_REPEAT);
	vec4_copy(p[2].v01, (double [4]){-1, 1, 1, 1});
	vec4_copy(p[2].v12, (double [4]){1, -1, 1, 1});
	vec4_copy(p[2].v20, (double [4]){1, 1, 1, 1});
	vec2_copy(p[2].v01_uv, (double [2]){0, 0});
	vec2_copy(p[2].v12_uv, (double [2]){1, 1});
	vec2_copy(p[2].v20_uv, (double [2]){0, 1});
	p[2].tex_id = load_texture_from_bmp("assets/lava.bmp", TX_REPEAT);
	vec4_copy(p[3].v01, (double [4]){-1, -1, -1, 1});
	vec4_copy(p[3].v12, (double [4]){-1, 1, 1, 1});
	vec4_copy(p[3].v20, (double [4]){-1, 1, -1, 1});
	vec2_copy(p[3].v01_uv, (double [2]){0, 0});
	vec2_copy(p[3].v12_uv, (double [2]){1, 1});
	vec2_copy(p[3].v20_uv, (double [2]){0, 1});
	p[3].tex_id = load_texture_from_bmp("assets/house_tex.bmp", TX_REPEAT);
	tmp = load_obj("assets/house.obj");
	tmp2 = load_obj("assets/objects/office.obj");
	e->world.sectors->objectnum = 4;
	e->world.sectors->objects = (t_object *)malloc(sizeof(t_object) * 3);
	mf_memcpy(&e->world.sectors->objects[1], obj_to_object(tmp2, "assets/diffuse.bmp"), sizeof(t_object));
	mf_memcpy(&e->world.sectors->objects[0], obj_to_object(tmp, "assets/house_tex.bmp"), sizeof(t_object));
	mf_memcpy(&e->world.sectors->objects[3], obj_to_object(tmp, "assets/house_tex.bmp"), sizeof(t_object));
	mf_memcpy(&e->world.sectors->objects[2], obj_to_object(tmp, "assets/house_tex.bmp"), sizeof(t_object));
	
	mat4_scale(e->world.sectors->objects[0].mesh->matrix, 0.1, 0.1, 0.1);
	mat4_translate(e->world.sectors->objects[0].mesh->matrix, 0, 0, -100);
	mat4_scale(e->world.sectors->objects[1].mesh->matrix, 0.1, 0.1, 0.1);
	mat4_translate(e->world.sectors->objects[1].mesh->matrix, 40, 0, -100);
	mat4_scale(e->world.sectors->objects[2].mesh->matrix, 0.1, 0.1, 0.1);
	mat4_translate(e->world.sectors->objects[2].mesh->matrix, 80, 0, -100);
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
