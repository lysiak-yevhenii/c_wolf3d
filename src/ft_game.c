/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylisyak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 18:48:10 by ylisyak           #+#    #+#             */
/*   Updated: 2018/10/08 21:55:39 by ylisyak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void    ft_draw_wall(t_win *game, int  wall_side, int x, int y)
{
    game->pixel_ptr = (uint32_t*)game->walls.ptr_texture[game->map.map[game->player->mapy][game->player->mapx] + wall_side]->pixels;
    game->x = game->walls.ptr_texture[game->map.map[game->player->mapy][game->player->mapx] + wall_side]->w;
    game->y = game->walls.ptr_texture[game->map.map[game->player->mapy][game->player->mapx] + wall_side]->h;
    game->color_ptr = game->pixel_ptr[game->x * game->texy + game->texx];
    (game->player->side == 0) ? game->color_ptr = (game->color_ptr >> 1) & 8355711 : 0;
    game->image[x + y * SCREEN_WIDTH] = game->color_ptr;
}

int				ft_rgb(int r, int g, int b, int transp)
{
    int			color;

    color = b + (g << 8) + (r << 16) + (transp << 24);
    return (color);
}

void    ft_line_direct(t_win *game)
{
    t_vector2d direction;

    game->color = ft_rgb(0, 255, 255, 0);
    direction.x0 = game->player->posx * game->minimapcx;
    direction.y0 = game->player->posy * game->minimapcy;
    direction.x1 = (game->player->posx + game->player->dirx * 4 + \
	cos(game->player->rot) * game->player->stripwidth) * game->minimapcx;
    direction.y1 = (game->player->posy + game->player->diry * 4 + \
	sin(game->player->rot) * game->player->stripwidth) * game->minimapcy; 
    direction.color = ft_rgb(255, 0, 0, 0);
    ft_line_sdl(&direction, game);
}

void    ft_fill_rect(t_ft_rect *rect, t_win *game)
{
    int startx;
    int starty;
    int endx;
    int endy;
    int tmp;

    startx = rect->x * game->minimapcx;
    tmp = startx;
    endx = startx + game->minimapcx;
    starty = rect->y * game->minimapcy;
    endy = starty + game->minimapcy;
    while (starty < endy)
    {
        startx = tmp;
        while (startx < endx)
        {
            game->miniimage[startx + (starty * (int)game->width)] \
			= rect->color;
            startx++;
        }
        starty++;
    }
}

void    ft_putplayer_sdl(t_win *game)
{
    t_ft_rect rect;

    rect.x = game->player->posx;
    rect.y = game->player->posy;
    rect.color = ft_rgb(0, 0, 255, 0);
    ft_fill_rect(&rect, game);
    ft_line_direct(game);
    rect.x = game->player->posx * game->minimapcx;
    rect.y = game->player->posy *  game->minimapcy;
    rect.color = ft_rgb(0, 255, 0, 0);
	if (rect.x < game->width && rect.y < game->height)
    	game->miniimage[(int)rect.x + ((int)rect.y * (int)game->width)] = \
		rect.color;
}

void    ft_drawminimap(t_win *game)
{
    t_ft_rect rect;
    int wall;

    rect.y = 0;
    game->minimapcx = game->width / game->map.miniwidth;
    game->minimapcy = game->height / game->map.miniheight;
    rect.width = game->width;
    rect.hight = game->height;
    rect.color = ft_rgb(255, 0,0,0);
    while (rect.y < game->map.miniheight) {
        rect.x = 0;
        while (rect.x < game->map.miniwidth) {
            wall = game->map.map[rect.y][rect.x];
            if (wall > 0) {
                ft_fill_rect(&rect, game);
            }
            rect.x++;
        }
        rect.y++;
    }
    ft_putplayer_sdl(game);
}

void   ft_move_forward(t_win *game)
{
    if (game->map.map[(int)game->player->posy] \
	[(int)(game->player->posx + game->player->dirx * \
	game->player->moviespeed)] == false)
		game->player->posx += game->player->dirx * game->player->moviespeed;
    if (game->map.map[(int)(game->player->posy + game->player->diry * \
	game->player->moviespeed)][(int) game->player->posx] == false)
		game->player->posy += game->player->diry * game->player->moviespeed ;
    if (game->currentKeyStates[SDL_SCANCODE_D])
        ft_turnleft(game);
    else if (game->currentKeyStates[SDL_SCANCODE_A])
        ft_turnright(game);
}

void   ft_move_backward(t_win *game)
{
    if (game->map.map[(int)game->player->posy] \
	[(int)(game->player->posx - game->player->dirx * \
	game->player->moviespeed)] == false)
		game->player->posx -= game->player->dirx * game->player->moviespeed;
	if (game->map.map[(int)(game->player->posy - game->player->diry * \
	game->player->moviespeed)][(int)game->player->posx] == false)
		game->player->posy -= game->player->diry * game->player->moviespeed;
    if (game->currentKeyStates[SDL_SCANCODE_D])
        ft_turnright(game);
    else if (game->currentKeyStates[SDL_SCANCODE_A])
        ft_turnleft(game);
}

void    ft_move(t_win *game)
{
    if (game->currentKeyStates[SDL_SCANCODE_W])
        ft_move_forward(game);
    else if (game->currentKeyStates[SDL_SCANCODE_S])
        ft_move_backward(game);
    else if (game->currentKeyStates[SDL_SCANCODE_D])
        ft_turnleft(game);
    else if (game->currentKeyStates[SDL_SCANCODE_A])
        ft_turnright(game);
}

void    ft_additonal_engine(t_win *game)
{
	(game->minimapsurface == NULL) ? game->minimapsurface = \
	SDL_CreateRGBSurface(0, game->width, game->height, 32, 0, 0, 0, 0) : 0;
    (game->minimapsurface != NULL) ? game->miniimage = \
	(uint32_t *)game->minimapsurface->pixels : 0;
    ft_drawminimap(game);
}

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
    game->x = game->walls.ptr_texture[game->map.map[game->player->mapy]\
	[game->player->mapx] - 1]->w;
    game->y = game->walls.ptr_texture[game->map.map[game->player->mapy]\
	[game->player->mapx] - 1]->h;
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

