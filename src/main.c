# include "doom-nukem.h"


void	init_test_world(t_e *e)
{
	SDL_Surface *img = libui_surface_image_load_32argb("test.bmp", 64, 64);
	t_polygon	*new;
	e->world.sectornum = 1;
	e->world.sectors = (t_sector *)malloc(sizeof(t_sector));
	e->world.sectors->id = 0;
	e->world.sectors->objectnum = 0;
	e->world.sectors->surfacenum = 1;
	e->world.sectors->surfaces = (t_surface *)malloc(sizeof(t_surface));
	mat4_init(e->world.sectors->surfaces->matrix);
	e->world.sectors->surfaces->next_sector_id = NULL;
	new = (t_polygon *)malloc(sizeof(t_polygon));
	new->is_clipped = FALSE;
	new->preloaded_normal = FALSE;
	new->v_light[0] = 1;
	new->v_light[1] = 0.6;
	new->v_light[2] = 0.2;
	new->v01_o = (double [4]){-1, 1, 1, 1};
	new->v12_o = (double [4]){1, 1, 1, 1};
	new->v20_o = (double [4]){1, -1, 1, 1};
	new->v01_uv = (double [2]){0, 1};
	new->v12_uv = (double [2]){1, 1};
	new->v20_uv = (double [2]){1, 0};
	new->texture = img;
	list2_push(e->world.sectors->surfaces->polygons, new);
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
