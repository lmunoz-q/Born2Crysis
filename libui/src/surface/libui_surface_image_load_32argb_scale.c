/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_surface_image_load_32argb_scale.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:30:59 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/22 16:31:06 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/*
** will load the image found at the path given in parameter and force a 32bit
** argb format for the surface (to unify all blit operations of this library)
*/

static inline SDL_Surface	*image_load_fail(SDL_Surface *tmp1,
	SDL_Surface *tmp2, SDL_Surface *out)
{
	if (tmp1 != NULL)
		SDL_FreeSurface(tmp1);
	if (tmp2 != NULL)
		SDL_FreeSurface(tmp2);
	if (out != NULL)
		SDL_FreeSurface(out);
	return (NULL);
}

SDL_Surface					*libui_surface_image_load_32argb_scale(
	const char *path, double width, double height)
{
	SDL_Surface		*tmp1;
	SDL_Surface		*tmp2;
	SDL_Surface		*out;

	if ((tmp1 = IMG_Load(path)) == NULL)
		return (NULL);
	if ((tmp2 = SDL_CreateRGBSurface(SDL_SWSURFACE, tmp1->w, tmp1->h, 32,
			0xFF0000, 0xFF00, 0xFF, 0xFF000000)) == NULL)
		return (image_load_fail(tmp1, NULL, NULL));
	if (SDL_BlitSurface(tmp1, NULL, tmp2, NULL) < 0)
		return (image_load_fail(tmp1, tmp2, NULL));
	if ((out = SDL_CreateRGBSurface(SDL_SWSURFACE, (int)(tmp1->w * width),
			(int)(tmp1->h * height), 32, 0xFF0000,
			0xFF00, 0xFF, 0xFF000000)) == NULL)
		return (image_load_fail(tmp1, tmp2, NULL));
	if (SDL_BlitScaled(tmp2, NULL, out, NULL) < 0)
		return (image_load_fail(tmp1, tmp2, out));
	return (out);
}
