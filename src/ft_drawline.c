/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylisyak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 22:25:19 by ylisyak           #+#    #+#             */
/*   Updated: 2018/10/10 22:32:51 by ylisyak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

int				ft_rgb(int r, int g, int b, int transp)
{
	int			color;

	color = b + (g << 8) + (r << 16) + (transp << 24);
	return (color);
}

void			ft_vertex(int x, int y, int color, t_win *game)
{
	(void)color;
	if ((x >= 0 && y >= 0) && (x < game->width && y < game->height))
		game->miniimage[(int)x + ((int)y * (int)game->width)] = 0xFFFFFF;
}

void			ft_build_p1(t_win *game, int *x, int *y, t_vector2d *vector)
{
	int			i;
	int			d;
	int			d1;
	int			d2;

	i = 0;
	d = (game->tmpk << 1) - game->tmpc;
	d1 = game->tmpk << 1;
	d2 = (game->tmpk - game->tmpc) << 1;
	ft_vertex((int)vector->x0, (int)vector->y0, vector->color, game);
	*x = ((int)vector->x0) + game->sx;
	*y = ((int)vector->y0);
	while (++i <= game->tmpc)
	{
		if (d > 0)
		{
			d += d2;
			*y += game->sy;
		}
		else
			d += d1;
		ft_vertex(*x, *y, vector->color, game);
		*x += game->sx;
	}
}

void			ft_build_p2(t_win *game, int *x, int *y, t_vector2d *vector)
{
	int			i;
	int			d;
	int			d1;
	int			d2;

	i = 0;
	d = (game->tmpc << 1) - game->tmpk;
	d1 = game->tmpc << 1;
	d2 = (game->tmpc - game->tmpk) << 1;
	ft_vertex((int)vector->x0, (int)vector->y0, vector->color, game);
	*y = ((int)vector->y0 + game->sy);
	*x = ((int)vector->x0);
	while (++i <= game->tmpk)
	{
		if (d > 0)
		{
			d += d2;
			*x += game->sx;
		}
		else
			d += d1;
		ft_vertex(*x, *y, vector->color, game);
		*y += game->sy;
	}
}

void			ft_line_sdl(t_vector2d *vector, t_win *game)
{
	int			x;
	int			y;

	game->tmpc = abs((int)vector->x1 - (int)vector->x0);
	game->tmpk = abs((int)vector->y1 - (int)vector->y0);
	game->sx = (int)vector->x1 >= (int)vector->x0 ? 1 : -1;
	game->sy = (int)vector->y1 >= (int)vector->y0 ? 1 : -1;
	(game->tmpk <= game->tmpc) ? ft_build_p1(game, &x, &y, vector) : \
	ft_build_p2(game, &x, &y, vector);
}
