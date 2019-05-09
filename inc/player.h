#ifndef PLAYER_H
# define PLAYER_H

# include <inventory.h>

# define DEFAULT_MAX_SPEED 100.0
# define DEFAULT_MAX_LIFE 100

# define ACC_GRAVITY 0
# define ACC_PLAYER_WALK 1
# define ACC_PLAYER_JUMP 2
# define ACC_MODIFIER 3
# define ACCELERATIONS 4

typedef struct	s_player_stats
{
	int			life;
	int			max_life;
	int			armor;
	int			stamina;
	int			max_stamina;
	int			kill_count;
	int			score;
	char		script_data[64];
}				t_player_stats;

typedef struct	s_player
{
	double			pos[3];
	double			velocity[3];
	double			acceleration[ACCELERATIONS][3];
	double			direction[2];
	int				sector;
	t_inventory		inventory;
	t_player_stats	stats;
}				t_player;

#endif
