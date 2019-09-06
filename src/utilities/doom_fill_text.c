/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_fill_text.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 17:51:59 by tfernand          #+#    #+#             */
/*   Updated: 2019/09/01 17:57:40 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	doom_clean_text(char *text, int size)
{
	int	i;

	i = 0;
	while (i < size + 1)
	{
		text[i] = '\0';
		i++;
	}
}

void	doom_fill_text(char *text, const char *value_text,
	const char *base_text)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < BASE_TEXT_SIZE && base_text[i] != '\0')
	{
		text[i] = base_text[i];
		i++;
	}
	while (i < BASE_TEXT_SIZE && value_text[j] != '\0')
	{
		text[i] = value_text[j];
		i++;
		j++;
	}
}
