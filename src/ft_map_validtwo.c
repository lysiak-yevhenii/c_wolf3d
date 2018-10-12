/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_validtwo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylisyak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 17:28:34 by ylisyak           #+#    #+#             */
/*   Updated: 2018/10/12 17:35:42 by ylisyak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void			ft_filltabcord(t_win *c_cl)
{
	char		*iter;

	c_cl->y = 0;
	while (get_next_line(c_cl->map.fd, &c_cl->map.line))
	{
		c_cl->x = 0;
		iter = c_cl->map.line;
		ft_help_function(c_cl, iter);
		free(c_cl->map.line);
		c_cl->y++;
	}
	c_cl->map.chk = 666;
}

int				ft_right_symbol(char *s, int from)
{
	s += from;
	while (*s)
	{
		if (!((*s >= '0' && *s <= '9') || (*s >= 'A' && *s <= ('A' + 6)) \
		|| (*s >= 'a' && *s <= ('a' + 6))) && *s != '\0')
			ft_error_hex();
		s++;
	}
	return (1);
}

int				ft_validhex(char *map, int tmpd)
{
	int			constnbr;
	char		*cpy;

	constnbr = 6;
	cpy = map;
	if (map[tmpd + 1] == '0' && (map[tmpd + 2] == 'x' ||\
		map[tmpd + 2] == 'X'))
	{
		if (map[tmpd + 3] != '\0')
		{
			if ((constnbr < ft_strlen_from(cpy, (tmpd + 3))))
				return (0);
			if (ft_right_symbol(cpy, (tmpd + 3)) != 1)
				return (0);
		}
		else
			ft_error_hex();
	}
	else
	{
		ft_error_hex();
		return (0);
	}
	return (1);
}

int				ft_nblen(int tmpd)
{
	int			len;
	int			res;

	len = 0;
	res = tmpd;
	if (tmpd == 0)
		return (1);
	while (res != 0)
	{
		res = res / 10;
		len++;
	}
	if (len == 0)
		len++;
	if (tmpd < 0)
		len++;
	return (len);
}

int				ft_validval(char **maps, t_win *par)
{
	int			i;
	size_t		tmpd;

	i = 0;
	par->zoom = 0;
	while (maps[i] != NULL)
	{
		if (ft_isdigit(maps[i][0]) != 1)
			(maps[i][0] != '-' && !ft_isdigit(maps[i][1])) ? \
			ft_error_notdigit() : 0;
		tmpd = ft_nblen(ft_atoi(maps[i]));
		if (ft_strlen(maps[i]) != tmpd && maps[i][tmpd] == ',')
			(ft_validhex(maps[i], tmpd) != 1) ? ft_error_hex() : 0;
		if (ft_strlen(maps[i]) != tmpd && ft_isascii(maps[i][tmpd]) \
			&& maps[i][tmpd] != ',')
			return (0);
		i++;
		par->zoom++;
	}
	return (1);
}
