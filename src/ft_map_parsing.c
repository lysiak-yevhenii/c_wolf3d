/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylisyak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 21:05:47 by ylisyak           #+#    #+#             */
/*   Updated: 2018/10/12 17:57:36 by ylisyak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

static int			ft_validation_len(t_win *c_cl)
{
	int				k;
	char			**maps;

	c_cl->map.size = 0;
	k = -1;
	maps = ft_strsplit(c_cl->map.line, ' ');
	if (c_cl->map.chk != 1)
		ft_count_ethalon(c_cl, maps, &c_cl->map.size);
	while (maps[c_cl->map.size] != NULL && maps[c_cl->map.size][0] != 0)
		c_cl->map.size++;
	if ((*c_cl->map.line == '\0' || *c_cl->map.line == '\n' ||\
	c_cl->map.miniwidth == c_cl->map.size) && ft_validval(maps, c_cl))
	{
		while (maps[++k])
			ft_strdel(&maps[k]);
		free(maps);
		return (1);
	}
	else
	{
		while (maps[++k])
			ft_strdel(&maps[k]);
		free(maps);
		return (0);
	}
}

static int			ft_valid_fill(t_win *c_cl, char *av)
{
	static int		doubn;

	while (get_next_line(c_cl->map.fd, &c_cl->map.line) > 0)
	{
		(*c_cl->map.line == '\0' && doubn == 0) && doubn++;
		(*c_cl->map.line == '\0' && doubn == 1) ? ft_error_len() : 0;
		c_cl->map.chkord += ft_validation_len(c_cl);
		++c_cl->map.miniheight;
		free(c_cl->map.line);
	}
	if (get_next_line(c_cl->map.fd, &c_cl->map.line) != 0)
		return (0);
	else
	{
		(close(c_cl->map.fd) == -1) ? ft_error_gen(&av[1]) : 0;
		return (1);
	}
}

static int			ft_mallocmemarrays(t_win *par)
{
	if (ft_memstcmal(par) & ft_memstcol(par))
		return (1);
	else
		return (0);
}

static int			ft_condition(char *av, t_win *c_cl)
{
	(BUFF_SIZE < 1) ? ft_error_buzz() : 0;
	(is_regular_file(av)) ? 0 : ft_error_dir();
	((c_cl->map.fd = open(av, O_RDONLY)) == -1) ? ft_error_gen(av) : 0;
	(ft_valid_fill(c_cl, av) == 0) ? ft_error_gnl(c_cl) : 0;
	(c_cl->map.miniheight < 3 && c_cl->map.miniheight < 3) ?\
	ft_error_play_space() : 0;
	((c_cl->map.fd = open(av, O_RDONLY)) == -1) ? ft_error_gen(av) : 0;
	(ft_mallocmemarrays(c_cl) == 0) ? ft_error_alloc() : 0;
	if (c_cl->map.chkord == c_cl->map.miniheight)
		return (1);
	else
		ft_error_len();
	return (-1);
}

void				ft_map_parsing(char *av, t_win *c_cl)
{
	int				x;
	int				y;

	x = 0;
	y = 0;
	(ft_condition(av, c_cl) == 1) ? ft_filltabcord(c_cl) : 0;
	(c_cl->map.chk == 666) ? ft_borders(c_cl) : 0;
}
