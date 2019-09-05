/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_animation.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 19:11:00 by hmartzol          #+#    #+#             */
/*   Updated: 2019/08/22 17:06:35 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBUI_ANIMATION_H
# define LIBUI_ANIMATION_H

# include <libui_typedef.h>

/*
** length 0: no animation (cb will not be called)
*/

struct	s_libui_animation
{
	t_libui_animation_callback	*cb;
	size_t						length;
	void						*user_data;
};

#endif
