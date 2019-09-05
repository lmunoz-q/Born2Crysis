/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_save_file_name.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 13:57:43 by tfernand          #+#    #+#             */
/*   Updated: 2019/09/05 18:03:46 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	update_save_file_name(t_editor_interface *edi)
{
	libui_label_set_text(edi->input_save_file.shilds, edi->save_file_name);
}
