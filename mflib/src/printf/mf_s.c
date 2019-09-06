/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mf_s.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 14:39:13 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/04 23:44:57 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfprintf.h"

char	*mf_s_func(va_list *ap, t_params *p)
{
	char			*str;
	char			*res;
	unsigned int	bufflen;
	int				i;

	if (!(str = va_arg(*ap, char*)))
		if (!(str = mf_strdup("(null)")))
			return (NULL);
	bufflen = ((p->flags & PRECISION) && p->prec < mf_strlen(str))
	? p->prec : mf_strlen(str);
	p->size = bufflen;
	bufflen = ((p->flags & WIDTH) && p->width > bufflen)
	? p->width : bufflen;
	if (!(res = mf_strnew(bufflen)))
		return (NULL);
	i = -1;
	while (++i < (int)bufflen)
		res[i] = ((p->flags & ZPAD) && !(p->flags & RPAD)) ? '0' : ' ';
	i = ((p->flags & PRECISION) && p->prec < bufflen) ? p->prec : p->size;
	mf_strncpy(((p->flags & RPAD) == RPAD) ? res : res + (bufflen - i),
	str, (i > (int)mf_strlen(str)) ? (int)mf_strlen(str) : i);
	if (!mf_strcmp(str, "(null)"))
		free(str);
	p->size = mf_strlen(res);
	return (res);
}
