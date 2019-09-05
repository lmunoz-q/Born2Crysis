/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_widget_set_pos.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 16:29:38 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/22 16:57:23 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

static inline void	i_shilds(t_libui_widget *w, SDL_Point point)
{
	t_libui_widget		*childs_ptr;

	childs_ptr = w->shilds;
	while (childs_ptr != NULL)
	{
		point.x = childs_ptr->rect.x;
		point.y = childs_ptr->rect.y;
		libui_widget_set_pos(childs_ptr, point);
		childs_ptr = childs_ptr->next;
	}
}

void				libui_widget_set_pos(t_libui_widget *w, SDL_Point point)
{
	SDL_Point			parent_pos;
	SDL_Rect			pr;

	if (w->parent == NULL)
		parent_pos = (SDL_Point){0, 0};
	else
		parent_pos = (SDL_Point){w->parent->rect.x,
			w->parent->rect.y};
	w->relative_pos.x = (point.x < 0) ? 0 : point.x;
	w->relative_pos.y = (point.y < 0) ? 0 : point.y;
	if (w->parent != NULL)
	{
		pr.w = w->parent->rect.w;
		pr.h = w->parent->rect.h;
		w->rect.w = (w->relative_pos.x + w->rect.w > pr.w)
				? pr.w - w->relative_pos.x : w->rect.w;
		w->rect.h = (w->relative_pos.y + w->rect.h > pr.h)
				? pr.h - w->relative_pos.y : w->rect.h;
	}
	w->rect.x = w->relative_pos.x + parent_pos.x;
	w->rect.y = w->relative_pos.y + parent_pos.y;
	i_shilds(w, point);
}
