#include <doom-nukem.h>
#include <world.h>

int	update_entity_against_mesh(t_entity *proj, t_world *world, t_entity *ent, t_mesh *mesh)
{
	int			it;
	t_vec4d		c;
	double		cor;
	t_wall		wall;
	int			type;

	(void)world;
	(void)ent;
	it = -1;
	if (mesh->walls == NULL)
		return (0);
//	printf("testing %d walls\n", mesh->nb_walls);
	while (++it < mesh->nb_walls)
	{
		c = (t_vec4d){.c3 = {.vec3d = mesh->walls[it].center, .w = 1}};
		c.c3.vec3d = vec3vec3_substract(mat4vec4_multiply(mesh->matrix, c).c3.vec3d, proj->position);
		if (c.n.x * c.n.x + c.n.y * c.n.y + c.n.z * c.n.z
				<= mesh->walls[it].radius * mesh->walls[it].radius)
		{
//			printf("in radius of wall, normal: %f %f %f, vertices:%f %f %f, %f %f %f, %f %f %f\n", mesh->walls[it].normal.n.x, mesh->walls[it].normal.n.y, mesh->walls[it].normal.n.z, mesh->walls[it].vertices[0].n.x, mesh->walls[it].vertices[0].n.y, mesh->walls[it].vertices[0].n.z, mesh->walls[it].vertices[1].n.x, mesh->walls[it].vertices[1].n.y, mesh->walls[it].vertices[1].n.z, mesh->walls[it].vertices[2].n.x, mesh->walls[it].vertices[2].n.y, mesh->walls[it].vertices[2].n.z);
			wall.normal = mat4vec4_multiply(mesh->matrix, (t_vec4d){.c3 = {.vec3d = mesh->walls[it].normal}}).c3.vec3d;
			wall.vertices[0] = mat4vec4_multiply(mesh->matrix, (t_vec4d){.c3 = {mesh->walls[it].vertices[0], 1}}).c3.vec3d;
			wall.vertices[1] = mat4vec4_multiply(mesh->matrix, (t_vec4d){.c3 = {mesh->walls[it].vertices[1], 1}}).c3.vec3d;
			wall.vertices[2] = mat4vec4_multiply(mesh->matrix, (t_vec4d){.c3 = {mesh->walls[it].vertices[2], 1}}).c3.vec3d;
			wall.center = mat4vec4_multiply(mesh->matrix, (t_vec4d){.c3 = {mesh->walls[it].center, 1}}).c3.vec3d;
			wall.radius = mesh->walls[it].radius;
//			printf("  after transform, normal: %f %f %f, vertices:%f %f %f, %f %f %f, %f %f %f\n", wall.normal.n.x, wall.normal.n.y, wall.normal.n.z, wall.vertices[0].n.x, wall.vertices[0].n.y, wall.vertices[0].n.z, wall.vertices[1].n.x, wall.vertices[1].n.y, wall.vertices[1].n.z, wall.vertices[2].n.x, wall.vertices[2].n.y, wall.vertices[2].n.z);
			if ((type = entity_wall_collision(*proj, wall, &cor)))
			{
//				printf("\ncollision found\n\n");
				
				proj->position = vec3vec3_add(proj->position, vec3scalar_multiply(mesh->walls[it].normal, cor));
				if (type == 1)
				{
					proj->velocity.n.y = 0;
					proj->onground = TRUE;
				}
				if (type == 2)
				{
					proj->velocity.n.y += (D_GRAVITY * DELTATIME);
					proj->onground = TRUE;
				}
				if (type == 4)
				{
					if (proj->velocity.n.y > 0.0)
						proj->velocity.n.y = 0.0;
				}
				if (type == 5)
				{
					if (proj->velocity.n.y > 0.0)
						proj->velocity.n.y = 0.0;
				}
			}
		}
	}
	return (0);
}

t_entity	basic_physics(t_entity e)
{
	// printf("base velocity: %f %f %f\n", e.velocity.n.x, e.velocity.n.y, e.velocity.n.z);
	e.position = vec3vec3_add(e.position, e.velocity);
	e.velocity.a[1] -= (D_GRAVITY * DELTATIME);
	e.velocity.a[0] *= DEFAULT_FRICTION;
	e.velocity.a[2] *= DEFAULT_FRICTION;
	// printf("new velocity: %f %f %f\n", e.velocity.n.x, e.velocity.n.y, e.velocity.n.z);
	return (e);
}

int	update_entity(t_world *world, t_entity *ent)
{
	t_entity	proj;
	t_sector	*sector;
	int			it;
	t_vec3d		or;

	if ((sector = get_sector(ent->sector, world)) == NULL)
		return (0);
	proj = basic_physics(*ent);/*vec3vec3_add(ent->position, vec3scalar_multiply(ent->velocity, DELTATIME));*/
	or = proj.position;
	// printf("projected position: %f %f %f\n", or.n.x, or.n.y, or.n.z);
	it = -1;
	while (++it < sector->objectnum)
		update_entity_against_mesh(&proj, world, ent, sector->objects[it].mesh);
	it = -1;
	while (++it < sector->meshnum)
		update_entity_against_mesh(&proj, world, ent, &sector->mesh[it]);
	*ent = proj;
	// ent->position = or;
	return (proj.position.n.x != or.n.x || proj.position.n.y != or.n.y || proj.position.n.z != or.n.z);
}
