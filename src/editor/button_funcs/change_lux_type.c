/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_lux_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 17:01:42 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/21 17:07:13 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	clean_text(char *text, int size)
{
	int	i;

	i = 0;
	while (i < size + 1)
	{
		text[i] = '\0';
		i++;
	}
}

static void	fill_text(char *text, const char *value_text, const char *base_text)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < SECTEUR_TEXT_SIZE && base_text[i] != '\0')
	{
		text[i] = base_text[i];
		i++;
	}
	while (i < SECTEUR_TEXT_SIZE && value_text[j] != '\0')
	{
		text[i] = value_text[j];
		i++;
		j++;
	}
}

static void	update_lux_type_text(t_libui_widget *widget,
	enum e_light_type lux_type)
{
	char	new_text[SECTEUR_TEXT_SIZE + 1];

	clean_text(new_text, SECTEUR_TEXT_SIZE);
	if (lux_type == POINT_LIGHT)
		fill_text(new_text, LUX_TYPE_POINT_TEXT, LUX_TYPE_TEXT);
	else
		fill_text(new_text, LUX_TYPE_DIRECTION_TEXT, LUX_TYPE_TEXT);
	libui_label_set_text(widget, new_text);
}

int			change_lux_type(SDL_Event *event, t_libui_widget *widget,
	void *data)
{
	t_editor_interface	*editor_interface;

	(void)event;
	(void)widget;
	editor_interface = (t_editor_interface *)data;
	if (editor_interface->lux_type == POINT_LIGHT)
		editor_interface->lux_type = DIRECTIONAL_LIGHT;
	else
		editor_interface->lux_type = POINT_LIGHT;
	update_lux_type_text(&(editor_interface->lux_type_label),
		editor_interface->lux_type);
	return (0);
}
