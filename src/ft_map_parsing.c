/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylisyak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 21:05:47 by ylisyak           #+#    #+#             */
/*   Updated: 2018/10/08 21:06:43 by ylisyak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

static int				is_regular_file(const char *path)
{
    struct stat	path_stat;

    stat(path, &path_stat);
    return (S_ISREG(path_stat.st_mode));
}

static int			ft_memstcol(t_win *c_cl)
{
    int		i;

    i = 0;
    if (!(c_cl->map.ceilingmap = (int**)malloc(sizeof(int*) * (c_cl->map.miniheight + 1))))
        return (0);
    while (i < c_cl->map.miniheight + 1)
    {
        if (!(c_cl->map.ceilingmap[i++] = (int *)malloc(sizeof(int)  \
		* c_cl->map.miniwidth + 1)))
            return (0);
    }
    i = 0;
    while (i < c_cl->map.miniheight)
        c_cl->map.ceilingmap[i++][c_cl->map.miniwidth] = 0;
    return (1);
}

static void			ft_count_ethalon(t_win *params, char **maps, int *i)
{
    int			newi;

    newi = *i;
    while (maps[newi] != NULL && maps[newi][0] != 0 && maps[newi][1] != 10 && params->map.chk != 1)
        newi++;
    *i = newi;
    if (params->map.chk != 1)
    {
        params->map.miniwidth+= *i;
        params->map.chk = 1;
    }
}

static int			ft_memstcmal(t_win *c_cl)
{
    int		i;

    i = 0;
    if (!(c_cl->map.map = (int**)malloc(sizeof(int*) * c_cl->map.miniheight)))
        return (0);
    while (i < c_cl->map.miniheight)
        if (!(c_cl->map.map[i++] = (int *)malloc(sizeof(int) \
		* c_cl->map.miniwidth + 1)))
            return (0);
    i = 0;
    while (i < c_cl->map.miniheight)
        c_cl->map.map[i++][c_cl->map.miniwidth] = 0;
    return (1);
}

static void		ft_help_function(t_win *c_cl, char *iter)
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
                c_cl->map.ceilingmap[(int)c_cl->y][(int)c_cl->x] =  \
				ft_atoi_base(++iter, 16);
            iter++;
        }
        c_cl->x++;
    }
}

static void		ft_filltabcord(t_win *c_cl)
{
    char	*iter;

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

static int			ft_right_symbol(char *s, int from)
{
    s += from;
    while (*s)
    {
        if (!((*s >= '0' && *s <= '9') || (*s >= 'A' && *s <= ('A' + 6))
              || (*s >= 'a' && *s <= ('a' + 6))) && *s != '\0')
            ft_error_hex();
        s++;
    }
    return (1);
}

static int			ft_validhex(char *map, int tmpd)
{
    int		constnbr;
    char	*cpy;

    constnbr = 6;
    cpy = map;
    if (map[tmpd + 1] == '0' && (map[tmpd + 2] == 'x' || map[tmpd + 2] == 'X'))
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

static int			ft_nblen(int tmpd)
{
    int		len;
    int		res;

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

static int			ft_validval(char **maps, t_win *par)
{
    int		i;
    size_t	tmpd;

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

static int			ft_validation_len(t_win  *c_cl)
{
    int		k;
    char	**maps;

    c_cl->map.size = 0;
    k = -1;
    maps = ft_strsplit(c_cl->map.line, ' ');
    if (c_cl->map.chk != 1)
        ft_count_ethalon(c_cl, maps, &c_cl->map.size);
    while (maps[c_cl->map.size] != NULL && maps[c_cl->map.size][0] != 0)
        c_cl->map.size++;
    if ((*c_cl->map.line == '\0' || *c_cl->map.line == '\n' || c_cl->map.miniwidth == c_cl->map.size) && ft_validval(maps, c_cl))
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


static int				ft_valid_fill(t_win *c_cl, char *av)
{
    static int	doubn;

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

static int				ft_mallocmemarrays(t_win *par)
{
    if (ft_memstcmal(par) & ft_memstcol(par))
        return (1);
    else
        return (0);
}

static int				ft_condition(char *av, t_win *c_cl)
{
    (void)c_cl;
    (BUFF_SIZE < 1) ? ft_error_buzz() : 0;
    (is_regular_file(av)) ? 0 : ft_error_dir();
    ((c_cl->map.fd = open(av, O_RDONLY)) == -1) ? ft_error_gen(av) : 0;
    (ft_valid_fill(c_cl, av) == 0) ? ft_error_gnl(c_cl) : 0;
    (c_cl->map.miniheight < 3 && c_cl->map.miniheight < 3) ? ft_error_play_space() : 0;
    ((c_cl->map.fd = open(av, O_RDONLY)) == -1) ? ft_error_gen(av) : 0;
    (ft_mallocmemarrays(c_cl) == 0) ? ft_error_alloc() : 0;
    if (c_cl->map.chkord == c_cl->map.miniheight)
        return (1);
    else
        ft_error_len();
    return (-1);
}

static int     ft_borders(t_win *c_cl)
{
    int  x;
    int  y;
    int  basey;
    int  basex;

    y = 0;
    c_cl->map.chkord = 0;
    basex = c_cl->map.miniwidth;
    basey = c_cl->map.miniheight;
	while (y < basey)
    {
        if (c_cl->map.chkord == 0 || (y + 1) == c_cl->map.miniheight) {
            x = 0;
            while (x < basex)
			{
                c_cl->map.map[y][x] = 1;
				x++;
			}
            y++;
            c_cl->map.chkord = 1;
        }
        if (y != c_cl->map.miniheight) {
            c_cl->map.map[y][0] = 1;
            c_cl->map.map[y][c_cl->map.miniwidth - 1] = 1;
        }
        if (y <= c_cl->map.miniheight)
		   	y++;
    }
    return (1);
}

void    ft_map_parsing(char *av, t_win *c_cl)
{
    int x;
    int y;

    x = 0;
    y = 0;
    (ft_condition(av, c_cl) == 1) ? ft_filltabcord(c_cl) : 0;
    (c_cl->map.chk == 666) ? ft_borders(c_cl) : 0;
}
