#include <doom-nukem.h>
#include <world.h>

// int	update_entity_against_entity(t_double3 *proj, t_world *world, t_entity *ent, t_entity *col)
// {
//
// }

void	mat4d3_multiply_0(double mat[4][4], t_double3 in, t_double3 *out)
{
	double	t[4];

	t[0] = in.x;
	t[1] = in.y;
	t[2] = in.z;
	t[3] = 0.;
	mat4vec4_multiply(mat, t, t);
	vec4_normalize_s(t);
	out->x = t[0];
	out->y = t[1];
	out->z = t[2];
}

void	mat4d3_multiply_1(double mat[4][4], t_double3 in, t_double3 *out)
{
	double	t[4];

	t[0] = in.x;
	t[1] = in.y;
	t[2] = in.z;
	t[3] = 1.;
	mat4vec4_multiply(mat, t, t);
	out->x = t[0];
	out->y = t[1];
	out->z = t[2];
}

int	update_entity_against_mesh(t_double3 *proj, t_world *world, t_entity *ent, t_mesh *mesh)
{
	int			it;
	double		c[4];
	t_double3	ct;
	double		cor;
	t_wall		wall;

	(void)world;
	(void)ent;
	it = -1;
	if (mesh->walls == NULL)
		return (0);
	while (++it < mesh->nb_walls)
	{
		ct = mesh->walls[it].center;
		c[0] = ct.x;
		c[1] = ct.y;
		c[2] = ct.z;
		c[3] = 1.;
		mat4vec4_multiply(mesh->matrix, c, c);
		c[0] -= proj->x;
		c[1] -= proj->y;
		c[2] -= proj->z;
		if (c[0] * c[0] + c[1] * c[1] + c[2] * c[2]
				<= mesh->walls[it].radius * mesh->walls[it].radius)
		{
			mat4d3_multiply_0(mesh->matrix, mesh->walls[it].normal, &wall.normal);
			mat4d3_multiply_1(mesh->matrix, mesh->walls[it].vertices[0], &wall.vertices[0]);
			mat4d3_multiply_1(mesh->matrix, mesh->walls[it].vertices[1], &wall.vertices[1]);
			mat4d3_multiply_1(mesh->matrix, mesh->walls[it].vertices[2], &wall.vertices[2]);
			if (point_in_extruded_wall(*proj, wall, (t_double2){10, 0}, &cor))
				*proj = d3_add(*proj, d3_scale(mesh->walls[it].normal, cor));
		}
	}
	return (0);
}

int	update_entity(t_world *world, t_entity *ent)
{
	t_double3	proj;
	t_sector	*sector;
	int			it;
	t_double3	or;

	if ((sector = get_sector(ent->sector, world)) == NULL)
		return (0);
	proj = d3_add(ent->position, d3_scale(ent->velocity, DELTATIME));
	printf("projected position: %f %f %f\n", proj.x, proj.y, proj.z);
	or = proj;
	it = -1;
	while (++it < sector->objectnum)
		update_entity_against_mesh(&proj, world, ent, sector->objects[it].mesh);
	it = -1;
	while (++it < sector->meshnum)
		update_entity_against_mesh(&proj, world, ent, &sector->mesh[it]);
	ent->position = proj;
	return (proj.x != or.x || proj.y != or.y || proj.z != or.z);
}
