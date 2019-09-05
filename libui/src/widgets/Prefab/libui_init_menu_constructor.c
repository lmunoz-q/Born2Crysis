/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_init_menu_constructor.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 14:38:52 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/22 16:47:07 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	libui_init_menu_constructor(t_libui_menu_constructor *constructor)
{
	*constructor = (t_libui_menu_constructor){.ws = NULL,
		.parent = NULL,
		.rect = {0, 0, 0, 0},
		.label_rect = {0, 0, 0, 0},
		.selecteur_rect = {0, 0, 0, 0},
		.text = NULL,
		.font = NULL,
		.theme = NULL,
		.options_number = 1,
		.option_height = 35};
}
