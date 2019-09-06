/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_destroy_label_data.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 14:48:06 by tfernand          #+#    #+#             */
/*   Updated: 2019/03/28 15:14:29 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	libui_destroy_label_data(t_libui_widget_text *data)
{
	free(data->ptr);
	data->ptr = NULL;
}
