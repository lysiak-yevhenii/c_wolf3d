/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylisyak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 19:03:31 by ylisyak           #+#    #+#             */
/*   Updated: 2018/10/10 23:58:07 by ylisyak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void			ft_insert_review(t_win *c_cl)
{
	if ((int)c_cl->player->posy > c_cl->map.miniheight || c_cl->player->posx > \
	c_cl->map.miniwidth)
		ft_error_not_empty();
	else if (c_cl->map.map[(int)c_cl->player->posy]\
[(int)c_cl->player->posx] != 0)
		ft_error_not_empty();
}

void			ft_map_textures_valid(t_win *c_cl)
{
	int			x;
	int			y;

	x = 0;
	y = 0;
	while (y < c_cl->map.miniheight)
	{
		x = 0;
		while (x < c_cl->map.miniwidth)
		{
			if ((c_cl->map.map[y][x] + 4) > (c_cl->walls.quantity))
				ft_error_textures(". oh sorry Tur not exist", "walltextures");
			x++;
		}
		ft_putchar('\n');
		y++;
	}
}

int				main(int ac, char **av)
{
	t_win		c_cl;
	t_player	player;
	time_t		t;

	if (ac < 2)
		return (0);
	ft_bzero(&c_cl, sizeof(t_win));
	ft_map_parsing(av[1], &c_cl);
	if (c_cl.map.chk == 666)
	{
		srand((unsigned)time(&t));
		ft_bzero(&player, sizeof(t_player));
		ft_initialize_stract(&c_cl);
		c_cl.player = &player;
		ft_initialize_player(&c_cl);
		ft_insert_review(&c_cl);
		ft_init_window(&c_cl);
		ft_map_textures_valid(&c_cl);
		(c_cl.statement & FT_FALSE) ? sdl_close(&c_cl) : ft_core(&c_cl);
		sdl_close(&c_cl);
		system("leaks -q wolf3d");
	}
	return (0);
}
