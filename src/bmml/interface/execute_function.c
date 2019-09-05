/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:39:37 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

void			sub_process(t_processor *process)
{
	t_op_table	*ot;
	int			op_code;

	while (process->error == ET_OK && process->pc < process->func->code_size)
	{
		op_code = process->func->code[process->pc++];
		if ((ot = get_op(&op_code, 1)) == NULL)
		{
			process->error = ET_INVALID_INSTRUCTION;
			break ;
		}
		ot->process(process, (t_op_param*)&process->func->code[process->pc]);
		process->pc += sizeof(t_op_param) * ot->nb_param;
	}
}

t_error_type	execute_function(t_function *func, void *param, void *local,
	int debug)
{
	t_processor		process;

	if (func == NULL)
		return (ET_NULL_FUNCTION);
	func->alias_memory[0].type = PT_I8;
	func->alias_memory[0].data.i8 = param;
	func->alias_memory[1].type = PT_I8;
	func->alias_memory[1].data.i8 = local;
	process.debug = debug;
	process.func = func;
	process.pc = 0;
	process.error = ET_OK;
	sub_process(&process);
	if (debug && process.error != ET_OK)
		printf("caught error in script: %d\n", process.error);
	return (process.error);
}
