/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylisyak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 02:26:04 by ylisyak           #+#    #+#             */
/*   Updated: 2018/10/11 23:00:14 by ylisyak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void		ft_step_sidedist(t_win *game, int *x)
{
	ft_camera(game, *x);
	if (game->player->raydirx < 0)
	{
		game->player->stepx = -1;
		game->player->sdistx = \
		(game->player->posx - game->player->mapx) * game->player->ddistx;
	}
	else
	{
		game->player->stepx = 1;
		game->player->sdistx = \
		(game->player->mapx + 1.0 - game->player->posx) * game->player->ddistx;
	}
	if (game->player->raydiry < 0)
	{
		game->player->stepy = -1;
		game->player->sdisty = \
		(game->player->posy - game->player->mapy) * game->player->ddisty;
	}
	else
	{
		game->player->stepy = 1;
		game->player->sdisty = \
		(game->player->mapy + 1.0 - game->player->posy) * game->player->ddisty;
	}
}

void		ft_review_hit_or_not(t_win *game)
{
	game->player->hit = 0;
	while (game->player->hit == 0)
	{
		if (game->player->sdistx < game->player->sdisty)
		{
			game->player->sdistx += game->player->ddistx;
			game->player->mapx += game->player->stepx;
			game->player->side = 0;
		}
		else
		{
			game->player->sdisty += game->player->ddisty;
			game->player->mapy += game->player->stepy;
			game->player->side = 1;
		}
		if (game->map.map[game->player->mapy][game->player->mapx] > 0)
			game->player->hit = 1;
	}
	(game->player->side == 0) ? (game->player->perpwalldist = \
	(game->player->mapx - game->player->posx +\
	((1 - game->player->stepx) >> 1)) / game->player->raydirx) : \
	(game->player->perpwalldist = (game->player->mapy - game->player->posy +\
	((1 - game->player->stepy) >> 1)) / game->player->raydiry);
}

void		ft_wall(t_win *game, int lineheight, int x)
{
	int		y;

	y = game->drawstart;
	while (y < game->drawend)
	{
		game->coff = y - SCREEN_HHALPH + (lineheight >> 1);
		game->texy = ((game->coff * game->x) / lineheight);
		if (game->player->stepx < 0)
			ft_draw_wall(game, 0, x, y);
		else
			ft_draw_wall(game, 1, x, y);
		if (game->player->side == 1)
		{
			if (game->player->stepy < 0)
				ft_draw_wall(game, 2, x, y);
			else
				ft_draw_wall(game, 3, x, y);
		}
		y++;
	}
}

void		ft_floor_hit(t_win *game, double wallx)
{
	if (game->player->side == 0 && game->player->raydirx > 0)
	{
		game->floorxwall = game->player->mapx;
		game->floorywall = game->player->mapy + wallx;
	}
	else if (game->player->side == 0 && game->player->raydirx < 0)
	{
		game->floorxwall = game->player->mapx + 1.0;
		game->floorywall = game->player->mapy + wallx;
	}
	else if (game->player->side == 1 && game->player->raydiry > 0)
	{
		game->floorxwall = game->player->mapx + wallx;
		game->floorywall = game->player->mapy;
	}
	else
	{
		game->floorxwall = game->player->mapx + wallx;
		game->floorywall = game->player->mapy + 1.0;
	}
}

void		ft_ceiling_floor_viz(t_win *game, int x)
{
	double	currentdist;
	int		y;

	y = game->drawend + 1;
	game->distwall = game->player->perpwalldist;
	game->distplayer = 0.0;
	if (game->drawend < 0)
		game->drawend = SCREEN_HEIGHT;
	game->x1 = game->flats.ptr_texture[1]->w;
	game->y1 = game->flats.ptr_texture[1]->h;
	game->x2 = game->ceiling.ptr_texture[0]->w;
	game->y2 = game->ceiling.ptr_texture[0]->h;
	while (y < SCREEN_HEIGHT)
	{
		currentdist = SCREEN_HEIGHT / (2.0 * y - SCREEN_HEIGHT);
		ft_draw_c_f(game, x, y, currentdist);
		y++;
	}
}
