/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_is_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 15:17:36 by tfernand          #+#    #+#             */
/*   Updated: 2019/09/03 15:20:26 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	update_is_light(t_editor_interface *edi)
{
	if (edi->is_light == TRUE)
		libui_label_set_text(edi->light_textbutton.shilds, "LIGHT (OFF)");
	else
		libui_label_set_text(edi->light_textbutton.shilds, "LIGHT (ON)");
}
