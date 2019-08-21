/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_lux_intensity_text.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 17:15:47 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/21 18:40:26 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h" 

static size_t uint_len(unsigned int n)
{
	size_t len;

	len = 1;
	while (n >= 10)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static void DOOM_itoa(char *value_text, unsigned int n)
{
	size_t len;

	len = uint_len(n);
	len--;
	while (n >= 10)
	{
		value_text[len--] = (n % 10) + '0';
		n = n / 10;
	}
	value_text[len] = n + '0';
}

static void clean_text(char *text, int size)
{
	int i = 0;

	while (i < size + 1)
	{
		text[i] = '\0';
		i++;
	}
}

static void fill_text(char *text, unsigned int value, const char *base_text)
{
	char		value_text[20];
	int i = 0;
	int j = 0;

	while (i < LUX_TEXT_SIZE && base_text[i] != '\0')
	{
		text[i] = base_text[i];
		i++;
	}
	clean_text(value_text, 19);
	DOOM_itoa(value_text, value);
	while (i < LUX_TEXT_SIZE && value_text[j] != '\0')
	{
		text[i] = value_text[j];
		i++;
		j++;
	}
}

void update_lux_intensity_text(t_libui_widget *label, double	new_value)
{
	char new_text[LUX_TEXT_SIZE + 1];

	clean_text(new_text, LUX_TEXT_SIZE);
	fill_text(new_text, (int)new_value, LUX_INTEN_TEXT);
	libui_label_set_text(label, new_text);
}

void update_lux_fallof_text(t_libui_widget *label, double new_value)
{
	char new_text[LUX_TEXT_SIZE + 1];
	char *tmp;

	clean_text(new_text, LUX_TEXT_SIZE);
	fill_text(new_text, (int)new_value, LUX_FALLOF_TEXT);
	tmp = new_text;
	while (*tmp)
		tmp++;
	*tmp = '.';
	fill_text(new_text, (int)((new_value - (double)(int)new_value) * 10), new_text);
	libui_label_set_text(label, new_text);
}

