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

void    ft_music_execute(t_win *c_ct)
{
    if (c_ct->music.play)
        ft_music_play(c_ct);
    if (c_ct->music.pause)
        ft_music_play(c_ct);
    if (c_ct->music.stop)
        ft_hold_music(c_ct);
    if (c_ct->music.next_song)
        ft_music_next(c_ct);
    if (c_ct->music.previou_song)
        ft_music_previous(c_ct);
}

void    ft_turnleft(t_win *game)
{
    double cosinus;
    double sinus;
    cosinus = cos(game->player->rotspeed);
    sinus = sin(game->player->rotspeed);
    game->player->olddirx = game->player->dirx;
    game->player->dirx = game->player->dirx * cosinus - \
						 game->player->diry * sinus;
    game->player->diry = game->player->olddirx * sinus + \
						 game->player->diry * cosinus;
    game->player->oldplanex = game->player->planex;
    game->player->planex = game->player->planex * cosinus - \
						   game->player->planey * sinus;
    game->player->planey =  game->player->oldplanex * sinus + \
							game->player->planey * cosinus;

}

void    ft_turnright(t_win *game)
{
    double cosinus;
    double sinus;

    cosinus = cos(-game->player->rotspeed);
    sinus = sin(-game->player->rotspeed);
    game->player->olddirx = game->player->dirx;
    game->player->dirx = game->player->dirx * cosinus - \
						 game->player->diry * sinus;
    game->player->diry = game->player->olddirx * sinus + \
						 game->player->diry * cosinus;
    game->player->oldplanex = game->player->planex;
    game->player->planex = game->player->planex * cosinus - \
						   game->player->planey * sinus;
    game->player->planey = game->player->oldplanex * sinus + \
						   game->player->planey * cosinus;
}

void    ft_menu_execute(t_win *c_ct)
{
        (c_ct->flag_menu_game & FT_GAME) ? (c_ct->flag_menu_game = FT_MENU) \
        && (c_ct->menu.lotary = rand() % c_ct->menu.quantity) \
        : (c_ct->flag_menu_game = FT_GAME);
        c_ct->menu.status = 0;
}

void    ft_new_event_player(t_win *c_ct)
{
     if (SDL_PollEvent(&c_ct->event)) {
         c_ct->currentKeyStates = SDL_GetKeyboardState(NULL);
         (c_ct->event.type == SDL_QUIT || \
		 c_ct->currentKeyStates[SDL_SCANCODE_ESCAPE]) ? \
		(c_ct->statement = 0) : 0;
         if (c_ct->event.type == SDL_KEYDOWN) {
             ft_music_player_keyevent_down(c_ct);
             if ((c_ct->music.play == 1) || \
				(c_ct->music.pause == 1) || (c_ct->music.stop == 1) || \
                (c_ct->music.next_song == 1) || (c_ct->music.previou_song == 1))
                 ft_music_execute(c_ct);
             if (c_ct->currentKeyStates[SDL_SCANCODE_F1])
                 ft_menu_execute(c_ct);
         }
         else if (c_ct->event.type == SDL_KEYUP)
             ft_bzero_music_params(c_ct);
         else if (c_ct->event.type == SDL_QUIT)
             c_ct->statement = 0;
     }

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

void    ft_event_manu(t_win *c_ct)
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

void ft_main_keyevent_down(t_win *c_ct)
{
    if (c_ct->mpthree.key.keysym.scancode == SDL_SCANCODE_DOWN || \
		c_ct->mpthree.key.keysym.scancode == SDL_SCANCODE_UP) {
        if (c_ct->main.selected[0] == 0) {
            c_ct->main.selected[0] = 1;
            c_ct->main.selected[1] = 0;
        } else if (c_ct->main.selected[0] == 1) {
            c_ct->main.selected[0] = 0;
            c_ct->main.selected[1] = 1;
        }
    }
    if (c_ct->mpthree.key.keysym.scancode == SDL_SCANCODE_SPACE)
    {
        if (c_ct->main.selected[0] == 1) {
            c_ct->menu.status = 1;
            ft_game_execute(c_ct);
        } else if (c_ct->main.selected[0] == 0) {
            c_ct->statement = 0;
        }
    }
}

void    ft_event_main(t_win *main)
{
    if (SDL_WaitEvent(&main->mpthree))
    {
        if (main->mpthree.type == SDL_QUIT || \
		main->mpthree.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
            (main->statement = 0);
        if (main->mpthree.type == SDL_KEYDOWN)
            ft_main_keyevent_down(main);
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
        SDL_FreeSurface(c_ct->screensurface);
        SDL_RenderClear(c_ct->gRenderer);
        SDL_RenderCopy(c_ct->gRenderer, c_ct->gTexture, NULL, NULL);
		(c_ct->gTexture != NULL) ? SDL_DestroyTexture(c_ct->gTexture) : 0;
        SDL_RenderPresent(c_ct->gRenderer);
	}
}
