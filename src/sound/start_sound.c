/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_sound.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 15:32:25 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/08/25 15:32:26 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom_nukem.h>
#include <physic.h>

void	start_sound(t_sound *s)
{
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	Mix_AllocateChannels(3);
	Mix_Volume(1, MIX_MAX_VOLUME / 2);
//	s->sound = Mix_LoadWAV("assets/sound/bass.wav");
	s->step = Mix_LoadWAV("assets/sound/step.wav");
//	Mix_VolumeChunk(s->sound, MIX_MAX_VOLUME / 3);
//	Mix_PlayChannel(1, s->sound, -1);
	Mix_VolumeChunk(s->step, MIX_MAX_VOLUME);
}
