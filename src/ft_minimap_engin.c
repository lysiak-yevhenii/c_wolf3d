/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap_engin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylisyak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 23:12:53 by ylisyak           #+#    #+#             */
/*   Updated: 2018/10/10 23:16:21 by ylisyak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void			ft_putplayer_sdl(t_win *game)
{
	t_ft_rect	rect;

	rect.x = game->player->posx;
	rect.y = game->player->posy;
	rect.color = ft_rgb(0, 0, 255, 0);
	ft_fill_rect(&rect, game);
	ft_line_direct(game);
	rect.x = game->player->posx * game->minimapcx;
	rect.y = game->player->posy * game->minimapcy;
	rect.color = ft_rgb(0, 255, 0, 0);
	if (rect.x < game->width && rect.y < game->height)
		game->miniimage[(int)rect.x + ((int)rect.y * (int)game->width)] = \
		rect.color;
}

void			ft_drawminimap(t_win *game)
{
	t_ft_rect	rect;
	int			wall;

	rect.y = 0;
	game->minimapcx = game->width / game->map.miniwidth;
	game->minimapcy = game->height / game->map.miniheight;
	rect.width = game->width;
	rect.hight = game->height;
	rect.color = ft_rgb(255, 0, 0, 0);
	while (rect.y < game->map.miniheight)
	{
		rect.x = 0;
		while (rect.x < game->map.miniwidth)
		{
			wall = game->map.map[rect.y][rect.x];
			if (wall > 0)
			{
				ft_fill_rect(&rect, game);
			}
			rect.x++;
		}
		rect.y++;
	}
	ft_putplayer_sdl(game);
}

void			ft_additonal_engine(t_win *game)
{
	(game->minimapsurface == NULL) ? game->minimapsurface = \
	SDL_CreateRGBSurface(0, game->width, game->height, 32, 0, 0, 0, 0) : 0;
	(game->minimapsurface != NULL) ? game->miniimage = \
							(uint32_t *)game->minimapsurface->pixels : 0;
	ft_drawminimap(game);
}
