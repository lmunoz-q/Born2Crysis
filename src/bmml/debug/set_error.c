/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:39:17 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:39:19 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

t_compiler	*set_error(t_compiler *comp, t_error_type type)
{
	comp->error = (t_error){.type = type, .pos = comp->head - comp->text};
	return (comp);
}
