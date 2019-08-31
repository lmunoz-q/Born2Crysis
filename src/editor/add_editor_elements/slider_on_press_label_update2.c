/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider_on_press_label_update2.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 15:51:16 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/31 15:51:23 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom_nukem.h>

int		slider_on_press_label_update(SDL_Event *event,
	t_libui_widget *widget, void *data)
{
	t_libui_widget_progressbar		*progressdata;
	int								tmp_x;
	struct s_double_value_slider	*dvs;

	(void)event;
	dvs = (struct s_double_value_slider*)data;
	if (widget->type == LUI_WT_SLIDER)
	{
		progressdata = (t_libui_widget_progressbar *)widget->data;
		SDL_GetMouseState(&tmp_x, NULL);
		tmp_x = tmp_x - widget->rect.x;
		if (tmp_x > widget->rect.w)
			tmp_x = widget->rect.w;
		if (widget->rect.w == 0)
			return (-1);
		tmp_x = (double)(tmp_x) / (double)widget->rect.w
				* (double)(progressdata->value_max
				- progressdata->value_min) + progressdata->value_min;
		update_double_slider_data(widget, dvs->label,
			(double)tmp_x / (double)100.0);
		*(dvs->value) = (double)tmp_x / (double)100.0;
	}
	return (0);
}

int		slider_on_press_label_update2(SDL_Event *event, t_libui_widget *widget,
	void *data)
{
	t_libui_widget_progressbar		*progressdata;
	int								tmp_x;
	char							tmp_text[25];
	struct s_int_value_slider		*ivs;

	(void)event;
	ivs = (struct s_int_value_slider *)data;
	if (widget->type == LUI_WT_SLIDER)
	{
		progressdata = (t_libui_widget_progressbar *)widget->data;
		SDL_GetMouseState(&tmp_x, NULL);
		tmp_x = tmp_x - widget->rect.x;
		if (tmp_x > widget->rect.w)
			tmp_x = widget->rect.w;
		if (widget->rect.w == 0)
			return (-1);
		tmp_x = (double)(tmp_x) / (double)widget->rect.w
				* (double)(progressdata->value_max - progressdata->value_min);
		libui_progressbar_set_current_value(widget, tmp_x);
		doom_str_clean(tmp_text, 25);
		doom_nb_to_text(tmp_text, tmp_x);
		libui_label_set_text(ivs->label, tmp_text);
		*(ivs->value) = tmp_x;
	}
	return (0);
}
