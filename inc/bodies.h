#ifndef BODIES_H
# define BODIES_H

# include <physic.h>
# include <gjk.h>

int	entity_direction(t_vec3d *direction, void *data);
int	entity_support(t_vec3d *support, t_vec3d dir, void *data);

int	wall_direction(t_vec3d *direction, void *data);
int	wall_support(t_vec3d *support, t_vec3d dir, void *data);

#endif
