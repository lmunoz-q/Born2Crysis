/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mf_subprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:09:43 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/04 20:34:01 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfprintf.h"

static char	*mf_strnnjoin(const char *s1, int len1, const char *s2, int len2)
{
	char	*new;
	char	*res;

	if (!(new = mf_strnew(len1 + len2 + 1)))
		return (NULL);
	res = new;
	while (len1--)
		*new++ = *s1++;
	while (len2--)
		*new++ = *s2++;
	*new = '\0';
	return (res);
}

static void	mf_sub_percent(int *len, char *cpy, char *arg, char **str)
{
	*len += mf_strlen(cpy);
	free(cpy);
	while (arg > *str)
		(*str)++;
}

static int	mf_getpercent(char **buff, char **str, int *len)
{
	char	*arg;
	char	*tmp;
	char	*cpy;

	tmp = *buff;
	arg = mf_strchr(*str, '%');
	if (arg == NULL)
	{
		if (!(*buff = mf_strnnjoin(*buff, *len, *str, mf_strlen(*str))))
			return (0);
	}
	else
	{
		if (!(cpy = mf_strnew(arg - (*str))))
			return (0);
		cpy = mf_strncpy(cpy, *str, arg - (*str));
		if (!(*buff = mf_strnnjoin(*buff, *len, cpy, mf_strlen(cpy))))
			return (0);
		mf_sub_percent(len, cpy, arg, str);
		free(tmp);
		return (1);
	}
	*len += mf_strlen(*str);
	free(tmp);
	return (0);
}

void		mf_subprint(va_list *ap, char **str, char **buff, int *len)
{
	char	*tmp;
	char	*tmp2;
	int		argsize;

	while (**str)
	{
		argsize = 0;
		if (mf_getpercent(buff, str, len))
		{
			tmp = *buff;
			(*str)++;
			tmp2 = mf_parse(ap, str, &argsize);
			if (tmp2 == NULL)
				break ;
			if (!(*buff = mf_strnnjoin(*buff, *len, tmp2, argsize)))
				exit(-1);
			*len += argsize;
			free(tmp);
			free(tmp2);
		}
		else
			break ;
	}
}
