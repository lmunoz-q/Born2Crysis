/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:37:50 by tfernand          #+#    #+#             */
/*   Updated: 2019/05/08 14:17:34 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H

#include "libui.h"
#include "doom-nukem.h"

typedef struct	s_double_color
{
	int first_color;
	int second_color;
}				t_double_color;

void	launch_main_menu(t_e *e);

#endif
