/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 13:47:53 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/09 15:06:51 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

/*
** TEMPORARY TESTS DO NOT TOUCH OR MAREK WILL SPANK YOU!
*/
void	init_test_world(t_e *e)
{
	t_polygon	*p;
	t_obj		*tmp;
	//t_obj		*tmp2;

	e->world.sectornum = 2;
	e->world.sectors = (t_sector *)malloc(sizeof(t_sector) * 2);
	e->world.sectors[0].id = 0;
	e->world.sectors[0].objectnum = 0;
	e->world.sectors[0].meshnum = 2;
	e->world.sectors[0].mesh = (t_mesh *)malloc(sizeof(t_mesh) * 2);
	e->world.sectors[0].mesh[0].active = TRUE;
	e->world.sectors[0].mesh[1].active = TRUE;
	mat4_init(e->world.sectors[0].mesh->matrix);
	mat4_init(e->world.sectors[0].mesh[1].matrix);
	e->world.sectors[0].mesh->polygonnum = 8;
	e->world.sectors[0].mesh->sector_id = -1;
	e->world.sectors[0].mesh->polygons = (t_polygon *)malloc(sizeof(t_polygon) * 8);
	p = e->world.sectors[0].mesh->polygons;
	vec4_copy(p[0].v01, (double [4]){-20, -1, -20, 1});
	vec4_copy(p[0].v12, (double [4]){-20, -1, 20, 1});
	vec4_copy(p[0].v20, (double [4]){20, -1, -20, 1});
	vec2_copy(p[0].v01_uv, (double [2]){0, 0});
	vec2_copy(p[0].v12_uv, (double [2]){0, 4});
	vec2_copy(p[0].v20_uv, (double [2]){4, 0});
	p[0].tex_id = load_texture_from_bmp("assets/lava.bmp", TX_REPEAT);
	p[0].transparency = 0;
	vec4_copy(p[1].v01, (double [4]){-20, -1, 20, 1});
	vec4_copy(p[1].v12, (double [4]){20, -1, 20, 1});
	vec4_copy(p[1].v20, (double [4]){20, -1, -20, 1});
	vec2_copy(p[1].v01_uv, (double [2]){0, 4});
	vec2_copy(p[1].v12_uv, (double [2]){4, 4});
	vec2_copy(p[1].v20_uv, (double [2]){4, 0});
	p[1].tex_id = p[0].tex_id;
	p[1].transparency = 0;
	vec4_copy(p[2].v01, (double [4]){-20, 8, -20, 1});
	vec4_copy(p[2].v12, (double [4]){-20, -1, -20, 1});
	vec4_copy(p[2].v20, (double [4]){20, -1, -20, 1});
	vec2_copy(p[2].v01_uv, (double [2]){0, 0});
	vec2_copy(p[2].v12_uv, (double [2]){0, 2});
	vec2_copy(p[2].v20_uv, (double [2]){10, 2});
	p[2].tex_id = load_texture_from_bmp("assets/redbrick.bmp", TX_REPEAT);
	p[2].transparency = 0;
	vec4_copy(p[3].v01, (double [4]){20, 8, -20, 1});
	vec4_copy(p[3].v12, (double [4]){-20, 8, -20, 1});
	vec4_copy(p[3].v20, (double [4]){20, -1, -20, 1});
	vec2_copy(p[3].v01_uv, (double [2]){10, 0});
	vec2_copy(p[3].v12_uv, (double [2]){0, 0});
	vec2_copy(p[3].v20_uv, (double [2]){10, 2});
	p[3].tex_id = p[2].tex_id;
	p[3].transparency = 0;
	vec4_copy(p[4].v01, (double [4]){20, 8, -20, 1});
	vec4_copy(p[4].v12, (double [4]){20, -1, -20, 1});
	vec4_copy(p[4].v20, (double [4]){20, -1, 20, 1});
	vec2_copy(p[4].v01_uv, (double [2]){0, 0});
	vec2_copy(p[4].v12_uv, (double [2]){0, 2});
	vec2_copy(p[4].v20_uv, (double [2]){10, 2});
	p[4].tex_id = p[2].tex_id;
	p[4].transparency = 0;
	vec4_copy(p[5].v01, (double [4]){20, 8, 20, 1});
	vec4_copy(p[5].v12, (double [4]){20, 8, -20, 1});
	vec4_copy(p[5].v20, (double [4]){20, -1, 20, 1});
	vec2_copy(p[5].v01_uv, (double [2]){10, 0});
	vec2_copy(p[5].v12_uv, (double [2]){0, 0});
	vec2_copy(p[5].v20_uv, (double [2]){10, 2});
	p[5].tex_id = p[2].tex_id;
	p[5].transparency = 0;
	vec4_copy(p[6].v01, (double [4]){-20, 8, 20, 1});
	vec4_copy(p[6].v12, (double [4]){20, -1, 20, 1});
	vec4_copy(p[6].v20, (double [4]){-20, -1, 20, 1});
	vec2_copy(p[6].v01_uv, (double [2]){0, 0});
	vec2_copy(p[6].v12_uv, (double [2]){10, 2});
	vec2_copy(p[6].v20_uv, (double [2]){0, 2});
	p[6].tex_id = p[2].tex_id;
	p[6].transparency = 0;
	vec4_copy(p[7].v01, (double [4]){-20, 8, 20, 1});
	vec4_copy(p[7].v12, (double [4]){20, 8, 20, 1});
	vec4_copy(p[7].v20, (double [4]){20, -1, 20, 1});
	vec2_copy(p[7].v01_uv, (double [2]){0, 0});
	vec2_copy(p[7].v12_uv, (double [2]){10, 0});
	vec2_copy(p[7].v20_uv, (double [2]){10, 2});
	p[7].tex_id = p[2].tex_id;
	p[7].transparency = 0;
	e->world.sectors[0].mesh[1].polygonnum = 2;
	e->world.sectors[0].mesh[1].polygons = (t_polygon *)malloc(sizeof(t_polygon) * 2);
	e->world.sectors[0].mesh[1].sector_id = 1;
	p = e->world.sectors[0].mesh[1].polygons;
	mat4_init(e->world.sectors[0].mesh[1].matrix);
	vec4_copy(p[0].v01, (double [4]){-20, 8, -20, 1});
	vec4_copy(p[0].v12, (double [4]){-20, -1, 20, 1});
	vec4_copy(p[0].v20, (double [4]){-20, -1, -20, 1});
	vec2_copy(p[0].v01_uv, (double [2]){0, 0});
	vec2_copy(p[0].v12_uv, (double [2]){10, 2});
	vec2_copy(p[0].v20_uv, (double [2]){0, 2});
	p[0].tex_id = -1;
	p[0].transparency = 0;
	vec4_copy(p[1].v01, (double [4]){-20, 8, -20, 1});
	vec4_copy(p[1].v12, (double [4]){-20, 8, 20, 1});
	vec4_copy(p[1].v20, (double [4]){-20, -1, 20, 1});
	vec2_copy(p[1].v01_uv, (double [2]){0, 0});
	vec2_copy(p[1].v12_uv, (double [2]){10, 0});
	vec2_copy(p[1].v20_uv, (double [2]){10, 2});
	p[1].tex_id = -1;
	p[1].transparency = 0;
	e->world.sectors[0].mesh[1].radius = get_mesh_radius(&e->world.sectors[0].mesh[1]);
	e->world.sectors[0].mesh[0].radius = get_mesh_radius(&e->world.sectors[0].mesh[0]);

	e->world.sectors[1].id = 1;
	e->world.sectors[1].lights.light_count = 0;
	e->world.sectors[1].objectnum = 0;
	e->world.sectors[1].meshnum = 4;
	e->world.sectors[1].mesh = (t_mesh *)malloc(sizeof(t_mesh) * 4);
	e->world.sectors[1].mesh[0].active = TRUE;
	e->world.sectors[1].mesh[1].active = TRUE;
	e->world.sectors[1].mesh[2].active = TRUE;
	e->world.sectors[1].mesh[3].active = TRUE;
	mat4_init(e->world.sectors[1].mesh->matrix);
	e->world.sectors[1].mesh->polygonnum = 2;
	e->world.sectors[1].mesh->sector_id = -1;
	e->world.sectors[1].mesh->polygons = (t_polygon *)malloc(sizeof(t_polygon) * 2);
	p = e->world.sectors[1].mesh->polygons;
	vec4_copy(p[0].v01, (double [4]){-60, -1, -20, 1});
	vec4_copy(p[0].v12, (double [4]){-60, -1, 20, 1});
	vec4_copy(p[0].v20, (double [4]){-20, -1, -20, 1});
	vec2_copy(p[0].v01_uv, (double [2]){0, 0});
	vec2_copy(p[0].v12_uv, (double [2]){0, 4});
	vec2_copy(p[0].v20_uv, (double [2]){4, 0});
	p[0].tex_id = load_texture_from_bmp("assets/lava.bmp", TX_REPEAT);
	p[0].transparency = 0;
	vec4_copy(p[1].v01, (double [4]){-60, -1, 20, 1});
	vec4_copy(p[1].v12, (double [4]){-20, -1, 20, 1});
	vec4_copy(p[1].v20, (double [4]){-20, -1, -20, 1});
	vec2_copy(p[1].v01_uv, (double [2]){0, 4});
	vec2_copy(p[1].v12_uv, (double [2]){4, 4});
	vec2_copy(p[1].v20_uv, (double [2]){4, 0});
	p[1].tex_id = p[0].tex_id;
	p[1].transparency = 0;
	e->world.sectors[1].mesh[1].sector_id = 0;
	mat4_init(e->world.sectors[1].mesh[1].matrix);
	e->world.sectors[1].mesh[1].polygonnum = 2;
	e->world.sectors[1].mesh[1].polygons = (t_polygon *)malloc(sizeof(t_polygon) * 2);
	p = e->world.sectors[1].mesh[1].polygons;
	mat4_init(e->world.sectors[1].mesh[1].matrix);
	vec4_copy(p[0].v01, (double [4]){-20, 8, -20, 1});
	vec4_copy(p[0].v12, (double [4]){-20, -1, -20, 1});
	vec4_copy(p[0].v20, (double [4]){-20, -1, 20, 1});
	vec2_copy(p[0].v01_uv, (double [2]){0, 0});
	vec2_copy(p[0].v12_uv, (double [2]){0, 2});
	vec2_copy(p[0].v20_uv, (double [2]){10, 2});
	p[0].tex_id = -1;
	p[0].transparency = 0;
	vec4_copy(p[1].v01, (double [4]){-20, 8, 20, 1});
	vec4_copy(p[1].v12, (double [4]){-20, 8, -20, 1});
	vec4_copy(p[1].v20, (double [4]){-20, -1, 20, 1});
	vec2_copy(p[1].v01_uv, (double [2]){10, 0});
	vec2_copy(p[1].v12_uv, (double [2]){0, 0});
	vec2_copy(p[1].v20_uv, (double [2]){10, 2});
	p[1].tex_id = -1;
	p[1].transparency = 0;
	e->world.sectors[1].mesh[2].polygonnum = 2;
	e->world.sectors[1].mesh[2].polygons = (t_polygon *)malloc(sizeof(t_polygon) * 2);
	p = e->world.sectors[1].mesh[2].polygons;
	e->world.sectors[1].mesh[2].sector_id = -1;
	mat4_init(e->world.sectors[1].mesh[2].matrix);
	mat4_translate(e->world.sectors[1].mesh[2].matrix, -40, 0, 0);
	mat4_rotate_pitch(e->world.sectors[1].mesh[2].matrix, 270);
	vec4_copy(p[0].v01, (double [4]){-5, 8, -5, 1});
	vec4_copy(p[0].v12, (double [4]){-5, -1, -5, 1});
	vec4_copy(p[0].v20, (double [4]){5, -1, -5, 1});
	vec2_copy(p[0].v01_uv, (double [2]){0, 0});
	vec2_copy(p[0].v12_uv, (double [2]){0, 2});
	vec2_copy(p[0].v20_uv, (double [2]){2, 2});
	p[0].tex_id = load_texture_from_bmp("assets/redbrick.bmp", TX_REPEAT);
	p[0].transparency = 150;
	vec4_copy(p[1].v01, (double [4]){5, 8, -5, 1});
	vec4_copy(p[1].v12, (double [4]){-5, 8, -5, 1});
	vec4_copy(p[1].v20, (double [4]){5, -1, -5, 1});
	vec2_copy(p[1].v01_uv, (double [2]){2, 0});
	vec2_copy(p[1].v12_uv, (double [2]){0, 0});
	vec2_copy(p[1].v20_uv, (double [2]){2, 2});
	p[1].tex_id = p[0].tex_id;
	p[1].transparency = 150;
	e->world.sectors[1].mesh[3].polygonnum = 2;
	e->world.sectors[1].mesh[3].polygons = (t_polygon *)malloc(sizeof(t_polygon) * 2);
	p = e->world.sectors[1].mesh[3].polygons;
	e->world.sectors[1].mesh[3].sector_id = -1;
	mat4_init(e->world.sectors[1].mesh[3].matrix);
	mat4_translate(e->world.sectors[1].mesh[3].matrix, -30, 0, 5);
	mat4_rotate_pitch(e->world.sectors[1].mesh[3].matrix, 270);
	vec4_copy(p[0].v01, (double [4]){-5, 8, -5, 1});
	vec4_copy(p[0].v12, (double [4]){-5, -1, -5, 1});
	vec4_copy(p[0].v20, (double [4]){5, -1, -5, 1});
	vec2_copy(p[0].v01_uv, (double [2]){0, 0});
	vec2_copy(p[0].v12_uv, (double [2]){0, 2});
	vec2_copy(p[0].v20_uv, (double [2]){2, 2});
	p[0].tex_id = load_texture_from_bmp("assets/redbrick.bmp", TX_REPEAT);
	p[0].transparency = 150;
	vec4_copy(p[1].v01, (double [4]){5, 8, -5, 1});
	vec4_copy(p[1].v12, (double [4]){-5, 8, -5, 1});
	vec4_copy(p[1].v20, (double [4]){5, -1, -5, 1});
	vec2_copy(p[1].v01_uv, (double [2]){2, 0});
	vec2_copy(p[1].v12_uv, (double [2]){0, 0});
	vec2_copy(p[1].v20_uv, (double [2]){2, 2});
	p[1].tex_id = p[0].tex_id;
	p[1].transparency = 150;
	e->world.sectors[1].mesh[2].radius = get_mesh_radius(&e->world.sectors[1].mesh[2]);
	e->world.sectors[1].mesh[1].radius = get_mesh_radius(&e->world.sectors[1].mesh[1]);
	e->world.sectors[1].mesh[0].radius = get_mesh_radius(&e->world.sectors[1].mesh[0]);
	e->world.sectors[1].mesh[3].radius = get_mesh_radius(&e->world.sectors[1].mesh[3]);

	tmp = load_obj("assets/house.obj");
	//tmp2 = load_obj("assets/objects/office.obj");
	e->world.sectors->objectnum = 3;
	e->world.sectors->objects = (t_object *)malloc(sizeof(t_object) * 4);
	mf_memcpy(&e->world.sectors->objects[3], obj_to_object(tmp, "assets/stonewall.bmp", TX_REPEAT), sizeof(t_object));
	mf_memcpy(&e->world.sectors->objects[0], obj_to_object(tmp, "assets/house_tex.bmp", TX_CLAMP_EDGES), sizeof(t_object));
	mf_memcpy(&e->world.sectors->objects[1], obj_to_object(tmp, "assets/house_tex.bmp", TX_CLAMP_EDGES), sizeof(t_object));
	mf_memcpy(&e->world.sectors->objects[2], obj_to_object(tmp, "assets/house_tex.bmp", TX_CLAMP_EDGES), sizeof(t_object));
	
	mat4_scale(e->world.sectors->objects[0].mesh->matrix, 0.2, 0.2, 0.2);
	mat4_translate(e->world.sectors->objects[0].mesh->matrix, 0, 0, -100);
	mat4_scale(e->world.sectors->objects[1].mesh->matrix, 0.2, 0.2, 0.2);
	mat4_translate(e->world.sectors->objects[1].mesh->matrix, 80, 0, -100);
	mat4_scale(e->world.sectors->objects[2].mesh->matrix, 0.2, 0.2, 0.2);
	mat4_translate(e->world.sectors->objects[2].mesh->matrix, 160, 0, -100);
	mat4_scale(e->world.sectors->objects[3].mesh->matrix, 0.2, 0.2, 0.2);
	mat4_rotate_pitch(e->world.sectors->objects[3].mesh->matrix, 90);
	mat4_translate(e->world.sectors->objects[3].mesh->matrix, -80, 0, -80);

	e->world.sectors[0].lights.light_count = 1;
	e->world.sectors[0].lights.lights = (t_light *)malloc(sizeof(t_light));
	e->world.sectors[0].lights.lights[0].type = POINT_LIGHT;
	e->world.sectors[0].lights.lights[0].pos_o[0] = 8;
	e->world.sectors[0].lights.lights[0].pos_o[1] = 5;
	e->world.sectors[0].lights.lights[0].pos_o[2] = -10;
	e->world.sectors[0].lights.lights[0].pos_o[3] = 1;
	e->world.sectors[0].lights.lights[0].intensity = 150;
	e->world.sectors[0].lights.lights[0].dir[0] = 0;
	e->world.sectors[0].lights.lights[0].dir[1] = 0.3;
	e->world.sectors[0].lights.lights[0].dir[2] = 0.7;
	mat4_init(e->world.sectors[0].lights.lights[0].mat);
}

