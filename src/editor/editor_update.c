/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 23:36:08 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/31 16:12:25 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int	editor_update(t_e *e, t_editor_interface *editor_interface)
{
	editor_interface->preview_mat = mat4_rotate_pitch(editor_interface->
		preview_mat, 1);
	update_sector_physics(e);
	return (0);
}
