/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_double_slider_data.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 16:56:52 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/26 17:30:36 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void doom_nb_to_text(char *text, int nb)
{
	int tmp;
	int	i;

	tmp = nb;
	i = 0;
	while (tmp >= 10)
	{
		tmp = tmp / 10;
		i++;
	}
	while (i >= 0)
	{
		text[i] = '0' + nb % 10;
		nb = nb / 10;
		i--;
	}
}

static void doom_dtoa(double value, char *text, unsigned int len)
{
	unsigned int	nb;

	doom_str_clean(text, len);
	nb = (int)value;
	doom_nb_to_text(text, nb);
	while(*text != '\0')
		++text;
	*text = '.';
	++text;
	nb = (int)((value - (double)nb) * (double)100);
	doom_nb_to_text(text, nb);
}

void	update_double_slider_data(t_libui_widget *slider,
	t_libui_widget *label, double new_value)
{
	int							tmp_x;
	char						tmp_text[25];
	t_libui_widget_progressbar	*data;

	if (slider->type == LUI_WT_SLIDER)
	{
		tmp_x = (int)(new_value * 100);
		data = (t_libui_widget_progressbar *)
			((t_libui_widget_slider *)slider->data)->progressbardata;
		if (tmp_x < data->value_min)
			tmp_x = data->value_min;
		if (tmp_x > data->value_max)
			tmp_x = data->value_max;
		doom_str_clean(tmp_text, 25);
		libui_progressbar_set_current_value(slider, tmp_x);
		doom_dtoa((double)tmp_x / (double)100.0, tmp_text, 25);
		libui_label_set_text(label, tmp_text);
	}
}
