/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_handle_drop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 13:58:12 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/20 14:43:59 by mfischer         ###   ########.fr       */
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
    message = malloc(size+1);
    SDL_memset(message, '\0', size+1);
    // Shows directory of dropped file
    SDL_GetGlobalMouseState(&x, &y);
    SDL_GetWindowPosition(e->win->ptr, &x2, &y2);
    x -= x2;
    y -= y2;
    printf("Released grab at x %d, y %d\n", x, y);
    if (x > e->win->surface->w - EDITOR_MENU_WIDTH
        && y > e->win->surface->h - 100)
    {
        snprintf(message, size, "File : %s.", e->input_map.drop_file_path);
        libui_label_set_text(&(e->editor.selected_file_label), message);
    }
    e->editor.item_placer = obj_to_mesh(object_manager_get_obj(e->input_map.drop_file_path), "assets/redbrick.bmp", TX_CLAMP_EDGES);
}