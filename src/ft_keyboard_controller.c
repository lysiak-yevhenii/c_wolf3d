/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard_controller.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylisyak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 18:25:13 by ylisyak           #+#    #+#             */
/*   Updated: 2018/10/12 00:29:58 by ylisyak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void		ft_menu_execute(t_win *c_ct)
{
	(c_ct->flag_menu_game & FT_GAME) ? (c_ct->flag_menu_game = FT_MENU) \
	&& (c_ct->menu.lotary = rand() % c_ct->menu.quantity) \
	: (c_ct->flag_menu_game = FT_GAME);
	c_ct->menu.status = 0;
}

void		ft_menu_keyevent_down(t_win *c_ct)
{
	if (c_ct->mpthree.key.keysym.scancode == SDL_SCANCODE_F1)
		c_ct->menu.status = 1;
}

void		ft_menu_keyevent_up(t_win *c_ct)
{
	if (c_ct->mpthree.key.keysym.scancode == SDL_SCANCODE_F1)
		c_ct->menu.status = 0;
}

void		ft_game_execute(t_win *c_ct)
{
	if (c_ct->menu.status == 1)
	{
		(c_ct->flag_menu_game & FT_GAME) ? (c_ct->flag_menu_game = FT_MENU) \
		&& (c_ct->menu.lotary = rand() % c_ct->menu.quantity) \
		: (c_ct->flag_menu_game = FT_GAME);
		c_ct->menu.status = 0;
	}
}

void		ft_core(t_win *c_ct)
{
	c_ct->width = SCREEN_WIDTH * 0.10;
	c_ct->height = SCREEN_HEIGHT * 0.10;
	c_ct->width = ((int)(c_ct->width / c_ct->map.miniwidth) * \
	c_ct->map.miniwidth);
	c_ct->height = ((int)(c_ct->height / c_ct->map.miniheight) * \
	c_ct->map.miniheight);
	c_ct->main.lotary = rand() % c_ct->main.quantity;
	ft_showmenu(c_ct);
	while (c_ct->statement)
	{
		c_ct->time = SDL_GetTicks();
		c_ct->screensurface = \
		SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);
		ft_main_engin(c_ct);
		ft_menu_engin(c_ct);
		if (c_ct->flag_menu_game & FT_GAME)
		{
			c_ct->minimapsurface = \
			SDL_CreateRGBSurface(0, c_ct->width, c_ct->height, 32, 0, 0, 0, 0);
			ft_new_event_player(c_ct);
			ft_game_core(c_ct);
		}
		ft_visualization(c_ct);
	}
}
