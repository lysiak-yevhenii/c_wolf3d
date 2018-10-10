/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylisyak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 18:48:10 by ylisyak           #+#    #+#             */
/*   Updated: 2018/10/10 22:24:48 by ylisyak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void			ft_visualization(t_win *c_ct)
{
	SDL_FreeSurface(c_ct->screensurface);
	SDL_RenderClear(c_ct->gRenderer);
	SDL_RenderCopy(c_ct->gRenderer, c_ct->gTexture, NULL, NULL);
	(c_ct->gTexture != NULL) ? SDL_DestroyTexture(c_ct->gTexture) : 0;
	SDL_RenderPresent(c_ct->gRenderer);
}

void			ft_draw_wall(t_win *game, int wall_side, int x, int y)
{
	game->pixel_ptr = (uint32_t*)game->walls.ptr_texture[game->map.map\
[game->player->mapy][game->player->mapx] + wall_side]->pixels;
	game->x = game->walls.ptr_texture[game->map.map[game->player->mapy]\
[game->player->mapx] + wall_side]->w;
	game->y = game->walls.ptr_texture[game->map.map[game->player->mapy]\
[game->player->mapx] + wall_side]->h;
	game->color_ptr = game->pixel_ptr[game->x * game->texy + game->texx];
	(game->player->side == 0) ? game->color_ptr = \
	(game->color_ptr >> 1) & 8355711 : 0;
	game->image[x + y * SCREEN_WIDTH] = game->color_ptr;
}

void			ft_line_direct(t_win *game)
{
	t_vector2d	direction;

	game->color = ft_rgb(0, 255, 255, 0);
	direction.x0 = game->player->posx * game->minimapcx;
	direction.y0 = game->player->posy * game->minimapcy;
	direction.x1 = (game->player->posx + game->player->dirx * 4 + \
	cos(game->player->rot) * game->player->stripwidth) * game->minimapcx;
	direction.y1 = (game->player->posy + game->player->diry * 4 + \
	sin(game->player->rot) * game->player->stripwidth) * game->minimapcy;
	direction.color = ft_rgb(255, 0, 0, 0);
	ft_line_sdl(&direction, game);
}

void			ft_fill_rect(t_ft_rect *rect, t_win *game)
{
	rect->startx = rect->x * game->minimapcx;
	rect->tmp = rect->startx;
	rect->endx = rect->startx + game->minimapcx;
	rect->starty = rect->y * game->minimapcy;
	rect->endy = rect->starty + game->minimapcy;
	while (rect->starty < rect->endy)
	{
		rect->startx = rect->tmp;
		while (rect->startx < rect->endx)
		{
			game->miniimage\
[rect->startx + (rect->starty * (int)game->width)] = rect->color;
			rect->startx++;
		}
		rect->starty++;
	}
}
