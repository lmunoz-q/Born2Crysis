/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_secteur_courant_text.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 15:40:56 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/21 16:45:01 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom_nukem.h>

static void		doom_itoa(char *value_text, unsigned int n)
{
	size_t			len;
	size_t			m;
	unsigned int	n2;

	m = 1;
	n2 = n;
	while (n2 >= 10)
	{
		m++;
		n2 /= 10;
	}
	len = m;
	len--;
	while (n >= 10)
	{
		value_text[len--] = (n % 10) + '0';
		n = n / 10;
	}
	value_text[len] = n + '0';
}

static void		clean_text(char *text, int size)
{
	int i;

	i = 0;
	while (i < size + 1)
	{
		text[i] = '\0';
		i++;
	}
}

static void		fill_text(char *text, unsigned int value,
	const char *base_text)
{
	char	value_text[20];
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < SECTEUR_TEXT_SIZE && base_text[i] != '\0')
	{
		text[i] = base_text[i];
		i++;
	}
	clean_text(value_text, 19);
	doom_itoa(value_text, value);
	while (i < SECTEUR_TEXT_SIZE && value_text[j] != '\0')
	{
		text[i] = value_text[j];
		i++;
		j++;
	}
}

void			update_secteur_courant_text(t_libui_widget *label,
	unsigned int new_value)
{
	char new_text[SECTEUR_TEXT_SIZE + 1];

	clean_text(new_text, SECTEUR_TEXT_SIZE);
	fill_text(new_text, new_value, SECTEUR_TEXT);
	libui_label_set_text(label, new_text);
}

void			update_secteur2_courant_text(t_libui_widget *label,
	unsigned int new_value)
{
	char new_text[SECTEUR_TEXT_SIZE + 1];

	clean_text(new_text, SECTEUR_TEXT_SIZE);
	fill_text(new_text, new_value, SECTEUR2_TEXT);
	libui_label_set_text(label, new_text);
}
