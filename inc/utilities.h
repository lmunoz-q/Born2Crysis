/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:43:20 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/01 00:43:24 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

# include <SDL2/SDL.h>

void		count_fps(int *res);

void		doom_str_clean(char *text, unsigned int len);
void		doom_nb_to_text(char *text, int nb, int size_min);

#endif
