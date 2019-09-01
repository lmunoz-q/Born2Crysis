/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_eidos_rewind.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 21:01:54 by hmartzol          #+#    #+#             */
/*   Updated: 2019/08/25 14:44:43 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <key_funcs.h>

void	kf_eidos_rewind(void *param)
{
	t_player_entity	*ent;

	ent = &((t_e*)param)->main_player.entity;
	ent->eidos.rewinding = 1;
}
