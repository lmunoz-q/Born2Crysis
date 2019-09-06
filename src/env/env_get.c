/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 15:30:13 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/01 16:00:00 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_e		*set_env(t_e *e)
{
	static t_e		*e_s = NULL;

	if (e)
		e_s = e;
	return (e_s);
}

t_e		*get_env(void)
{
	return (set_env(NULL));
}
