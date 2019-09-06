/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mf_quicksort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 23:14:03 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/05 23:55:15 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfsort.h"

static int	partition(int *arr, int low, int high)
{
	int		pivot;
	int		i;
	int		j;

	pivot = arr[high];
	i = low - 1;
	j = low - 1;
	while (++j < high)
	{
		if (arr[j] <= pivot)
		{
			i++;
			mf_swap_int(&arr[i], &arr[j], 1);
		}
	}
	mf_swap_int(&arr[i + 1], &arr[high], 1);
	return (i + 1);
}

void		mf_quicksort(int *arr, int low, int high)
{
	int		ni;

	if (low < high)
	{
		ni = partition(arr, low, high);
		mf_quicksort(arr, low, ni - 1);
		mf_quicksort(arr, ni + 1, high);
	}
}
