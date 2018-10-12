/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylisyak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 18:48:10 by ylisyak           #+#    #+#             */
/*   Updated: 2018/10/12 19:53:00 by ylisyak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void		ft_camera(t_win *game, int x)
{
	game->player->camerax = (x << 1) / (double)SCREEN_WIDTH - 1;
	game->player->raydirx = game->player->dirx * game->zoom +\
	game->player->planex * game->player->camerax;
	game->player->raydiry = game->player->diry * game->zoom +\
	game->player->planey * game->player->camerax;
	game->player->mapx = (int)game->player->posx;
	game->player->mapy = (int)game->player->posy;
	game->player->ddistx = fabs(1.0 / game->player->raydirx);
	game->player->ddisty = fabs(1.0 / game->player->raydiry);
}

void		ft_main_cycle(t_win *game, int x, double wallx, int lineheight)
{
	while (x < SCREEN_WIDTH)
	{
		ft_step_sidedist(game, &x);
		ft_review_hit_or_not(game);
		lineheight = (int)((SCREEN_HEIGHT) / game->player->perpwalldist);
		game->drawstart = -(lineheight >> 1) + SCREEN_HHALPH;
		(game->drawstart < 0) ? (game->drawstart = 0) : 0;
		game->drawend = (lineheight >> 1) + SCREEN_HHALPH;
		(game->drawend >= (SCREEN_HEIGHT)) ?\
		(game->drawend = (SCREEN_HEIGHT) - 1) : 0;
		(game->player->side == 0) ? (wallx = game->player->posy +\
		game->player->perpwalldist * game->player->raydiry) :\
		(wallx = game->player->posx + game->player->perpwalldist *\
		game->player->raydirx);
		wallx -= floor(wallx);
		game->texx = (int)(wallx * (double)game->x);
		(game->player->side == 0 && game->player->raydirx > 0) ?\
		(game->texx = game->x - game->texx - 1) : 0;
		(game->player->side == 1 && game->player->raydiry < 0) ?\
		(game->texx = game->y - game->texx - 1) : 0;
		ft_wall(game, lineheight, x);
		ft_floor_hit(game, wallx);
		ft_ceiling_floor_viz(game, x);
		x++;
	}
}

void		ft_main_engine(t_win *game)
{
	int		x;
	double	wallx;
	int		lineheight;

	x = 0;
	wallx = 0.0;
	lineheight = 0;
	ft_main_cycle(game, x, wallx, lineheight);
}

void		ft_new_event_player(t_win *c_ct)
{
	if (SDL_PollEvent(&c_ct->event))
	{
		c_ct->currentkeystates = SDL_GetKeyboardState(NULL);
		(c_ct->event.type == SDL_QUIT || \
		c_ct->currentkeystates[SDL_SCANCODE_ESCAPE]) ? \
		(c_ct->statement = 0) : 0;
		if (c_ct->event.type == SDL_KEYDOWN)
		{
			ft_music_player_keyevent_down(c_ct);
			if ((c_ct->music.play == 1) || \
			(c_ct->music.pause == 1) || (c_ct->music.stop == 1) || \
			(c_ct->music.next_song == 1) || (c_ct->music.previou_song == 1))
				ft_music_execute(c_ct);
			if (c_ct->currentkeystates[SDL_SCANCODE_F1])
				ft_menu_execute(c_ct);
		}
		else if (c_ct->event.type == SDL_KEYUP)
			ft_bzero_music_params(c_ct);
		else if (c_ct->event.type == SDL_QUIT)
			c_ct->statement = 0;
	}
}

void		ft_game_core(t_win *game)
{
	SDL_Rect area;

	area.x = 0;
	area.y = 0;
	area.w = game->width;
	area.h = game->height;
	(game->screensurface == NULL) ? game->screensurface = \
	SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0) : 0;
	game->image = (uint32_t *)game->screensurface->pixels;
	ft_main_engine(game);
	ft_additonal_engine(game);
	game->currentkeystates = SDL_GetKeyboardState(NULL);
	(game->currentkeystates[SDL_SCANCODE_W] || \
	game->currentkeystates[SDL_SCANCODE_S] || \
	game->currentkeystates[SDL_SCANCODE_D] || \
	game->currentkeystates[SDL_SCANCODE_A]) ? ft_move(game) : 0;
	SDL_BlitSurface(game->minimapsurface, NULL, game->screensurface, &area);
	SDL_FreeSurface(game->minimapsurface);
	game->gtexture = \
	SDL_CreateTextureFromSurface(game->grenderer, game->screensurface);
}
