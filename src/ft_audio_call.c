/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_audio_call.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylisyak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 19:06:11 by ylisyak           #+#    #+#             */
/*   Updated: 2018/10/08 21:54:09 by ylisyak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void        ft_error_textures(char *str, char *strtow)
{
    ft_putstr("\33[0;31m");
    ft_putstr("No enough ");
    ft_putstr(str);
    ft_putstr("<--- this textures. Please load more.");
    ft_putstr("\nOR PUT BACK FOLDER NAME OR CREATE: ");
    ft_putstr(strtow);
    ft_putstr(" folder.");
    exit(1);
}

void   ft_bzero_music_params(t_win *c_ct)
{
    c_ct->music.play = 0;
    c_ct->music.pause = 0;
    c_ct->music.stop = 0;
    c_ct->music.next_song = 0;
    c_ct->music.previou_song = 0;
}

int    ft_music_previous(t_win *c_cl)
{
   if (Mix_PlayingMusic() == 1) {
        if (c_cl->music.current_track > 0) {
            c_cl->music.current_track--;
           	ft_putstr(c_cl->music.track_names[c_cl->music.current_track]);
			ft_putstr("\n");
            Mix_FreeMusic(c_cl->music.track);
            Mix_PlayMusic((c_cl->music.track = Mix_LoadMUS \
			(c_cl->music.track_name_and_path[c_cl->music.current_track])), -1);
        }
    }
    else
    {
        if (c_cl->music.current_track > 0) {
            c_cl->music.current_track--;
            ft_putstr(c_cl->music.track_names[c_cl->music.current_track]);
			ft_putstr("\n");
            Mix_FreeMusic(c_cl->music.track);
            Mix_PlayMusic((c_cl->music.track = Mix_LoadMUS \
			(c_cl->music.track_name_and_path[c_cl->music.current_track])), -1);
    	}
	}
    return (1);
}


int    ft_music_next(t_win *c_cl)
{
    if (Mix_PlayingMusic() == 1) {
        if (c_cl->music.current_track < c_cl->music.quant_tracks - 1) {
            c_cl->music.current_track++;
            ft_putstr(c_cl->music.track_names[c_cl->music.current_track]);
			ft_putstr("\n");
            Mix_FreeMusic(c_cl->music.track);
            Mix_PlayMusic((c_cl->music.track = Mix_LoadMUS \
			(c_cl->music.track_name_and_path[c_cl->music.current_track])), -1);
        }
    }
    else
    {
        if (c_cl->music.current_track < c_cl->music.quant_tracks - 1) {
            ++c_cl->music.current_track;
            ft_putstr(c_cl->music.track_names[c_cl->music.current_track]);
			ft_putstr("\n");
            Mix_FreeMusic(c_cl->music.track);
            Mix_PlayMusic((c_cl->music.track = Mix_LoadMUS \
			(c_cl->music.track_name_and_path[c_cl->music.current_track])), -1);
        }
    }
    return (1);
}

int    ft_music_play(t_win *c_cl) {
    if (Mix_PlayingMusic() == 0) {
        ft_putstr(c_cl->music.track_names[c_cl->music.current_track]);
		ft_putstr("\n");
        Mix_FreeMusic(c_cl->music.track);
        Mix_PlayMusic((c_cl->music.track = Mix_LoadMUS \
		(c_cl->music.track_name_and_path[c_cl->music.current_track])), -1);
    }
    else if (Mix_PlayingMusic() == 1)
        (Mix_PausedMusic() == 1) ? Mix_ResumeMusic() : Mix_PauseMusic();
    return (1);
}

int    ft_hold_music(t_win *c_cl)
{
    if (c_cl->currentKeyStates[SDL_SCANCODE_F6])
        Mix_HaltMusic();
    return (1);
}

void    ft_fill_playlist(t_win *c_cl, int quantity)
{
    int     order;
    char    *path;
    char    *tmp;

    tmp = NULL;
    order = 0;
    path = "./music/tracks/";
    printf("Loaded tracks:\n");
    while (order < quantity) {
        printf("%s\n", c_cl->music.track_names[order]);
        tmp = ft_strjoin(path, c_cl->music.track_names[order++]);
        free(tmp);
    }
}

void    ft_malmix(t_win *c_cl)
{
    c_cl->music.quant_tracks = ft_count_files("./music/tracks/", c_cl);
    printf("Music: %d\n", c_cl->music.quant_tracks);
    ft_fill_playlist(c_cl, c_cl->music.quant_tracks);
}

int     ft_init_audios(t_win *c_cl)
{
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        ft_truble_mix("SDL_mixer initialize Error: ", c_cl);
        return (-1);
    }
    (!(c_cl->statement & FT_FALSE)) ? ft_malmix(c_cl) : 0;
    return (1);
}
