/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mf_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 23:19:13 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/19 23:20:36 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfstring.h"

int		mf_strcmp(const char *s1, const char *s2)
{
	if (*s1 == *s2 && *s1 == '\0')
		return (0);
	if (*s1 == *s2 && *s1 != '\0')
		return (mf_strcmp(s1 + 1, s2 + 1));
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
