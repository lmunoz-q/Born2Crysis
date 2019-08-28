#ifndef GJK_H
# define GJK_H

# include <mflib.h>

# define GJK_EPSILON 1.19209290E-07
# define GJK_MAX_ITERATIONS 20

typedef struct	s_gjk_support
{
	int		aid;
	int		bid;
	t_vec3d	a;
	t_vec3d	b;
}				t_gjk_support;

typedef struct	s_gjk_vertex
{
	t_vec3d	a;
	t_vec3d	b;
	t_vec3d	p;
	int		aid;
	int		bid;
}				t_gjk_vertex;

typedef struct	s_gjk_simplex
{
	int				max_iter;
	int				iter;
	int				hit;
	int				cnt;
	t_gjk_vertex	v[4];
	t_vec4d			bc;
	double			d;
}				t_gjk_simplex;

typedef struct	s_gjk_result
{
	int		hit;
	t_vec3d	p0;
	t_vec3d	p1;
	double	distance_squared;
	int		iterations;
}				t_gjk_result;

/*
** stores the direction the body is moving
** return 1 if the body is moving, 0 otherwise
*/
typedef int		(t_direction_func)(t_vec3d *direction, void *data);

/*
** stores the farthest vertex/point of the body in the given direction
** return value must be a unique id for this support, usually an index of a
** vertex in a shape or hash of this support
*/
typedef int		(t_support_func)(t_vec3d *support, t_vec3d dir, void *data);

/*
** object containing the necessary methods for the gjk algorithm
** data is handled in ab opaque way by the two methods direction and support
*/
typedef struct	s_gjk_body
{
	t_direction_func	*direction;
	t_support_func		*support;
	void				*data;
}				t_gjk_body;

/*
** default gjk usage, find the potential collision/distance between object a and
** b (accessed via specific function to read the data received in parameter)
*/
t_gjk_result	gjk(t_gjk_body a, t_gjk_body b);

/*
** loop function, return 1 if further calculation is needed, 0 if end reached
*/
int				gjk_loop(t_gjk_simplex *simplex,
						const t_gjk_support *support,
						t_vec3d *direction_vector);

/*
** populate res stgructure from the current simplex (usually the last calculated
** by gjk_loop)
** if the simplex is invalid, the content of res is not initialised
*/
void			gjk_analyze(t_gjk_result *result,
							const t_gjk_simplex *simplex);

/*
** internal functions
*/
void			gjk_switch(t_gjk_simplex *simplex);
int				case_4(t_gjk_simplex *simplex);
int				case_4_bis(t_gjk_simplex *s, t_vec3d v3[12], double d[30]);

#endif
