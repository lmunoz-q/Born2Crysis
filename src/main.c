# include "doom-nukem.h"

/*
** TEMPORARY TESTS DO NOT TOUCH OR MAREK WILL SPANK YOU!
*/
void	init_test_world(t_e *e)
{
	t_polygon *p;

	e->world.sectornum = 1;
	e->world.sectors = (t_sector *)malloc(sizeof(t_sector));
	e->world.sectors->id = 0;
	e->world.sectors->objectnum = 0;
	e->world.sectors->meshnum = 1;
	e->world.sectors->mesh = (t_mesh *)malloc(sizeof(t_mesh));
	mat4_init(e->world.sectors->mesh->matrix);
	//mat4_rotate_pitch(e->world.sectors->mesh->matrix, 180.0);
	//mat4_scale(e->world.sectors->mesh->matrix, 0.1, 0.1, 0.1);
	mat4_translate(e->world.sectors->mesh->matrix, 0, 0, 2);
	e->world.sectors->mesh->polygonnum = 1;
	e->world.sectors->mesh->polygons = (t_polygon *)malloc(sizeof(t_polygon));
	p = e->world.sectors->mesh->polygons;
	vec4_copy(p[0].v01, (double [4]){-1, 1, 1, 1});
	vec4_copy(p[0].v12, (double [4]){1, 1, 1, 1});
	vec4_copy(p[0].v20, (double [4]){1, -1, 1, 1});
	vec2_copy(p[0].v01_uv, (double [2]){0, 1});
	vec2_copy(p[0].v12_uv, (double [2]){1, 1});
	vec2_copy(p[0].v20_uv, (double [2]){1, 0});
	p->tex_id = load_texture_from_bmp("assets/lava.bmp", TX_REPEAT);
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
