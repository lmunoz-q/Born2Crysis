/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 23:40:10 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/30 12:52:57 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VAR_H
# define VAR_H

# include <stdlib.h>
# include <stdint.h>
# include <stdarg.h>
# include "mfmemory.h"

int					mf_clamp_int(int value, int min, int max);
double				mf_clamp_double(double value, double min, double max);
void				mf_swap_doubles(double *one, double *two, size_t n);
void				mf_swap_int(int *one, int *two, size_t n);
/*
** Swaps content of two void pointers
**
** RETURNS: void
*/
void				mf_swap_void_ptrs(void *a, void *b, size_t size);
double				mf_min_double(int num, ...);
int					mf_min_int(int num, ...);
uint32_t			mf_wrap_around(uint32_t x, uint32_t n);

#endif
