/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_init_inputtext_constructor.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 18:01:05 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/27 16:15:15 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void					libui_init_inputtext_constructor(
							t_libui_inputtext_constructor *constructor)
{
	*constructor = (t_libui_inputtext_constructor){.ws = NULL,
									.parent = NULL,
									.rect = {0, 0, 0, 0},
									.label_rect = {0, 0, 0, 0},
									.text = NULL,
									.text_max_len = LIBUI_INPUT_TEXT_MAX_SIZE,
									.font = NULL,
									.font_color = {255, 255, 255, 255},
									.back_color = 0xffffffff};
}
