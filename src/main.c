# include "doom-nukem.h"

int main()
{
	t_e		env;

	libui_init();
	if (!(env_init(&env)))
		return (-1);
	launch_main_menu(&env);
	//load threads
	//run func (state manager or whatever the fuck you want to call it!
	//unload funcs
	//destroy funcs
	env_destroy(&env);
	libui_close();
	return (0);
}
