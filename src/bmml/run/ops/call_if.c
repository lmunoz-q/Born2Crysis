/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_if.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:40:24 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:40:26 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

t_error_type	process_call_if(t_processor *p, t_op_param *param)
{
	t_data	val;

	if (get_casted_parameter(p, &param[0], &val, PT_U64) != ET_OK)
		return (p->error);
	if (val.u64)
		return (process_call(p, &param[1]));
	return (p->error);
}
