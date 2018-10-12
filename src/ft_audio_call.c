/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_audio_call.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylisyak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 19:06:11 by ylisyak           #+#    #+#             */
/*   Updated: 2018/10/12 19:22:34 by ylisyak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

int			ft_music_previous(t_win *c_cl)
{
	if (Mix_PlayingMusic() == 1)
	{
		if (c_cl->music.current_track > 0)
		{
			c_cl->music.current_track--;
			ft_putstr(c_cl->music.track_names[c_cl->music.current_track]);
			ft_putstr("\n");
			Mix_FreeMusic(c_cl->music.track);
			Mix_PlayMusic((c_cl->music.track = Mix_LoadMUS\
(c_cl->music.track_name_and_path[c_cl->music.current_track])), -1);
		}
	}
	else
	{
		if (c_cl->music.current_track > 0)
		{
			c_cl->music.current_track--;
			ft_putstr(c_cl->music.track_names[c_cl->music.current_track]);
			ft_putstr("\n");
			Mix_FreeMusic(c_cl->music.track);
			Mix_PlayMusic((c_cl->music.track = Mix_LoadMUS\
(c_cl->music.track_name_and_path[c_cl->music.current_track])), -1);
		}
	}
	return (1);
}

int			ft_music_next(t_win *c_cl)
{
	if (Mix_PlayingMusic() == 1)
	{
		if (c_cl->music.current_track < c_cl->music.quant_tracks - 1)
		{
			c_cl->music.current_track++;
			ft_putstr(c_cl->music.track_names[c_cl->music.current_track]);
			ft_putstr("\n");
			Mix_FreeMusic(c_cl->music.track);
			Mix_PlayMusic((c_cl->music.track = Mix_LoadMUS\
(c_cl->music.track_name_and_path[c_cl->music.current_track])), -1);
		}
	}
	else
	{
		if (c_cl->music.current_track < c_cl->music.quant_tracks - 1)
		{
			++c_cl->music.current_track;
			ft_putstr(c_cl->music.track_names[c_cl->music.current_track]);
			ft_putstr("\n");
			Mix_FreeMusic(c_cl->music.track);
			Mix_PlayMusic((c_cl->music.track = Mix_LoadMUS\
(c_cl->music.track_name_and_path[c_cl->music.current_track])), -1);
		}
	}
	return (1);
}

int			ft_music_play(t_win *c_cl)
{
	if (Mix_PlayingMusic() == 0)
	{
		ft_putstr(c_cl->music.track_names[c_cl->music.current_track]);
		ft_putstr("\n");
		Mix_FreeMusic(c_cl->music.track);
		Mix_PlayMusic((c_cl->music.track = Mix_LoadMUS\
(c_cl->music.track_name_and_path[c_cl->music.current_track])), -1);
	}
	else if (Mix_PlayingMusic() == 1)
		(Mix_PausedMusic() == 1) ? Mix_ResumeMusic() : Mix_PauseMusic();
	return (1);
}

int			ft_hold_music(t_win *c_cl)
{
	if (c_cl->currentkeystates[SDL_SCANCODE_F6])
		Mix_HaltMusic();
	return (1);
}

int			ft_init_audios(t_win *c_cl)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		ft_truble_mix("SDL_mixer initialize Error: ", c_cl);
		return (-1);
	}
	(!(c_cl->statement & FT_FALSE)) ? ft_malmix(c_cl) : 0;
	return (1);
}
