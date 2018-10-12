/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylisyak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 23:09:43 by ylisyak           #+#    #+#             */
/*   Updated: 2018/10/12 19:31:34 by ylisyak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void		ft_menu_engin(t_win *c_ct)
{
	if (c_ct->flag_menu_game & FT_MENU)
	{
		ft_event_manu(c_ct);
		ft_menu(c_ct);
	}
}

void		ft_main_engin(t_win *c_ct)
{
	if (c_ct->flag_menu_game & FT_MAIN)
	{
		(Mix_PlayingMusic() == 0) ? Mix_PlayMusic((c_ct->music.track = \
		Mix_LoadMUS("./music/support/main.mp3")), -1) : 0;
		ft_event_main(c_ct);
		ft_main(c_ct);
	}
}

void		ft_event_manu(t_win *c_ct)
{
	if (SDL_WaitEvent(&c_ct->mpthree))
	{
		(c_ct->mpthree.type == SDL_QUIT || \
		c_ct->mpthree.key.keysym.scancode == SDL_SCANCODE_ESCAPE) ? \
							(c_ct->statement = 0) : 0;
		if (c_ct->mpthree.type == SDL_KEYDOWN)
			ft_menu_keyevent_down(c_ct);
		else if (c_ct->mpthree.type == SDL_KEYUP)
			ft_menu_keyevent_up(c_ct);
		ft_game_execute(c_ct);
	}
}

void		ft_menu(t_win *c_cl)
{
	(c_cl->gtexture != NULL) ? SDL_DestroyTexture(c_cl->gtexture) : 0;
	c_cl->gtexture = SDL_CreateTextureFromSurface(c_cl->grenderer,\
	(c_cl->menu.ptr_texture = \
	ft_get_img(c_cl->menu.names_with_path[c_cl->menu.lotary])));
	SDL_FreeSurface(c_cl->menu.ptr_texture);
	if (!c_cl->gtexture)
	{
		ft_putstr("Error : \n");
		ft_putstr(SDL_GetError());
		ft_putchar('\n');
	}
}
