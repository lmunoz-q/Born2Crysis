/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_close.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 20:25:47 by hmartzol          #+#    #+#             */
/*   Updated: 2019/08/29 19:41:52 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui.h>

void	libui_close(void)
{
	SDL_StopTextInput();
	if (TTF_WasInit())
		TTF_Quit();
	SDL_Quit();
}
