/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:37:53 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:37:56 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

void		*realloc_f(void *p, size_t size)
{
	void	*t;

	if ((t = realloc(p, size)) == NULL)
		free(p);
	return (t);
}
