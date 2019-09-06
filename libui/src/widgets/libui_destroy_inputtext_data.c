/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_destroy_inputtext_data.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 22:15:00 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/29 22:36:32 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	libui_destroy_inputtext_data(t_libui_widget *widget)
{
	libui_widget_destroy(widget->shilds);
}
