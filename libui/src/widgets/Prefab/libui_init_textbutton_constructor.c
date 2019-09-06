/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_init_textbutton_constructor.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 13:36:09 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/22 16:48:33 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void		libui_init_textbutton_constructor(
		t_libui_textbutton_constructor *constructor)
{
	static const t_libui_double_color	theme = {

	.first_color = 0xffaaaaaa, .second_color = 0xff888888};
	*constructor = (t_libui_textbutton_constructor){.ws = NULL,
													.parent = NULL,
													.rect = {0, 0, 0, 0},
													.label_rect = {0, 0, 0, 0},
													.text = NULL,
													.font = NULL,
													.theme = &theme};
}
