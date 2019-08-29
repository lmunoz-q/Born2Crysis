/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_handle_drop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 13:58:12 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/29 15:56:00 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

void	init_h(t_handle *h)
{
	h->x = 0;
	h->y = 0;
	h->x2 = 0;
	h->y2 = 0;
	h->size = 160;
}

void	kf_handle_drop(void *param)
{
	t_e			*e;
	t_handle	h;

	init_h(&h);
	e = param;
	if (!(h.message = malloc(h.size + 1)))
		return ;
	SDL_memset(h.message, '\0', h.size + 1);
	SDL_GetGlobalMouseState(&h.x, &h.y);
	SDL_GetWindowPosition(e->win->ptr, &h.x2, &h.y2);
	snprintf(h.message, h.size, "File : %s.", e->input_map.drop_file_path);
	libui_label_set_text(&(e->editor.selected_file_label), h.message);
	if (mf_strstr(e->input_map.drop_file_path, ".obj"))
	{
		if (e->editor.item_placer)
			free(e->editor.item_placer);
		e->editor.item_placer = obj_to_mesh(object_manager_get_obj(e->input_map.
			drop_file_path), "assets/textures/redbrick.bmp", TX_REPEAT);
	}
	else
		mesh_change_texture(e->editor.item_placer, load_texture_from_x(e->
		input_map.drop_file_path, TX_REPEAT));
	free(h.message);
	free(e->input_map.drop_file_path);
}
