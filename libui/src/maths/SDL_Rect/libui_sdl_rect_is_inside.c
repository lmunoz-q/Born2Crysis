/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_sdl_rect_is_inside.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:29:37 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/22 16:29:37 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui_maths.h>

/*
** test if rect1 is totally inside rect2
*/

int	libui_sdl_rect_is_inside(SDL_Rect rect1, SDL_Rect rect2)
{
	return (rect1.x >= rect2.x && rect1.x + rect1.w <= rect2.x + rect2.w
		&& rect1.y >= rect2.y && rect1.y + rect1.h <= rect2.y + rect2.h);
}
