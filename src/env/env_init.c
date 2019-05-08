/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 10:24:42 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/08 10:55:41 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

t_bool		env_init(t_e *e)
{
	t_libui_window_constructor constructor;
	constructor = libui_window_default_constructor();
	if (!(e->win = libui_window_create(constructor, NULL, NULL, NULL)))
		return (FALSE);
	return (TRUE);
}
