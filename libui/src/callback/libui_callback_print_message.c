/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_callback_print_message.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 15:41:54 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/31 17:19:10 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

#include <unistd.h>

static size_t	doom_strlen(const char *s)
{
	char *ptr;

	ptr = (char *)s;
	while (*ptr != '\0')
		ptr++;
	return ((size_t)(ptr - s));
}

static void		doom_putstr(char const *s)
{
	int i;

	if (s != NULL)
		i = write(1, s, doom_strlen(s));
	i = write(1, "\n", 1);
	(void)i;
}

int				libui_callback_print_message(SDL_Event *event,
	t_libui_widget *widget, void *data)
{
	(void)event;
	(void)widget;
	doom_putstr((char *)data);
	return (0);
}
