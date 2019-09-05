/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_env.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:35:00 by hmartzol          #+#    #+#             */
/*   Updated: 2019/08/22 17:06:29 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBUI_ENV_H
# define LIBUI_ENV_H

# include <libui_typedef.h>

struct		s_libui_env
{
	Uint32			widget_redraw_event;
	Uint32			discarded_event;
	t_libui_window	*windows;
};

t_libui_env	*libui_env(void);

#endif
