/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_validthree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylisyak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 17:41:53 by ylisyak           #+#    #+#             */
/*   Updated: 2018/10/12 18:42:53 by ylisyak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

static void		fill_params(t_win *c_cl, int *y, int *basex, int *basey)
{
	*y = 0;
	c_cl->map.chkord = 0;
	*basex = c_cl->map.miniwidth;
	*basey = c_cl->map.miniheight;
}

static void		kastbl(int *x, int y, t_win *c_cl)
{
	c_cl->map.map[y][*x] = 1;
	*x += 1;
}

int				ft_borders(t_win *c_cl)
{
	int			x;
	int			y;
	int			basey;
	int			basex;

	fill_params(c_cl, &y, &basex, &basey);
	while (y < basey)
	{
		if (c_cl->map.chkord == 0 || (y + 1) == c_cl->map.miniheight)
		{
			x = 0;
			while (x < basex)
				kastbl(&x, y, c_cl);
			y++;
			c_cl->map.chkord = 1;
		}
		if (y != c_cl->map.miniheight)
		{
			c_cl->map.map[y][0] = 1;
			c_cl->map.map[y][c_cl->map.miniwidth - 1] = 1;
		}
		(y <= c_cl->map.miniheight) ? y++ : 0;
	}
	return (1);
}
