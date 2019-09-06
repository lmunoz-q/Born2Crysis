/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mf_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 15:27:32 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/06 00:37:35 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "var.h"

void				mf_swap_void_ptrs(void *a, void *b, size_t size)
{
	char	*tmp;

	if (!(tmp = (char *)malloc(sizeof(char) * size)))
		return ;
	mf_memcpy(tmp, b, size);
	mf_memcpy(b, a, size);
	mf_memcpy(a, tmp, size);
	free(tmp);
}

void				mf_swap_doubles(double *one, double *two, size_t n)
{
	size_t	i;
	double	tmp;

	i = -1;
	while (++i < n)
	{
		tmp = one[i];
		one[i] = two[i];
		two[i] = tmp;
	}
}

void				mf_swap_int(int *one, int *two, size_t n)
{
	size_t	i;
	double	tmp;

	i = -1;
	while (++i < n)
	{
		tmp = one[i];
		one[i] = two[i];
		two[i] = tmp;
	}
}
