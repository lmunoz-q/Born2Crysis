/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_widget_destroy.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:09:11 by tfernand          #+#    #+#             */
/*   Updated: 2019/09/01 19:10:53 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	libui_widget_destroy(t_libui_widget *widget)
{
	if (widget->type == LUI_WT_TEXT && widget->data != NULL)
		libui_destroy_label_data(widget->data);
	if (widget->type == LUI_WT_INPUTTEXT && widget->data != NULL)
		libui_destroy_inputtext_data(widget);
	if (widget->type == LUI_WT_TEXT_BUTTON)
	{
		libui_widget_destroy(widget->shilds);
		free(widget->shilds);
		widget->shilds = NULL;
	}
	free(widget->data);
	widget->data = NULL;
	SDL_FreeSurface(widget->texture);
	widget->texture = NULL;
}
