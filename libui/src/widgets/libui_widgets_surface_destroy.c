/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_widgets_surface_destroy.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 19:46:16 by tfernand          #+#    #+#             */
/*   Updated: 2019/09/01 19:47:25 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	libui_widgets_surface_destroy(t_libui_widgets_surface *ws)
{
	SDL_FreeSurface(ws->surface);
	free(ws->pixel_bound_widget);
}
