#include <asm.h>

int	run_process(t_process *p)
{
	int r;

	while (!(r = do_op(p)))
		;
	if (r < 0)
		printf("asm: error\n");
	return (r);
}