#include <physic.h>

t_wall	wall_from_triangle(t_double3 triangle[3]) //clock-wise notation
{
	t_wall	out;
	double	t;
	double	msd;
	int		i;

	out.vertices[0] = triangle[0];
	out.vertices[1] = triangle[1];
	out.vertices[2] = triangle[2];
	out.normal = d3_normalize(d3_cross_product(
		d3_substract(triangle[1], triangle[0]),
		d3_substract(triangle[2], triangle[0])));
	out.center = d3_scale(
		d3_add(d3_add(triangle[0], triangle[1]), triangle[2]), 1.0 / 3.0);
	out.handler = NULL;
	msd = 0.0;
	i = -1;
	while (++i < 3)
	{
		t = d3_squared_magnitude(d3_substract(triangle[i], out.center));
		if (t > msd)
			msd = t;
	}
	out.radius = sqrt(msd);
	return (out);
}

int main()
{
//	t_e		env;

	t_wall		wall;
	double		correction;

	wall = wall_from_triangle((t_double3[3]){{1,0,1},{-1,0,-1},{-1,0,1}});
	printf("normal: %f %f %f\n", wall.normal.x, wall.normal.y, wall.normal.z);
	printf("center: %f %f %f\n", wall.center.x, wall.center.y, wall.center.z);
	printf("radius: %f\n", wall.radius);
	//dans ce test, le mur est un sol, d'epaisseur 10, 0 unitées devant le mur (donc un volume de 10 unitées derrière le mur)
	//le point ce situe 1 unitée derrière le mur (donc dans la hitarea)
	printf("collision: %d\n", point_in_extruded_wall((t_double3){0, -1, 0}, wall, (t_double2){10, 0}, &correction));
	//cette fois l'area est décallée de 5 unitées
	printf("collision: %d\n", point_in_extruded_wall((t_double3){0, -1, 0}, wall, (t_double2){10, 5}, &correction));
	//	libui_init();
//	if (!(env_init(&env)))
//		return (-1);
//	init_test_world(&env);
//	launch_main_menu(&env);
	//load threads
	//run func (state manager or whatever the fuck you want to call it!
	//unload funcs
	//destroy funcs
//	env_destroy(&env);
//	libui_close();
	return (0);
}
