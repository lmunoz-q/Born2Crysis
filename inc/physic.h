/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physic.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 21:01:54 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/08/25 14:44:43 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHYSIC_H
# define PHYSIC_H

# include <libui.h>
# include <mflib.h>
# include <typedefs.h>

/*
** typedef t_wall:
** where v0, v1 and v2 are the vertices of the triangle in 3d space
** centroid of a triangle: c = (v0 + v1 + v2) / 3
** radius of a triangle: r = max(abs(v0 - c), abs(v1 - c), abs(v2 - c))
** normal of a triangle: n = norm(cross(v1 - v0, v2 - v0))
** type: if abs(n.y) < WALL_TOLERANCE
**   then abs(n.x) > abs(n.z) ? WT_WALL_X : WT_WALL_Z
**   else n.y > 0 ? WT_FLOOR : WT_CEIL
** all informations of the wall can be reconstructed only based on the vertices
** switching the side of the wall is as easy as switching the v1 and v2
*/

/*
** typedef struct				s_wall static in world, might change in object
** {
** t_double3		vertices[3];
** t_double3		normal;
** t_double3		center;
** double			radius;
** }								t_wall;
*/

typedef struct					s_wall //static in world, might change in object
{
	t_vec3d						vertices[3];
	t_vec3d						normal;
	t_vec3d						center;
	double						radius;
	double						friction; //friction to apply on entity while in contact
	Uint32						on_contact_trigger; //action to call on trigger
}								t_wall;

/*
** foreach entity check it's proximity to a wall
*/
typedef struct s_entity			t_entity;

typedef enum					e_entity_flags
{
	EF_CLIP = 0b1, //will walls push this entity
	EF_GRAVITY = 0b10, //will gravity affect this entity
	EF_FRICTION = 0b100, //will friction affect this entity
	EF_ACTIVATE = 0b1000 //will the wall trigger effect on contact
}								t_entity_flags;

struct							s_entity
{
	t_entity_flags				flags;
	t_vec3d						position;
	t_vec3d						look;
	t_vec3d						velocity;
	Uint32						can_jump : 1;
	Uint32						can_go_up : 1;
	Uint32						can_go_down : 1;
	t_wall						*wall_contacts[8]; //references to the first 8 walls actively touching the entity
	t_entity					*entities_overlap[8]; //references to the first 8 entities actively touching the entity
	double						radius;
	double						height;
	t_sector					*sector;
	t_vec3d						vertices[8]; //mesh of the entity, created on the fly
};

typedef enum					e_player_stature
{
	PSE_NORMAL, //h: 1m80, r: 0m25
	PSE_CROUCH, //h: 1m00, r: 0m35
	// PSE_SNAKE   //h: 0m50, r: 0m75
}								t_player_stature;

typedef struct					s_player_entity
{
	t_entity					body; //floor/wall detection
	t_entity					wall_detection; //special actions
	t_player_stature			pse;
}								t_player_entity;

typedef struct					s_sector_physics
{
	t_vec3d						gravity;
	double						speed_limit;
	t_vec3d						global_friction;
	t_vec3d						drag;
	Uint32						frame_effect;
	Uint32						entering_effet;
	Uint32						leaving_effect;
}								t_sector_physics;

/*
** example of a sector with space like physics:
** {.gravity={{0,0,0}},.speed_limit={{4,4,4}},.global_friction={{1,1,1}}}
** example of a sector with normal physics:
** {.gravity={{-1.2,0,0}},.speed_limit={{3,3,3}},.global_friction={{0.9,1,0.9}}}
*/

/*
**typedef struct					s_physics_handler
**{
**	size_t						nb_entities;
**	t_entity					*entities; //contain all the entities
**								in the world
**	size_t						max_wall_handlers;
**	size_t						active_wall_handlers;
**	t_wall_handler				*wall_handlers;
**}								t_physics_handler;
*/

/*
** order:
** first we load all the walls of the sector the entity is in
** then we verify if the entity is near the planes using the center+radius
** then for each near plane, we project the player on the triangle
** then we test if the point is within the extrusion of the triangle
** once done for all near planes, calculate the new position
*/

/*
** if Y is within [-WALL_TOLERANCE, WALL_TOLERANCE] then the triangle is a wall
** (a ceiling or floor otherwise)
*/

# define WALL_TOLERANCE 0.05

/*
** example: wall 123 normal toward X (456 displacement of 123 on the X axis)
*/

/*
**              Z
**              |
**            1---4
**           /  |/
**          /   /
**         / P /|
** X------/---/-Y
**       /   /
**      2---5
*/

/*
**              Y
**              |
**            1 |
**           /| |
**          / | |
**         / P| |
** Z------/---|-X
**       /    |
**      3-----2
*/

/*
** entity vs entity collision is done via cylinders aligned on the Y axis so if
** the Y ranges match, the collision is as simple as a circle collision on a
** plane (d <= r1 + r2)
*/

/*
** new method derivated from mario64 (might be beter and modular):
** the extrusion is adaptative based on the Y component of the normal
** of the wall
** Y+: floor
** Y0: wall
** Y-: ceiling
** for each angle of the normal, the extrusion is moved along the normal,
** ceiling and floor the extrusion is behind the wall and pushes
** on the foot/head
** the closer to Y 0 the thicker the extrusion in front of the wall
** detection of inclusion is done via projection of the point on the wall and
** inclusion in the triangle (3 dot product in the same orientation)
** the distance between the projected point and the original point gives
** the penetration depth
** this way, the collision detection is standardised, and the only changing
** component is the amount of correction on Y0 for various entities sizes
** this method allow free axis corection (instead of XYZ aligned correction),
** meaning ramps + gravity might be able to create movement without user
** input (gravity pushe downward, correction pushes in diagonal,
** resuting in movement)
*/

/*
** first project the point on the plane of the triangle (p - (n . (p - o)) * n)
** then test if the projected point is inside the triangle (triple dot == sign)
** then test the magnitude of the vector going from the point to the projection
** (p' - p)
** if the magnitude is positive and > treshold, the movement is outside the hit
** if the magnitude is positive and < treshold or negative, the point hit (and
** potentially phased)
** int	point_in_extruded_wall(t_vec3d point, t_wall wall, t_vec2d extrusion,
** double *correction);
*/

t_vec3d							entity_accelerate(t_entity e, t_vec3d a);

t_vec3d							ssv_seg_seg(t_vec3d s1a, t_vec3d s1b,
											t_vec3d s2a, t_vec3d s2b);
int								collision_capsule_wall(t_vec3d *sep,
											t_vec3d cl[2], double r, t_wall w);

double							entity_wall_collision(t_entity original,
								t_entity ent, t_wall wall, double *correction);
t_wall							wall_from_triangle(t_vec3d triangle[3], t_mat4d mat);

t_bool      collision_raysphere(t_vec3d ray_a, t_vec3d ray_p, t_vec3d sphere, double radius);

#endif
