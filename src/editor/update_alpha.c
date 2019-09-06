/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_alpha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 15:24:43 by tfernand          #+#    #+#             */
/*   Updated: 2019/09/03 15:25:50 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	update_alpha(t_editor_interface *edi)
{
	char	tmp_text[25];

	libui_progressbar_set_current_value(&edi->slider_alpha, edi->alpha);
	doom_str_clean(tmp_text, 25);
	doom_nb_to_text(tmp_text, edi->alpha, 1);
	libui_label_set_text(&edi->label_nb_alpha, tmp_text);
}
