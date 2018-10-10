/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylisyak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 18:48:10 by ylisyak           #+#    #+#             */
/*   Updated: 2018/10/09 22:59:57 by ylisyak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"


void    ft_step_sidedist(t_win *game)
{
    if (game->player->raydirx < 0)
        (game->player->stepx = -1) && (game->player->sdistx = \
		(game->player->posx - game->player->mapx) * game->player->ddistx);
    else
        (game->player->stepx = 1) && (game->player->sdistx = \
		(game->player->mapx + 1.0 - game->player->posx) * game->player->ddistx);
    if (game->player->raydiry < 0)
        (game->player->stepy = -1) && (game->player->sdisty = \
		(game->player->posy - game->player->mapy) * game->player->ddisty);
    else
        (game->player->stepy = 1) && (game->player->sdisty = \
		(game->player->mapy + 1.0 - game->player->posy) * game->player->ddisty);
}

void    ft_review_hit_or_not(t_win *game)
{
    game->player->hit = 0;
    while ( game->player->hit == 0)
    {
        if (game->player->sdistx < game->player->sdisty) {
            game->player->sdistx += game->player->ddistx;
            game->player->mapx += game->player->stepx;
            game->player->side = 0;
        } else {
            game->player->sdisty += game->player->ddisty;
            game->player->mapy += game->player->stepy;
            game->player->side = 1;
        }
        if (game->map.map[game->player->mapy][game->player->mapx] > 0) 
			game->player->hit = 1;
    }
}


void    ft_main_engine(t_win *game) {
    int x;
    int y;
    double wallX;
	int lineHeight;

    x = 0;
    y = 0;
    while (x < SCREEN_WIDTH)
    {
        game->player->camerax = (x << 1) / (double)SCREEN_WIDTH - 1; 
        game->player->raydirx = game->player->dirx * game->zoom + game->player->planex * game->player->camerax;
        game->player->raydiry = game->player->diry * game->zoom +  game->player->planey * game->player->camerax;
        game->player->mapx = (int)game->player->posx;
        game->player->mapy = (int)game->player->posy;
        game->player->ddistx = fabs(1.0 / game->player->raydirx);
        game->player->ddisty = fabs(1.0 / game->player->raydiry);
        ft_step_sidedist(game);
        ft_review_hit_or_not(game);
        (game->player->side == 0) ? \
        (game->player->perpwalldist = (game->player->mapx - game->player->posx + ((1 - game->player->stepx) >> 1)) / game->player->raydirx) : \
        (game->player->perpwalldist = (game->player->mapy - game->player->posy + ((1 - game->player->stepy) >> 1)) / game->player->raydiry);
        lineHeight = (int) ((SCREEN_HEIGHT)/ game->player->perpwalldist);
        game->drawstart = -(lineHeight >> 1) + SCREEN_HHALPH;
        (game->drawstart < 0) ? (game->drawstart = 0) : 0;
        game->drawend = (lineHeight >> 1)  + SCREEN_HHALPH;
        (game->drawend >= (SCREEN_HEIGHT)) ? (game->drawend = (SCREEN_HEIGHT) - 1) : 0;
        (game->player->side == 0) ? (wallX = game->player->posy + game->player->perpwalldist * game->player->raydiry) : (wallX = game->player->posx + game->player->perpwalldist * game->player->raydirx);
        wallX -= floor(wallX);
        game->texx = (int)(wallX * (double)game->x);
        (game->player->side == 0 && game->player->raydirx > 0) ? (game->texx = game->x - game->texx - 1) : 0;
        (game->player->side == 1 && game->player->raydiry < 0) ? (game->texx = game->y - game->texx - 1) : 0;
        y = game->drawstart;
        while (y < game->drawend)
        {
			game->coff = y - SCREEN_HHALPH + (lineHeight >> 1);
            game->texy = ((game->coff * game->x) / lineHeight);
            if (game->player->stepx < 0)
                ft_draw_wall(game, 0, x, y);
            else
                ft_draw_wall(game, 1, x, y);
            if (game->player->side == 1)
            {
                if (game->player->stepy < 0)
                {
                    ft_draw_wall(game, 2, x, y);
                }
                else
                    ft_draw_wall(game, 3, x, y);
            }
            y++;           
		}
        //FLOOR CASTING
        double floorXWall, floorYWall; //x, y position of the floor texel at the bottom of the wall

        //4 different wall directions possible
        if(game->player->side == 0 && game->player->raydirx > 0)
        {
            floorXWall = game->player->mapx;
            floorYWall = game->player->mapy + wallX;
        }
        else if(game->player->side == 0 && game->player->raydirx < 0)
        {
            floorXWall = game->player->mapx + 1.0;
            floorYWall = game->player->mapy + wallX;
        }
        else if(game->player->side == 1 && game->player->raydiry> 0)
        {
            floorXWall = game->player->mapx + wallX;
            floorYWall = game->player->mapy;
        }
        else
        {
            floorXWall = game->player->mapx + wallX;
            floorYWall = game->player->mapy + 1.0;
        }
        double distWall, distPlayer, currentDist;

        distWall = game->player->perpwalldist;
        distPlayer = 0.0;

        if (game->drawend < 0) game->drawend = SCREEN_HEIGHT;
		game->x1 = game->flats.ptr_texture[1]->w;
        game->y1 = game->flats.ptr_texture[1]->h;
        game->x2 = game->ceiling.ptr_texture[0]->w;
        game->y2 = game->ceiling.ptr_texture[0]->h;
        for(int y = game->drawend + 1; y < SCREEN_HEIGHT; y++)
        {
            currentDist = SCREEN_HEIGHT / (2.0 * y - SCREEN_HEIGHT);
			double weight = (currentDist - distPlayer) / (distWall - distPlayer);
            double currentFloorX = weight * floorXWall + (1.0 - weight) * game->player->posx;
            double currentFloorY = weight * floorYWall + (1.0 - weight) * game->player->posy;
            int floorTexX, floorTexY;
            floorTexX = (int)(currentFloorX * game->x1) % game->x1;
            floorTexY = (int)(currentFloorY * game->y1) % game->y1;
            game->pixel_ptr = (uint32_t*)game->flats.ptr_texture[1]->pixels;
            game->color_ptr = (game->pixel_ptr[game->x1 * floorTexY + floorTexX] >> 1) & 8355711;
             game->image[x + y * SCREEN_WIDTH] = game->color_ptr;

            game->pixel_ptr = (uint32_t*)game->ceiling.ptr_texture[0]->pixels;
            game->color_ptr = (game->pixel_ptr[game->x2 * floorTexY + floorTexX] >> 1) & 8355711;
            game->image[x + (SCREEN_HEIGHT - y) * SCREEN_WIDTH] = game->color_ptr;
		}
        x++;
    }
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

void    ft_game_core(t_win *game)
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
 	game->currentKeyStates = SDL_GetKeyboardState(NULL);
    (game->currentKeyStates[SDL_SCANCODE_W] || \
	 game->currentKeyStates[SDL_SCANCODE_S] || \
	 game->currentKeyStates[SDL_SCANCODE_D] || \
	 game->currentKeyStates[SDL_SCANCODE_A]) ? ft_move(game) : 0;
    SDL_BlitSurface(game->minimapsurface, NULL, game->screensurface, &area);
    SDL_FreeSurface(game->minimapsurface);
    game->gTexture = \
	SDL_CreateTextureFromSurface(game->gRenderer, game->screensurface);
}

