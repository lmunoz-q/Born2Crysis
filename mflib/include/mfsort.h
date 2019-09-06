/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mfsort.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 23:09:55 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/30 12:56:57 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MFSORT_H
# define MFSORT_H

# include "var.h"
# include "boolean.h"

/*
** The quicksort function is a fast sorting function for int arrays.
**
** RETURNS: void
*/
void	mf_quicksort(int *arr, int low, int high);

/*
** The quicksort_c uses the same algorithm as the regular quicksort
** but takes generic pointers and takes a custom comparison function
** that returns TRUE when it should be swapped, and FALSE otherwise.
**
** PARAMS:
** The second param takes an array of a low and high bound.
** The last param is the size of the array elem type.
**
** RETURNS: void
*/
void	mf_quicksort_c(void *arr, int i[2], t_bool (*f)(void *, void *),
						size_t size);

#endif
