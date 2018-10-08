/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylisyak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 21:15:09 by ylisyak           #+#    #+#             */
/*   Updated: 2018/10/08 21:17:20 by ylisyak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void		ft_error_minus(void)
{
	ft_putstr("NOT WALID MAP! \'-\' is preasent! You funny...");
	ft_putstr("\nTry harder... (>_>) You know I hate you... ? .");
	ft_putstr("\nYou trying to kick my ass. I hope you will fail.");
	exit(1);
}

int         ft_truble_img(char *truble, t_win *c_cl)
{
    ft_putstr(truble);
    ft_putstr(IMG_GetError());
    c_cl->statement = FT_FALSE;
    return (1);
}

int         ft_truble_mix(char *truble, t_win *c_cl)
{
    ft_putstr(truble);
    ft_putstr(Mix_GetError());
    c_cl->statement = FT_FALSE;
    return (1);
}

int         ft_truble_win(char *truble, t_win *c_cl)
{
    ft_putstr(truble);
    ft_putstr(SDL_GetError());
    c_cl->statement = FT_FALSE;
    return (1);
}

void	ft_error_buzz(void)
{
    ft_putstr_fd("Error: BUFF_SIZE must be grater then 0\n", 2);
    exit(1);
}

void	ft_error_gnl(t_win *params)
{
    ft_putstr("Error: get_next_line returned -1.\n");
    free(params->map.line);
    exit(1);
}

void	ft_error_notdigit(void)
{
    ft_putstr("Error: not digit value.\n");
    exit(1);
}

void	ft_error_hex(void)
{
    ft_putstr("Error: heximal input invalid.\n");
    exit(1);
}

void	ft_error_alloc(void)
{
    ft_putstr("Error: allocate memory.\n");
    exit(1);
}

void	ft_error_dir(void)
{
    ft_putstr("Error: You put directory or another thing - NOT .fdf file! \n");
    exit(1);
}

void	ft_error_len(void)
{
    ft_putstr("Error: row not equal in each coloms.\n");
    exit(1);
}

void	ft_error_play_space(void)
{
    ft_putstr("Error: no enough space to put player.\n");
    exit(1);
}

void	ft_error_not_empty(void)
{
    ft_putstr("Error: try another point there to put player start position.\n");
    exit(1);
}

void	ft_error_ttf_init(void)
{
	ft_putstr("Init SDL_Error: ");
	ft_putstr(SDL_GetError());
	exit(2);
}

void	ft_error_gen(char *av)
{
    char *notify;
    char *tmp;

    notify = ft_strnew(1);
    tmp = ft_strjoin(notify, "error: ");
    free(notify);
    notify = ft_strjoin(tmp, strerror(errno));
    free(tmp);
    tmp = ft_strjoin(notify, " for ");
    free(notify);
    notify = ft_strjoin(tmp, av);
    free(tmp);
    tmp = ft_strjoin(notify, "\n");
    free(notify);
    ft_putstr_fd(tmp, 2);
    free(tmp);
    exit(1);
}
