# include "doom-nukem.h"

/*
** TEMPORARY TESTS DO NOT TOUCH OR MAREK WILL SPANK YOU!
*/
void	init_test_world(t_e *e)
{
	t_obj *tmp;
	SDL_Surface *img = libui_surface_image_load_32argb("test.bmp", 64, 64);
	SDL_Surface *img2 = libui_surface_image_load_32argb("test2.bmp", 64, 64);
	t_polygon	*new;
	e->world.sectornum = 1;
	e->world.sectors = (t_sector *)malloc(sizeof(t_sector));
	e->world.sectors->id = 0;
	e->world.sectors->objectnum = 0;
	e->world.sectors->surfacenum = 1;
	e->world.sectors->surfaces = (t_surface *)malloc(sizeof(t_surface));
	mat4_init(e->world.sectors->surfaces->matrix);
	mat4_scale(e->world.sectors->surfaces->matrix, 3, 6, 6);
	e->world.sectors->surfaces->next_sector_id = -1;
	tmp = load_obj("assets/house.obj");
	if ((e->world.sectors->objects = obj_to_object(tmp, "house_tex.bmp", 1024, 1024)))
	{
		e->world.sectors->objectnum++;
		mat4_scale(e->world.sectors->objects->matrix, 0.2, 0.2, 0.2);
		//mat4_rotate_yaw(e->world.sectors->objects->matrix, -90);
		mat4_translate(e->world.sectors->objects->matrix, 4, -10, -100);
	}
	new = (t_polygon *)malloc(sizeof(t_polygon));
	*new = (t_polygon){.is_clipped = FALSE, .preloaded_normal = FALSE,
	.v_light = {0, 0.2, 0.5}, .v01_o = {-1, 1, -1, 1}, .v12_o = {1, 1, -1, 1},
	.v20_o = {1, -1, -1, 1}, .v01_uv_o = {1, 0}, .v12_uv_o = {0, 0}, .v20_uv_o = {0, 1}, .texture = img2};
	e->world.sectors[0].surfaces[0].polygons = list2_create();
	list2_push(e->world.sectors[0].surfaces[0].polygons, new);
	new = (t_polygon *)malloc(sizeof(t_polygon));
	*new = (t_polygon){.is_clipped = FALSE, .preloaded_normal = FALSE,
	.v_light = {0, 0.5, 0.2}, .v01_o = {-1, 1, -1, 1}, .v12_o = {1, -1, -1, 1},
	.v20_o = {-1, -1, -1, 1}, .v01_uv_o = {1,0}, .v12_uv_o = {0, 1}, .v20_uv_o = {1, 1}, .texture = img2};
	list2_push(e->world.sectors[0].surfaces[0].polygons, new);

	new = (t_polygon *)malloc(sizeof(t_polygon));
	*new = (t_polygon){.is_clipped = FALSE, .preloaded_normal = FALSE,
	.v_light = {0, 0.2, 0.5}, .v01_o = {1, 1, 1, 1}, .v12_o = {1, -1, 1, 1},
	.v20_o = {1, 1, -1, 1}, .v01_uv_o = {1, 0}, .v12_uv_o = {1, 1}, .v20_uv_o = {0, 0}, .texture = img};
	list2_push(e->world.sectors[0].surfaces[0].polygons, new);
	new = (t_polygon *)malloc(sizeof(t_polygon));
	*new = (t_polygon){.is_clipped = FALSE, .preloaded_normal = FALSE,
	.v_light = {0, 0.5, 0.2}, .v01_o = {1, -1, 1, 1}, .v12_o = {1, -1, -1, 1},
	.v20_o = {1, 1, -1, 1}, .v01_uv_o = {1,1}, .v12_uv_o = {0, 1}, .v20_uv_o = {0, 0}, .texture = img};
	list2_push(e->world.sectors[0].surfaces[0].polygons, new);

	new = (t_polygon *)malloc(sizeof(t_polygon));
	*new = (t_polygon){.is_clipped = FALSE, .preloaded_normal = FALSE,
	.v_light = {0, 0.2, 0.5}, .v01_o = {6, -1, 1, 1}, .v12_o = {6, 1, 1, 1},
	.v20_o = {6, 1, -1, 1}, .v01_uv_o = {1, 1}, .v12_uv_o = {1, 0}, .v20_uv_o = {0, 0}, .texture = img};
	list2_push(e->world.sectors[0].surfaces[0].polygons, new);
	new = (t_polygon *)malloc(sizeof(t_polygon));
	*new = (t_polygon){.is_clipped = FALSE, .preloaded_normal = FALSE,
	.v_light = {0, 0.5, 0.2}, .v01_o = {6, -1, -1, 1}, .v12_o = {6, -1, 1, 1},
	.v20_o = {6, 1, -1, 1}, .v01_uv_o = {0,1}, .v12_uv_o = {1, 1}, .v20_uv_o = {0, 0}, .texture = img};
	list2_push(e->world.sectors[0].surfaces[0].polygons, new);

	new = (t_polygon *)malloc(sizeof(t_polygon));
	*new = (t_polygon){.is_clipped = FALSE, .preloaded_normal = FALSE,
	.v_light = {0, 0.2, 0.5}, .v01_o = {6, 1, -1, 1}, .v12_o = {8, 1, -1, 1},
	.v20_o = {8, -1, -1, 1}, .v01_uv_o = {1, 0}, .v12_uv_o = {0, 0}, .v20_uv_o = {0, 1}, .texture = img2};
	list2_push(e->world.sectors[0].surfaces[0].polygons, new);
	new = (t_polygon *)malloc(sizeof(t_polygon));
	*new = (t_polygon){.is_clipped = FALSE, .preloaded_normal = FALSE,
	.v_light = {0, 0.5, 0.2}, .v01_o = {6, 1, -1, 1}, .v12_o = {8, -1, -1, 1},
	.v20_o = {6, -1, -1, 1}, .v01_uv_o = {1,0}, .v12_uv_o = {0, 1}, .v20_uv_o = {1, 1}, .texture = img2};
	list2_push(e->world.sectors[0].surfaces[0].polygons, new);
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
