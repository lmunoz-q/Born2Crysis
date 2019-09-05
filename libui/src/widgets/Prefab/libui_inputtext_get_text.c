/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_inputtext_get_text.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 18:01:55 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/27 14:47:03 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

char				*libui_inputtext_get_text(t_libui_widget *widget)
{
	t_libui_widget	*label;

	label = widget->shilds;
	return (libui_label_get_text(label));
}
