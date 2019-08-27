/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_handle_drop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 13:58:12 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/27 14:46:53 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

void        kf_handle_drop(void *param)
{
    t_e     *e;
    int     x = 0;
    int   y = 0;
    int   x2 = 0;
    int   y2 = 0;
    int size = 160;
    char *message;
    e = param;
    if (!(message = malloc(size+1)))
        return ;
    SDL_memset(message, '\0', size+1);
    // Shows directory of dropped file
    SDL_GetGlobalMouseState(&x, &y);
    SDL_GetWindowPosition(e->win->ptr, &x2, &y2);
    x -= x2;
    y -= y2;
	snprintf(message, size, "File : %s.", e->input_map.drop_file_path);
	libui_label_set_text(&(e->editor.selected_file_label), message);
    if (mf_strstr(e->input_map.drop_file_path, ".obj"))
        e->editor.item_placer = obj_to_mesh(object_manager_get_obj(e->input_map.drop_file_path), "assets/textures/redbrick.bmp", TX_CLAMP_EDGES);
    if (mf_strstr(e->input_map.drop_file_path, ".bmp"))
        mesh_change_texture(e->editor.item_placer, load_texture_from_bmp(e->input_map.drop_file_path, TX_REPEAT));
    free(message);
}
