/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard_controller.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylisyak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 18:25:13 by ylisyak           #+#    #+#             */
/*   Updated: 2018/10/08 20:22:13 by ylisyak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void    ft_music_player_keyevent_down(t_win *c_ct)
{
    if (c_ct->currentKeyStates[SDL_SCANCODE_F8])
        if (c_ct->music.play)
            c_ct->music.pause = 1;
        else
            c_ct->music.play = 1;
    else if (c_ct->currentKeyStates[SDL_SCANCODE_F7])
        c_ct->music.previou_song = 1;
    else if (c_ct->currentKeyStates[SDL_SCANCODE_F9])
        c_ct->music.next_song = 1;
    else if (c_ct->currentKeyStates[SDL_SCANCODE_F6])
        c_ct->music.stop = 1;
    else if (c_ct->currentKeyStates[SDL_SCANCODE_KP_PLUS])
        c_ct->zoom += 0.1;
    else if (c_ct->currentKeyStates[SDL_SCANCODE_KP_MINUS])
        c_ct->zoom -= 0.1;
}


void    ft_menu_execute(t_win *c_ct)
{
        (c_ct->flag_menu_game & FT_GAME) ? (c_ct->flag_menu_game = FT_MENU) \
        && (c_ct->menu.lotary = rand() % c_ct->menu.quantity) \
        : (c_ct->flag_menu_game = FT_GAME);
        c_ct->menu.status = 0;
}

void    ft_menu_keyevent_down(t_win *c_ct)
{
    if (c_ct->mpthree.key.keysym.scancode == SDL_SCANCODE_F1)
        c_ct->menu.status = 1;
}

void ft_menu_keyevent_up(t_win *c_ct)
{
    if (c_ct->mpthree.key.keysym.scancode == SDL_SCANCODE_F1)
        c_ct->menu.status = 0;
}

void    ft_game_execute(t_win *c_ct)
{
    if (c_ct->menu.status == 1) {
        (c_ct->flag_menu_game & FT_GAME) ? (c_ct->flag_menu_game = FT_MENU) \
        && (c_ct->menu.lotary = rand() % c_ct->menu.quantity) \
        : (c_ct->flag_menu_game = FT_GAME);
        c_ct->menu.status = 0;
    }
}

void    ft_core(t_win *c_ct)
{
    c_ct->width = SCREEN_WIDTH * 0.10;
    c_ct->height = SCREEN_HEIGHT * 0.10;
    c_ct->width  = ((int)(c_ct->width / c_ct->map.miniwidth) * \
	c_ct->map.miniwidth);
    c_ct->height = ((int)(c_ct->height / c_ct->map.miniheight) * \
	c_ct->map.miniheight);
    c_ct->main.lotary = rand() % c_ct->main.quantity;
    ft_showmenu(c_ct);
    while (c_ct->statement) {
        c_ct->time = SDL_GetTicks();
        c_ct->screensurface = \
		SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);
        if (c_ct->flag_menu_game & FT_MAIN) {
            (Mix_PlayingMusic() == 0) ? \
			Mix_PlayMusic((c_ct->music.track = \
			Mix_LoadMUS("./music/support/main.mp3")), -1) : 0;
			ft_event_main(c_ct);
            ft_main(c_ct);
        }
        if (c_ct->flag_menu_game & FT_MENU) {
            ft_event_manu(c_ct);
            ft_menu(c_ct);
        }
        if (c_ct->flag_menu_game & FT_GAME) {
            c_ct->minimapsurface = \
			SDL_CreateRGBSurface(0, c_ct->width, c_ct->height, 32, 0, 0, 0, 0);
            ft_new_event_player(c_ct);
            ft_game_core(c_ct);
        }
        ft_visualization(c_ct);
	}
}
