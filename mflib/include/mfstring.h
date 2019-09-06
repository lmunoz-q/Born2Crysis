/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mfstring.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 19:27:14 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/04 15:39:58 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MFSTRING_H
# define MFSTRING_H

# include <unistd.h>
# include <stdlib.h>
# include "boolean.h"

char	*mf_itoa(int num);
void	mf_itoa_s(int num, char *res);
char	*mf_strnew(size_t size);
char	*mf_strchr(const char *s, int c);
char	*mf_strcpy(char *dst, const char *src);
void	mf_strclr(char *s);
char	*mf_strdup(const char *s1);
size_t	mf_strlen(const char *s);
char	*mf_strjoin(char const *s1, char const *s2);
int		mf_atoi(const char *str);
t_bool	mf_isspace(const char c);
t_bool	mf_isdigit(const char c);
char	*mf_strsub(char const *s, unsigned int start, size_t len);
double	mf_atof(const char *str);
int		mf_strnchr(char *str, char c);
char	*mf_strstr(const char *haystack, const char *needle);
char	*mf_strncpy(char *dst, const char *src, size_t n);
int		mf_strcmp(const char *s1, const char *s2);
char	*mf_uitoa(unsigned long long n);
void	mf_strtoupper(char *str);
int		mf_toupper(int c);
char	*mf_strrchr(const char *s, int c);

#endif
