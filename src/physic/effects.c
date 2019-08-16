//
// Created by lee on 16/08/2019.
//

#include <physic.h>
#include <world.h>

void	apply_effect(t_entity *e, t_world *w, t_effect effect)
{
	(void)w;
	if (effect == EFF_RESET_JUMP)
		e->can_jump = 1;
	if (effect == EFF_ACTIVATE_FLY)
	{
		e->can_go_down = 1;
		e->can_go_up = 1;
	}
	if (effect == EFF_DEACTIVATE_FLY)
	{
		e->can_go_down = 0;
		e->can_go_up = 0;
	}
}
