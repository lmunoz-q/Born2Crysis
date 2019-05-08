# include "doom-nukem.h"

int main()
{
	t_e		env;

	libui_init();
	if (!(env_init(&env)))
		return (-1);
	//load threads
	//run func (state manager or whatever the fuck you want to call it)
	//run_game(&env); //temporary, need a screen manager for this
	//unload funcs
	//destroy funcs
	env_destroy(&env);
	return (0);
}
