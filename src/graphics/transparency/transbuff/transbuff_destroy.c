/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transbuff_destroy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 17:46:24 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/01 18:45:14 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void		transbuff_destroy(void)
{
	t_trans_buffer		*buff;

	if (!(buff = get_transbuff()))
		return ;
	free(buff->data);
}
