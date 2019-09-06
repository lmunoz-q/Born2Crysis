/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mf_rand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:05:42 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/06 10:04:26 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfrand.h"

int		mf_rand(void)
{
	static int	prev_seed = 0;
	static int	cur_seed = 0;

	if (prev_seed != mf_seed(-1))
	{
		prev_seed = mf_seed(-1);
		cur_seed = prev_seed;
	}
	cur_seed = (1103515245 * cur_seed + 12345) % __INT_MAX__;
	return (cur_seed);
}
