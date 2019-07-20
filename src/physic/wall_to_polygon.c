#include <physic.h>
#include <world.h>

t_polygon	wall_to_polygon(t_wall wall, int tex_id)
{
	return ((t_polygon){
		.v01 = {wall.vertices[0].x, wall.vertices[0].y, wall.vertices[0].z, 0.},
		.v12 = {wall.vertices[1].x, wall.vertices[1].y, wall.vertices[1].z, 0.},
		.v20 = {wall.vertices[2].x, wall.vertices[2].y, wall.vertices[2].z, 0.},
		.normal = {wall.normal.x, wall.normal.y, wall.normal.z},
		.v01_uv = {0., 0.}, .v12_uv = {0., 0.}, .v20_uv = {0., 0.},
		.v_light = {0., 0., 0.}, .tex_id = tex_id, .transparency = 0});
}
