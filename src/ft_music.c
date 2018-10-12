/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_music.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylisyak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 20:05:18 by ylisyak           #+#    #+#             */
/*   Updated: 2018/10/12 19:24:30 by ylisyak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void		ft_music_execute(t_win *c_ct)
{
	if (c_ct->music.play)
		ft_music_play(c_ct);
	if (c_ct->music.pause)
		ft_music_play(c_ct);
	if (c_ct->music.stop)
		ft_hold_music(c_ct);
	if (c_ct->music.next_song)
		ft_music_next(c_ct);
	if (c_ct->music.previou_song)
		ft_music_previous(c_ct);
}

void		ft_bzero_music_params(t_win *c_ct)
{
	c_ct->music.play = 0;
	c_ct->music.pause = 0;
	c_ct->music.stop = 0;
	c_ct->music.next_song = 0;
	c_ct->music.previou_song = 0;
}

void		ft_fill_playlist(t_win *c_cl, int quantity)
{
	int		order;
	char	*path;
	char	*tmp;

	tmp = NULL;
	order = 0;
	path = "./music/tracks/";
	ft_putstr("Loaded tracks: \n");
	while (order < quantity)
	{
		ft_putstr(c_cl->music.track_names[order]);
		ft_putchar('\n');
		tmp = ft_strjoin(path, c_cl->music.track_names[order++]);
		free(tmp);
	}
}

void		ft_music_player_keyevent_down(t_win *c_ct)
{
	if (c_ct->currentkeystates[SDL_SCANCODE_F8])
		if (c_ct->music.play)
			c_ct->music.pause = 1;
		else
			c_ct->music.play = 1;
	else if (c_ct->currentkeystates[SDL_SCANCODE_F7])
		c_ct->music.previou_song = 1;
	else if (c_ct->currentkeystates[SDL_SCANCODE_F9])
		c_ct->music.next_song = 1;
	else if (c_ct->currentkeystates[SDL_SCANCODE_F6])
		c_ct->music.stop = 1;
	else if (c_ct->currentkeystates[SDL_SCANCODE_KP_PLUS])
		c_ct->zoom += 0.1;
	else if (c_ct->currentkeystates[SDL_SCANCODE_KP_MINUS])
		c_ct->zoom -= 0.1;
}

void		ft_malmix(t_win *c_cl)
{
	c_cl->music.quant_tracks = ft_count_files("./music/tracks/", c_cl);
	ft_putstr("Music: \n");
	ft_putnbr(c_cl->music.quant_tracks);
	ft_fill_playlist(c_cl, c_cl->music.quant_tracks);
}
