/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mfprintf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 15:56:18 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/04 15:10:38 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MFPRINTF_H
# define MFPRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "mfstring.h"

typedef enum		e_flags
{
	ALTERNATE = 1 << 0,
	RPAD = 1 << 1,
	ZPAD = 1 << 2,
	SIGN = 1 << 3,
	WIDTH = 1 << 4,
	PRECISION = 1 << 5,
	BLANK = 1 << 6
}					t_flags;

typedef struct		s_params
{
	t_flags			flags;
	enum
	{
		none,
		hh,
		h,
		l,
		ll,
		L
	}				convert;
	enum
	{
		na,
		c,
		s,
		p,
		d,
		i,
		o,
		u,
		x,
		X,
		f,
		pct
	}				type;
	unsigned int	width;
	unsigned int	prec;
	unsigned int	size;
	char			letter;
}					t_params;

typedef struct		s_aille
{
	int				size;
	int				nbz;
	int				padsize;
	int				sign;
}					t_aille;

int					mf_printf(const char *restrict format, ...);
char				*mf_sprintf(const char *restrict format, ...);
char				*mf_parse(va_list *ap, char **str, int *argsize);
char				*mf_dispatch(va_list *ap, t_params *params, int *size);
char				*mf_c_func(va_list *ap, t_params *param);
char				*mf_s_func(va_list *ap, t_params *param);
char				*mf_p_func(va_list *ap, t_params *param);
char				*mf_dui_func(va_list *ap, t_params *param);
char				*mf_o_func(va_list *ap, t_params *param);
char				*mf_x_func(va_list *ap, t_params *param);
char				*mf_f_func(va_list *ap, t_params *param);
char				*mf_na_func(t_params *param);
char				*mf_percent_func(t_params *param);
long long			mf_get_di(va_list *ap, t_params *param);
unsigned long long	mf_get_ouxxb(va_list *ap, t_params *param);
long double			mf_get_float(va_list *ap, t_params *param);
void				mf_printpad_zeros(char **tmp, int padsize, int nbz);
void				mf_get_width(va_list *ap, t_params *params, char **str);
int					mf_isflag(char **str);
void				mf_init_param(t_params *param);
void				mf_init_len(t_aille *len, t_params *p,
								char *nb, long double num);
void				mf_div_f(int *i, long double *tmp, char *res);
long long			mf_floor(long double numb);
long long			mf_fmod(long double num, int mod);
void				mf_subprint(va_list *ap, char **str,
								char **buff, int *len);

#endif
