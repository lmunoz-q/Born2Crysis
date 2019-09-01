/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_lux_inten_number.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 17:23:57 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/22 13:34:09 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom_nukem.h>

int	decrease_lux_inten_number(SDL_Event *event, t_libui_widget *widget,
	void *data)
{
	t_editor_interface	*editor_interface;

	(void)event;
	(void)widget;
	editor_interface = (t_editor_interface *)data;
	if (editor_interface->lux_intensity > 0)
		editor_interface->lux_intensity -= 1;
	if (editor_interface->lux_intensity < 0)
		editor_interface->lux_intensity = 0;
	update_lux_intensity_text(&(editor_interface->lux_inten_selec_label),
		editor_interface->lux_intensity);
	return (0);
}

int	decrease10_lux_inten_number(SDL_Event *event, t_libui_widget *widget,
	void *data)
{
	t_editor_interface *editor_interface;

	(void)event;
	(void)widget;
	editor_interface = (t_editor_interface *)data;
	if (editor_interface->lux_intensity > 0)
		editor_interface->lux_intensity -= 10;
	if (editor_interface->lux_intensity < 0)
		editor_interface->lux_intensity = 0;
	update_lux_intensity_text(&(editor_interface->lux_inten_selec_label),
		editor_interface->lux_intensity);
	return (0);
}

int	increase_lux_inten_number(SDL_Event *event, t_libui_widget *widget,
	void *data)
{
	t_editor_interface *editor_interface;

	(void)event;
	(void)widget;
	editor_interface = (t_editor_interface *)data;
	if (editor_interface->lux_intensity < MAX_LUX_INTENSITY)
		editor_interface->lux_intensity += 1;
	if (editor_interface->lux_intensity > MAX_LUX_INTENSITY)
		editor_interface->lux_intensity = MAX_LUX_INTENSITY;
	update_lux_intensity_text(&(editor_interface->lux_inten_selec_label),
								editor_interface->lux_intensity);
	return (0);
}

int	increase10_lux_inten_number(SDL_Event *event, t_libui_widget *widget,
	void *data)
{
	t_editor_interface *editor_interface;

	(void)event;
	(void)widget;
	editor_interface = (t_editor_interface *)data;
	if (editor_interface->lux_intensity < MAX_LUX_INTENSITY)
		editor_interface->lux_intensity += 10;
	if (editor_interface->lux_intensity > MAX_LUX_INTENSITY)
		editor_interface->lux_intensity = MAX_LUX_INTENSITY;
	update_lux_intensity_text(&(editor_interface->lux_inten_selec_label),
		editor_interface->lux_intensity);
	return (0);
}
