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

#include <SDL2/SDL_mixer.h>
#include <physic.h>

void	start_sound(void)
{
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	Mix_AllocateChannels(3);
	Mix_Volume(1, MIX_MAX_VOLUME / 2);
	Mix_Chunk *sound;
	Mix_Chunk *step;
	sound = Mix_LoadWAV("assets/sound/bass.wav");
	step = Mix_LoadWAV("assets/sound/step.wav");
	Mix_VolumeChunk(step, MIX_MAX_VOLUME);
	Mix_VolumeChunk(sound, MIX_MAX_VOLUME / 3);
	Mix_PlayChannel(1, sound, -1);
	Mix_PlayChannel(2, step, -1);
}
