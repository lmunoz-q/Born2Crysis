/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mf_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 15:56:11 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/04 23:42:58 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfprintf.h"

int			mf_printf(const char *restrict str, ...)
{
	va_list		ap;
	char		*buff;
	int			len;
	ssize_t		tmp;

	len = 0;
	if (!(buff = mf_strnew(0)))
		return (0);
	va_start(ap, str);
	mf_subprint(&ap, (char**)&str, &buff, &len);
	va_end(ap);
	tmp = write(1, buff, len);
	(void)tmp;
	free(buff);
	return (len);
}

char		*mf_sprintf(const char *restrict str, ...)
{
	va_list		ap;
	char		*buff;
	int			len;

	len = 0;
	if (!(buff = mf_strnew(0)))
		return (0);
	va_start(ap, str);
	mf_subprint(&ap, (char**)&str, &buff, &len);
	va_end(ap);
	return (buff);
}
