#include <asm.h>

void	process_load_op_args(t_process *p, uint8_t nb_args)
{
	size_t	head;
	uint8_t	mask;
	uint8_t	i;

	//should be on the byte right after the operation asking for arguments
	head = p->cpu.instruction_ptr.u64;
	i = -1;
	while (++i < nb_args)
	{
		mask = p->code[head] & AL_MASK;
		if (mask & AL_MEMORY) //kind-of a pointer, uses the next value as displacement (next value cannot be another pointer)
		{
		}
		else if (mask & AL_REGISTER) //next byte is a register_id
		{

		}
		else if (mask & AL_IMMEDIATE) //next bytes is the value itself
		{
		}
		else //error
		{
		}
	}
}
