#ifndef PHYSIC_H
# define PHYSIC_H

# include <libui.h>
# include <mflib.h>

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

// typedef struct					s_wall //static in world, might change in object
// {
// t_double3		vertices[3];
// t_double3		normal;
// t_double3		center;
// double			radius;
// }								t_wall;

typedef struct					s_wall //static in world, might change in object
{
	double			vertices[3][3];
	double			normal[3];
	double			center[3];
	double			radius;
}								t_wall;

typedef struct					s_colyder
{
	t_wall	*wall;
	double	force;
}								t_colyder;

/*
** foreach entity check it's proximity to a wall
*/
typedef struct s_entity			t_entity;

typedef enum					e_entity_type
{
	ET_PLAYER
}								t_entity_type;

typedef enum					e_entity_standing_status
{
	ESS_NORMAL, //moving, standing
	ESS_FALL,   //free fall, jump
	ESS_FLY     //fly, swim
}								t_entity_standing_status;

struct							s_entity
{
	t_entity_type				type;
	t_entity_standing_status	ess;
	t_double3					position;
	t_double3					look;
	t_double3					velocity;
	double						radius;
	double						height;
	int							sector;
};

typedef enum					e_player_stature
{
	PSE_NORMAL, //h: 1m80, r: 0m25
	PSE_CROUSH, //h: 1m00, r: 0m35
	PSE_SNAKE   //h: 0m50, r: 0m75
}								t_player_stature;

typedef struct					s_player_entity
{
	t_entity			feet; //floor/wall detection
	double				belt; //wall run/kick
	double				neck; //wall grab/climb
	double				top;  //ceiling detection
	t_player_stature	pse;
}								t_player_entity;

/*
typedef struct					s_physics_handler
{
	size_t						nb_entities;
	t_entity					*entities; //contain all the entities in the world
	size_t						max_wall_handlers;
	size_t						active_wall_handlers;
	t_wall_handler				*wall_handlers;
}								t_physics_handler;
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
** the extrusion is adaptative based on the Y component of the normal of the wall
** Y+: floor
** Y0: wall
** Y-: ceiling
** for each angle of the normal, the extrusion is moved along the normal, ceiling and floor the extrusion is behind the wall and pushes on the foot/head
** the closer to Y 0 the thicker the extrusion in front of the wall
** detection of inclusion is done via projection of the point on the wall and inclusion in the triangle (3 dot product in the same orientation)
** the distance between the projected point and the original point gives the penetration depth
** this way, the collision detection is standardised, and the only changing component is the amount of correction on Y0 for various entities sizes
** this method allow free axis corection (instead of XYZ aligned correction), meaning ramps + gravity might be able to create movement without user input (gravity pushe downward, correction pushes in diagonal, resuting in movement)
*/

/*
** first project the point on the plane of the triangle (p - (n . (p - o)) * n)
** then test if the projected point is inside the triangle (triple dot == sign)
** then test the magnitude of the vector going from the point to the projection (p' - p)
** if the magnitude is positive and > treshold, the movement is outside the hit
** if the magnitude is positive and < treshold or negative, the point hit (and
** potentially phased)
*/

t_double3	d3_add(t_double3 a, t_double3 b);

t_double3	d3_substract(t_double3 a, t_double3 b);

t_double3	d3_scale(t_double3 v, double s);

double		d3_magnitude(t_double3 v);

double		d3_squared_magnitude(t_double3 v);

 int	point_in_extruded_wall(t_double3 point, t_wall wall, t_double2 extrusion, double *correction);
//int	point_in_extruded_wall(double point[3], t_wall wall, double extrusion[2], double *correction);

t_wall	wall_from_triangle(t_double3 triangle[3]);

#endif
