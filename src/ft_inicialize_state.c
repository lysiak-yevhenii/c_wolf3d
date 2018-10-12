/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inicialize_state.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylisyak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 12:45:10 by ylisyak           #+#    #+#             */
/*   Updated: 2018/10/12 19:52:29 by ylisyak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void			ft_initialize_stract(t_win *sc_controller)
{
	sc_controller->window = NULL;
	sc_controller->screensurface = NULL;
	sc_controller->minimapsurface = NULL;
	sc_controller->grenderer = NULL;
	sc_controller->gtexture = NULL;
	sc_controller->mapw = 0;
	sc_controller->maph = 0;
	sc_controller->minimapcx = 0;
	sc_controller->minimapcy = 0;
	sc_controller->minimapscale = 4;
	sc_controller->flag_menu_game = FT_MAIN;
	sc_controller->music.current_track = 0;
	sc_controller->statement = 1;
	sc_controller->music.play = 0;
	sc_controller->music.pause = 0;
	sc_controller->music.next_song = 0;
	sc_controller->music.previou_song = 0;
	sc_controller->music.stop = 0;
	sc_controller->time = 0;
	sc_controller->zoom = 1;
	sc_controller->nfpresent = 0;
	sc_controller->ofpresent = 0;
}

void			ft_initialize_player(t_win *sc_controller)
{
	sc_controller->player->speed = 0;
	sc_controller->player->walku = 0;
	sc_controller->player->walkd = 0;
	sc_controller->player->walkr = 0;
	sc_controller->player->walkl = 0;
	sc_controller->player->rotspeed = 4 * M_PI / 180;
	sc_controller->player->moviespeed = 0.4;
	sc_controller->player->posx = 3.5;
	sc_controller->player->posy = 1.5;
	sc_controller->player->dirx = 1;
	sc_controller->player->diry = 0;
	sc_controller->player->planex = 0.0;
	sc_controller->player->planey = 0.66;
	sc_controller->zoom = 1;
}
