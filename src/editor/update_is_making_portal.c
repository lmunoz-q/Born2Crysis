/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_is_making_portal.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 15:15:40 by tfernand          #+#    #+#             */
/*   Updated: 2019/09/05 18:03:53 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	update_is_making_portal(t_editor_interface *edi)
{
	if (edi->is_making_portail == TRUE)
	{
		libui_label_set_text(edi->portail_textbutton.shilds, "MESH");
	}
	else
	{
		libui_label_set_text(edi->portail_textbutton.shilds, "PORTAIL");
	}
}
