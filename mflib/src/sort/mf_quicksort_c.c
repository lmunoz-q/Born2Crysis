/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mf_quicksort_c.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 00:27:53 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/06 13:11:08 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfsort.h"

static int	partition(char *arr, int index[2], t_bool (*f)(void *, void *),
	size_t size)
{
	void	*pivot;
	int		i;
	int		j;

	pivot = &arr[index[1] * size];
	i = index[0] - 1;
	j = index[0] - 1;
	while (++j < index[1])
	{
		if (f(&arr[j * size], pivot))
		{
			i++;
			mf_swap_void_ptrs(&arr[i * size], &arr[j * size], size);
		}
	}
	mf_swap_void_ptrs(&arr[(i + 1) * size], &arr[index[1] * size], size);
	return (i + 1);
}

void		mf_quicksort_c(void *arr, int i[2], t_bool (*f)(void *, void *),
	size_t size)
{
	int		ni;

	if (i[0] < i[1])
	{
		ni = partition(arr, (int[2]){i[0], i[1]}, f, size);
		mf_quicksort_c(arr, (int[2]){i[0], ni - 1}, f, size);
		mf_quicksort_c(arr, (int[2]){ni + 1, i[1]}, f, size);
	}
}
