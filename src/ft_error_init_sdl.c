/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_init_sdl.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylisyak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 22:33:56 by ylisyak           #+#    #+#             */
/*   Updated: 2018/10/10 22:35:00 by ylisyak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

int			ft_truble_img(char *truble, t_win *c_cl)
{
	ft_putstr(truble);
	ft_putstr(IMG_GetError());
	c_cl->statement = FT_FALSE;
	return (1);
}

int			ft_truble_mix(char *truble, t_win *c_cl)
{
	ft_putstr(truble);
	ft_putstr(Mix_GetError());
	c_cl->statement = FT_FALSE;
	return (1);
}

int			ft_truble_win(char *truble, t_win *c_cl)
{
	ft_putstr(truble);
	ft_putstr(SDL_GetError());
	c_cl->statement = FT_FALSE;
	return (1);
}

void		ft_error_ttf_init(void)
{
	ft_putstr("Init SDL_Error: ");
	ft_putstr(SDL_GetError());
	exit(2);
}
