/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_parsing_part_one.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylisyak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 16:26:14 by ylisyak           #+#    #+#             */
/*   Updated: 2018/10/12 17:27:37 by ylisyak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

int					is_regular_file(const char *path)
{
	struct stat		path_stat;

	stat(path, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}

int					ft_memstcol(t_win *c_cl)
{
	int				i;

	i = 0;
	if (!(c_cl->map.ceilingmap = (int**)malloc(sizeof(int*)\
	* (c_cl->map.miniheight + 1))))
		return (0);
	while (i < c_cl->map.miniheight + 1)
	{
		if (!(c_cl->map.ceilingmap[i++] = (int*)malloc(sizeof(int) \
	* c_cl->map.miniwidth + 1)))
			return (0);
	}
	i = 0;
	while (i < c_cl->map.miniheight)
		c_cl->map.ceilingmap[i++][c_cl->map.miniwidth] = 0;
	return (1);
}

void				ft_count_ethalon(t_win *params, char **maps, int *i)
{
	int				newi;

	newi = *i;
	while (maps[newi] != NULL && maps[newi][0] != 0 &&\
			maps[newi][1] != 10 && params->map.chk != 1)
		newi++;
	*i = newi;
	if (params->map.chk != 1)
	{
		params->map.miniwidth += *i;
		params->map.chk = 1;
	}
}

int					ft_memstcmal(t_win *c_cl)
{
	int				i;

	i = 0;
	if (!(c_cl->map.map = (int**)malloc(sizeof(int*) * c_cl->map.miniheight)))
		return (0);
	while (i < c_cl->map.miniheight)
		if (!(c_cl->map.map[i++] = (int *)malloc(sizeof(int)\
			* c_cl->map.miniwidth + 1)))
			return (0);
	i = 0;
	while (i < c_cl->map.miniheight)
		c_cl->map.map[i++][c_cl->map.miniwidth] = 0;
	return (1);
}

void				ft_help_function(t_win *c_cl, char *iter)
{
	while (*iter != '\0')
	{
		while (*iter == ' ')
			iter++;
		if (*iter == '-' || isdigit(*iter))
		{
			if (*iter == '-')
				ft_error_minus();
			c_cl->map.map[(int)c_cl->y][(int)c_cl->x] = ft_atoi_base(iter, 10);
			c_cl->map.ceilingmap[(int)c_cl->y][(int)c_cl->x] =  \
			ft_atoi_base("FFFFFF", 16);
		}
		while (*iter != ' ' && *iter != '\0')
		{
			if (*iter == 'x' || *iter == 'X')
				c_cl->map.ceilingmap[(int)c_cl->y][(int)c_cl->x] =\
ft_atoi_base(++iter, 16);
			iter++;
		}
		c_cl->x++;
	}
}
