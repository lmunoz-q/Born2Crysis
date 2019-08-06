#include <doom-nukem.h>
#include <world.h>

//int	update_entity_against_entity(t_double3 *proj, t_world *world, t_entity *ent, t_entity *col)
//{
//
//}
//
//void	mat4d3_multiply_0(double mat[4][4], t_double3 in, t_double3 *out)
//{
//	double	t[4];
//
//	t[0] = in.x;
//	t[1] = in.y;
//	t[2] = in.z;
//	t[3] = 0.;
//	mat4vec4_multiply(mat, t, t);
//	vec4_normalize_s(t);
//	out->x = t[0];
//	out->y = t[1];
//	out->z = t[2];
//}
//
//void	mat4d3_multiply_1(double mat[4][4], t_double3 in, t_double3 *out)
//{
//	double	t[4];
//
//	t[0] = in.x;
//	t[1] = in.y;
//	t[2] = in.z;
//	t[3] = 1.;
//	mat4vec4_multiply(mat, t, t);
//	out->x = t[0];
//	out->y = t[1];
//	out->z = t[2];
//}

int	update_entity_against_mesh(t_vec3d *proj, t_world *world, t_entity *ent, t_mesh *mesh)
{
	int			it;
	t_vec4d		c;
//	double		cor;
//	t_wall		wall;

	(void)proj;
	(void)world;
	(void)ent;
	it = -1;
	if (mesh->walls == NULL)
		return (0);
	while (++it < mesh->nb_walls)
	{
		c = (t_vec4d){.c3 = {.vec3d = mesh->walls[it].center, .w = 1}};
		c.c3.vec3d = vec3vec3_substract(mat4vec4_multiply(mesh->matrix, c).c3.vec3d, *proj);
		if (c.n.x * c.n.x + c.n.y * c.n.y + c.n.z * c.n.z
				<= mesh->walls[it].radius * mesh->walls[it].radius)
		{
//			wall.normal = mat4vec4_multiply(mesh->matrix, (t_vec4d){.vec3d = mesh->walls[it].normal}).vec3d;
//			mat4d3_multiply_1(mesh->matrix, mesh->walls[it].vertices[0], &wall.vertices[0]);
//			mat4d3_multiply_1(mesh->matrix, mesh->walls[it].vertices[1], &wall.vertices[1]);
//			mat4d3_multiply_1(mesh->matrix, mesh->walls[it].vertices[2], &wall.vertices[2]);
//			if (point_in_extruded_wall(*proj, wall, (t_double2){10, 0}, &cor))
//				*proj = d3_add(*proj, d3_scale(mesh->walls[it].normal, cor));
		}
	}
	return (0);
}

int	update_entity(t_world *world, t_entity *ent)
{
	t_vec3d		proj;
	t_sector	*sector;
	int			it;
	t_vec3d		or;

	if ((sector = get_sector(ent->sector, world)) == NULL)
		return (0);
	proj = vec3vec3_add(ent->position, vec3scalar_multiply(ent->velocity, DELTATIME));
	printf("projected position: %f %f %f\n", proj.n.x, proj.n.y, proj.n.z);
	or = proj;
	it = -1;
	while (++it < sector->objectnum)
		update_entity_against_mesh(&proj, world, ent, sector->objects[it].mesh);
	it = -1;
	while (++it < sector->meshnum)
		update_entity_against_mesh(&proj, world, ent, &sector->mesh[it]);
	ent->position = proj;
	return (proj.n.x != or.n.x || proj.n.y != or.n.y || proj.n.z != or.n.z);
}
