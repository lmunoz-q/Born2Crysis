/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 13:47:53 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/22 20:43:57 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** TEMPORARY TESTS DO NOT TOUCH OR MAREK WILL SPANK YOU!
*/
void	init_test_world(t_e *e)
{
	// /*
		SDL_RWops	*io;
		Uint64		size;
		t_map_file	*data;

		if (!(io = SDL_RWFromFile("test.b2cm", "rb")))
			return ;
		size = 0;
		SDL_RWread(io, &size, 1, 8);
		printf("file size: %llu\n", size);
		data = SDL_malloc(size);
		data->total_size = size;
		SDL_RWread(io, &data->nb_textures, 1, size - 8);
		SDL_RWclose(io);
		e->world = map_file_to_world(data);
		SDL_free(data);
	// */

	/*
	t_polygon	*p;

	e->world.sectornum = 2;
	e->world.sectors = (t_sector *)SDL_calloc(sizeof(t_sector), 2);

	//
	e->world.sectors[0].physics = (t_sector_physics){.gravity={{0,-1.2,0}},.speed_limit=1.00,.global_friction={{0.95,1,0.95}},.drag={{0.95,1,0.95}}};
	e->world.sectors[1].physics = (t_sector_physics){.gravity={{0,-1.2,0}},.speed_limit=1,.global_friction={{0.95,0.95,0.95}},.drag={{1,1,1}},.entering_effet=EFF_ACTIVATE_FLY,.leaving_effect=EFF_DEACTIVATE_FLY};
	//

	e->world.sectors[0].id = 0;
	e->world.sectors[0].meshnum = 2;
	e->world.sectors[0].mesh = (t_mesh *)SDL_calloc(sizeof(t_mesh), 2);

	e->world.sectors[0].mesh[0].walls = SDL_calloc(sizeof(t_wall), 8);
	e->world.sectors[0].mesh[0].walls[0] = wall_from_triangle((t_vec3d[3]){{{-20, -1, -20}}, {{-20, -1, 20}}, {{20, -1, -20}}});
	e->world.sectors[0].mesh[0].walls[0].friction = 1;
	e->world.sectors[0].mesh[0].walls[0].on_contact_trigger = EFF_RESET_JUMP;
	e->world.sectors[0].mesh[0].walls[1] = wall_from_triangle((t_vec3d[3]){{{-20, -1, 20}}, {{20, -1, 20}}, {{20, -1, -20}}});
	e->world.sectors[0].mesh[0].walls[1].friction = 1;
	e->world.sectors[0].mesh[0].walls[1].on_contact_trigger = EFF_RESET_JUMP;
	e->world.sectors[0].mesh[0].walls[2] = wall_from_triangle((t_vec3d[3]){{{20, 8, -20}}, {{-20, 8, -20}}, {{20, -1, -20}}});
	e->world.sectors[0].mesh[0].walls[3] = wall_from_triangle((t_vec3d[3]){{{-20, 8, -20}}, {{-20, -1, -20}}, {{20, -1, -20}}});
	e->world.sectors[0].mesh[0].walls[4] = wall_from_triangle((t_vec3d[3]){{{20, 8, -20}}, {{20, -1, -20}}, {{20, -1, 20}}});
	e->world.sectors[0].mesh[0].walls[5] = wall_from_triangle((t_vec3d[3]){{{20, 8, 20}}, {{20, 8, -20}}, {{20, -1, 20}}});
	e->world.sectors[0].mesh[0].walls[6] = wall_from_triangle((t_vec3d[3]){{{-20, 8, 20}}, {{20, -1, 20}}, {{-20, -1, 20}}});
	e->world.sectors[0].mesh[0].walls[7] = wall_from_triangle((t_vec3d[3]){{{-20, 8, 20}}, {{20, 8, 20}}, {{20, -1, 20}}});
	e->world.sectors[0].mesh[0].nb_walls = 8;

	e->world.sectors[0].mesh[0].active = TRUE;
	e->world.sectors[0].mesh[1].active = TRUE;
	mat4_init(&e->world.sectors[0].mesh->matrix);
	mat4_init(&e->world.sectors[0].mesh[1].matrix);
	e->world.sectors[0].mesh->polygonnum = 8;
	e->world.sectors[0].mesh->sector_id = -1;
	e->world.sectors[0].mesh->polygons = (t_polygon *)SDL_calloc(sizeof(t_polygon), 8);
	p = e->world.sectors[0].mesh->polygons;
	p[0].v01 = (t_vec4d){.a = {-20, -1, -20, 1}};
	p[0].v12 = (t_vec4d){.a = {-20, -1, 20, 1}};
	p[0].v20 = (t_vec4d){.a = {20, -1, -20, 1}};
	p[0].v01_uv = (t_vec2d){.a = {0, 0}};
	p[0].v12_uv = (t_vec2d){.a = {0, 4}};
	p[0].v20_uv = (t_vec2d){.a = {4, 0}};
	p[0].tex_id = load_texture_from_bmp("assets/textures/lava.bmp", TX_REPEAT);
	p[0].transparency = 0;
	p[1].v01 = (t_vec4d){.a = {-20, -1, 20, 1}};
	p[1].v12 = (t_vec4d){.a = {20, -1, 20, 1}};
	p[1].v20 = (t_vec4d){.a = {20, -1, -20, 1}};
	p[1].v01_uv = (t_vec2d){.a = {0, 4}};
	p[1].v12_uv = (t_vec2d){.a = {4, 4}};
	p[1].v20_uv = (t_vec2d){.a = {4, 0}};
	p[1].tex_id = p[0].tex_id;
	p[1].transparency = 0;
	p[2].v01 = (t_vec4d){.a = {-20, 8, -20, 1}};
	p[2].v12 = (t_vec4d){.a = {-20, -1, -20, 1}};
	p[2].v20 = (t_vec4d){.a = {20, -1, -20, 1}};
	p[2].v01_uv = (t_vec2d){.a = {0, 0}};
	p[2].v12_uv = (t_vec2d){.a = {0, 2}};
	p[2].v20_uv = (t_vec2d){.a = {10, 2}};
	p[2].tex_id = load_texture_from_bmp("assets/textures/redbrick.bmp", TX_REPEAT);
	p[2].transparency = 0;
	p[3].v01 = (t_vec4d){.a = {20, 8, -20, 1}};
	p[3].v12 = (t_vec4d){.a = {-20, 8, -20, 1}};
	p[3].v20 = (t_vec4d){.a = {20, -1, -20, 1}};
	p[3].v01_uv = (t_vec2d){.a = {10, 0}};
	p[3].v12_uv = (t_vec2d){.a = {0, 0}};
	p[3].v20_uv = (t_vec2d){.a = {10, 2}};
	p[3].tex_id = p[2].tex_id;
	p[3].transparency = 0;
	p[4].v01 = (t_vec4d){.a = {20, 8, -20, 1}};
	p[4].v12 = (t_vec4d){.a = {20, -1, -20, 1}};
	p[4].v20 = (t_vec4d){.a = {20, -1, 20, 1}};
	p[4].v01_uv = (t_vec2d){.a = {0, 0}};
	p[4].v12_uv = (t_vec2d){.a = {0, 2}};
	p[4].v20_uv = (t_vec2d){.a = {10, 2}};
	p[4].tex_id = p[2].tex_id;
	p[4].transparency = 0;
	p[5].v01 = (t_vec4d){.a = {20, 8, 20, 1}};
	p[5].v12 = (t_vec4d){.a = {20, 8, -20, 1}};
	p[5].v20 = (t_vec4d){.a = {20, -1, 20, 1}};
	p[5].v01_uv = (t_vec2d){.a = {10, 0}};
	p[5].v12_uv = (t_vec2d){.a = {0, 0}};
	p[5].v20_uv = (t_vec2d){.a = {10, 2}};
	p[5].tex_id = p[2].tex_id;
	p[5].transparency = 0;
	p[6].v01 = (t_vec4d){.a = {-20, 8, 20, 1}};
	p[6].v12 = (t_vec4d){.a = {20, -1, 20, 1}};
	p[6].v20 = (t_vec4d){.a = {-20, -1, 20, 1}};
	p[6].v01_uv = (t_vec2d){.a = {0, 0}};
	p[6].v12_uv = (t_vec2d){.a = {10, 2}};
	p[6].v20_uv = (t_vec2d){.a = {0, 2}};
	p[6].tex_id = p[2].tex_id;
	p[6].transparency = 0;
	p[7].v01 = (t_vec4d){.a = {-20, 8, 20, 1}};
	p[7].v12 = (t_vec4d){.a = {20, 8, 20, 1}};
	p[7].v20 = (t_vec4d){.a = {20, -1, 20, 1}};
	p[7].v01_uv = (t_vec2d){.a = {0, 0}};
	p[7].v12_uv = (t_vec2d){.a = {10, 0}};
	p[7].v20_uv = (t_vec2d){.a = {10, 2}};
	p[7].tex_id = p[2].tex_id;
	p[7].transparency = 0;
	e->world.sectors[0].mesh[1].polygonnum = 2;
	e->world.sectors[0].mesh[1].polygons = (t_polygon *)SDL_calloc(sizeof(t_polygon), 2);
	e->world.sectors[0].mesh[1].sector_id = 1;
	p = e->world.sectors[0].mesh[1].polygons;
	mat4_init(&e->world.sectors[0].mesh[1].matrix);
	p[0].v01 = (t_vec4d){.a = {-20, 8, -20, 1}};
	p[0].v12 = (t_vec4d){.a = {-20, -1, 20, 1}};
	p[0].v20 = (t_vec4d){.a = {-20, -1, -20, 1}};
	p[0].v01_uv = (t_vec2d){.a = {0, 0}};
	p[0].v12_uv = (t_vec2d){.a = {10, 2}};
	p[0].v20_uv = (t_vec2d){.a = {0, 2}};
	p[0].tex_id = load_texture_from_bmp("assets/textures/redbrick.bmp", TX_REPEAT);;
	p[0].transparency = 0;
	p[1].v01 = (t_vec4d){.a = {-20, 8, -20, 1}};
	p[1].v12 = (t_vec4d){.a = {-20, 8, 20, 1}};
	p[1].v20 = (t_vec4d){.a = {-20, -1, 20, 1}};
	p[1].v01_uv = (t_vec2d){.a = {0, 0}};
	p[1].v12_uv = (t_vec2d){.a = {10, 0}};
	p[1].v20_uv = (t_vec2d){.a = {10, 2}};
	p[1].tex_id = load_texture_from_bmp("assets/textures/redbrick.bmp", TX_REPEAT);;
	p[1].transparency = 0;
	e->world.sectors[0].mesh[1].radius = get_mesh_radius(&e->world.sectors[0].mesh[1]);
	e->world.sectors[0].mesh[0].radius = get_mesh_radius(&e->world.sectors[0].mesh[0]);

	e->world.sectors[1].id = 1;
	e->world.sectors[1].lights.light_count = 0;
	e->world.sectors[1].meshnum = 4;
	e->world.sectors[1].mesh = (t_mesh *)SDL_calloc(sizeof(t_mesh), 4);
	e->world.sectors[1].mesh[0].active = TRUE;
	e->world.sectors[1].mesh[1].active = TRUE;
	e->world.sectors[1].mesh[2].active = TRUE;
	e->world.sectors[1].mesh[3].active = TRUE;
	mat4_init(&e->world.sectors[1].mesh->matrix);
	mat4_init(&e->world.sectors[1].mesh[1].matrix);
	mat4_init(&e->world.sectors[1].mesh[2].matrix);
	mat4_init(&e->world.sectors[1].mesh[3].matrix);
	e->world.sectors[1].mesh->polygonnum = 2;
	e->world.sectors[1].mesh->sector_id = -1;
	e->world.sectors[1].mesh->polygons = (t_polygon *)SDL_calloc(sizeof(t_polygon), 2);

	e->world.sectors[1].mesh[0].walls = SDL_calloc(sizeof(t_wall), 2);
	e->world.sectors[1].mesh[0].walls[0] = wall_from_triangle((t_vec3d[3]){{{-60, -1, -20}}, {{-60, -1, 20}}, {{-20, -1, -20}}});
	e->world.sectors[1].mesh[0].walls[0].friction = 0.98;
	e->world.sectors[1].mesh[0].walls[1] = wall_from_triangle((t_vec3d[3]){{{-60, -1, 20}}, {{-20, -1, 20}}, {{-20, -1, -20}}});
	e->world.sectors[1].mesh[0].walls[1].friction = 0.98;
	
	e->world.sectors[1].mesh[0].nb_walls = 2;
	p = e->world.sectors[1].mesh->polygons;
	p[0].v01 = (t_vec4d){.a = {-60, -1, -20, 1}};
	p[0].v12 = (t_vec4d){.a = {-60, -1, 20, 1}};
	p[0].v20 = (t_vec4d){.a = {-20, -1, -20, 1}};
	p[0].v01_uv = (t_vec2d){.a = {0, 0}};
	p[0].v12_uv = (t_vec2d){.a = {0, 4}};
	p[0].v20_uv = (t_vec2d){.a = {4, 0}};
	p[0].tex_id = load_texture_from_bmp("assets/textures/lava.bmp", TX_REPEAT);
	p[0].transparency = 0;
	p[1].v01 = (t_vec4d){.a = {-60, -1, 20, 1}};
	p[1].v12 = (t_vec4d){.a = {-20, -1, 20, 1}};
	p[1].v20 = (t_vec4d){.a = {-20, -1, -20, 1}};
	p[1].v01_uv = (t_vec2d){.a = {0, 4}};
	p[1].v12_uv = (t_vec2d){.a = {4, 4}};
	p[1].v20_uv = (t_vec2d){.a = {4, 0}};
	p[1].tex_id = p[0].tex_id;
	p[1].transparency = 0;
	e->world.sectors[1].mesh[1].sector_id = 0;
	mat4_init(&e->world.sectors[1].mesh[1].matrix);
	e->world.sectors[1].mesh[1].polygonnum = 2;
	e->world.sectors[1].mesh[1].polygons = (t_polygon *)SDL_calloc(sizeof(t_polygon), 2);
	p = e->world.sectors[1].mesh[1].polygons;
	mat4_init(&e->world.sectors[1].mesh[1].matrix);
	p[0].v01 = (t_vec4d){.a = {-20, 8, -20, 1}};
	p[0].v12 = (t_vec4d){.a = {-20, -1, -20, 1}};
	p[0].v20 = (t_vec4d){.a = {-20, -1, 20, 1}};
	p[0].v01_uv = (t_vec2d){.a = {0, 0}};
	p[0].v12_uv = (t_vec2d){.a = {0, 2}};
	p[0].v20_uv = (t_vec2d){.a = {10, 2}};
	p[0].tex_id = load_texture_from_bmp("assets/textures/redbrick.bmp", TX_REPEAT);;
	p[0].transparency = 0;
	p[1].v01 = (t_vec4d){.a = {-20, 8, 20, 1}};
	p[1].v12 = (t_vec4d){.a = {-20, 8, -20, 1}};
	p[1].v20 = (t_vec4d){.a = {-20, -1, 20, 1}};
	p[1].v01_uv = (t_vec2d){.a = {10, 0}};
	p[1].v12_uv = (t_vec2d){.a = {0, 0}};
	p[1].v20_uv = (t_vec2d){.a = {10, 2}};
	p[1].tex_id = load_texture_from_bmp("assets/textures/redbrick.bmp", TX_REPEAT);;
	p[1].transparency = 0;
	e->world.sectors[1].mesh[2].polygonnum = 2;
	e->world.sectors[1].mesh[2].polygons = (t_polygon *)SDL_calloc(sizeof(t_polygon), 2);
	p = e->world.sectors[1].mesh[2].polygons;
	e->world.sectors[1].mesh[2].sector_id = -1;
	mat4_init(&e->world.sectors[1].mesh[2].matrix);
	e->world.sectors[1].mesh[2].matrix = mat4_translate(e->world.sectors[1].mesh[2].matrix, -40, 0, 0);
	e->world.sectors[1].mesh[2].matrix = mat4_rotate_pitch(e->world.sectors[1].mesh[2].matrix, 270);
	p[0].v01 = (t_vec4d){.a = {-5, 8, -5, 1}};
	p[0].v12 = (t_vec4d){.a = {-5, -1, -5, 1}};
	p[0].v20 = (t_vec4d){.a = {5, -1, -5, 1}};
	p[0].v01_uv = (t_vec2d){.a = {0, 0}};
	p[0].v12_uv = (t_vec2d){.a = {0, 2}};
	p[0].v20_uv = (t_vec2d){.a = {2, 2}};
	p[0].tex_id = load_texture_from_bmp("assets/textures/redbrick.bmp", TX_REPEAT);
	p[0].transparency = 150;
	p[1].v01 = (t_vec4d){.a = {5, 8, -5, 1}};
	p[1].v12 = (t_vec4d){.a = {-5, 8, -5, 1}};
	p[1].v20 = (t_vec4d){.a = {5, -1, -5, 1}};
	p[1].v01_uv = (t_vec2d){.a = {2, 0}};
	p[1].v12_uv = (t_vec2d){.a = {0, 0}};
	p[1].v20_uv = (t_vec2d){.a = {2, 2}};
	p[1].tex_id = p[0].tex_id;
	p[1].transparency = 150;
	e->world.sectors[1].mesh[3].polygonnum = 2;
	e->world.sectors[1].mesh[3].polygons = (t_polygon *)SDL_calloc(sizeof(t_polygon), 2);
	p = e->world.sectors[1].mesh[3].polygons;
	e->world.sectors[1].mesh[3].sector_id = -1;
	mat4_init(&e->world.sectors[1].mesh[3].matrix);
	e->world.sectors[1].mesh[3].matrix = mat4_translate(e->world.sectors[1].mesh[3].matrix, -30, 0, 5);
	e->world.sectors[1].mesh[3].matrix = mat4_rotate_pitch(e->world.sectors[1].mesh[3].matrix, 270);
	p[0].v01 = (t_vec4d){.a = {-5, 8, -5, 1}};
	p[0].v12 = (t_vec4d){.a = {-5, -1, -5, 1}};
	p[0].v20 = (t_vec4d){.a = {5, -1, -5, 1}};
	p[0].v01_uv = (t_vec2d){.a = {0, 0}};
	p[0].v12_uv = (t_vec2d){.a = {0, 2}};
	p[0].v20_uv = (t_vec2d){.a = {2, 2}};
	p[0].tex_id = load_texture_from_bmp("assets/textures/redbrick.bmp", TX_REPEAT);
	p[0].transparency = 150;
	p[1].v01 = (t_vec4d){.a = {5, 8, -5, 1}};
	p[1].v12 = (t_vec4d){.a = {-5, 8, -5, 1}};
	p[1].v20 = (t_vec4d){.a = {5, -1, -5, 1}};
	p[1].v01_uv = (t_vec2d){.a = {2, 0}};
	p[1].v12_uv = (t_vec2d){.a = {0, 0}};
	p[1].v20_uv = (t_vec2d){.a = {2, 2}};
	p[1].tex_id = p[0].tex_id;
	p[1].transparency = 150;
	e->world.sectors[1].mesh[2].radius = get_mesh_radius(&e->world.sectors[1].mesh[2]);
	e->world.sectors[1].mesh[1].radius = get_mesh_radius(&e->world.sectors[1].mesh[1]);
	e->world.sectors[1].mesh[0].radius = get_mesh_radius(&e->world.sectors[1].mesh[0]);
	e->world.sectors[1].mesh[3].radius = get_mesh_radius(&e->world.sectors[1].mesh[3]);

	e->world.sectors[0].lights.light_count = 1;
	e->world.sectors[0].lights.lights = (t_light *)SDL_calloc(sizeof(t_light), 1);
	e->world.sectors[0].lights.lights[0].type = POINT_LIGHT;
	e->world.sectors[0].lights.lights[0].pos_o.a[0] = 8;
	e->world.sectors[0].lights.lights[0].pos_o.a[1] = 5;
	e->world.sectors[0].lights.lights[0].pos_o.a[2] = -10;
	e->world.sectors[0].lights.lights[0].pos_o.a[3] = 1;
	e->world.sectors[0].lights.lights[0].intensity = 300;
	e->world.sectors[0].lights.lights[0].dir.a[0] = 0;
	e->world.sectors[0].lights.lights[0].dir.a[1] = 0.3;
	e->world.sectors[0].lights.lights[0].dir.a[2] = 0.7;
	mat4_init(&e->world.sectors[0].lights.lights[0].mat);
	e->world.sectors[0].lights.lights[0].fallof = 5;
	e->world.sectors[1].lights.lights = NULL;
	e->world.sectors[1].lights.light_count= 0;
	skybox_load(&e->world, "assets/skybox/skybox2.bmp");
*/
	e->editor.item_placer = obj_to_mesh(object_manager_get_obj("assets/objects/house.obj"), "assets/textures/redbrick.bmp", TX_CLAMP_EDGES);
	e->editor.is_object = FALSE;
	// printf("objects loaded: %d\n", get_object_list()->size);
}

#include <physic.h>

int main()
{
	t_e		env;

	env.world = (t_world){};
	libui_init();
	set_world(&env.world);
	env.world.skybox = NULL;
	env.world.sectornum = 0;
	init_test_world(&env);
	if (!(init_world(&env.world)))
		return (FALSE);
	if (!(env_init(&env)))
		return (-1);
	init_player(&env.main_player, &env.world);
	launch_main_menu(&env);
	//load threads
	//run func (state manager or whatever the fuck you want to call it!
	//unload funcs
	//destroy funcs
	env_destroy(&env);
	libui_close();
	return (0);
}
