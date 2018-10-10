/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylisyak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 18:48:10 by ylisyak           #+#    #+#             */
/*   Updated: 2018/10/10 23:50:10 by ylisyak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void		ft_turnleft(t_win *game)
{
	double	cosinus;
	double	sinus;

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
	game->player->planey = game->player->oldplanex * sinus + \
							game->player->planey * cosinus;
}

void		ft_turnright(t_win *game)
{
	double	cosinus;
	double	sinus;

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

void		ft_move_forward(t_win *game)
{
	if (game->map.map[(int)game->player->posy]\
			[(int)(game->player->posx + game->player->dirx * \
				game->player->moviespeed)] == false)
		game->player->posx += game->player->dirx * game->player->moviespeed;
	if (game->map.map[(int)(game->player->posy + \
	game->player->diry * game->player->moviespeed)]\
[(int)game->player->posx] == false)
		game->player->posy += game->player->diry * game->player->moviespeed;
	if (game->currentKeyStates[SDL_SCANCODE_D])
		ft_turnleft(game);
	else if (game->currentKeyStates[SDL_SCANCODE_A])
		ft_turnright(game);
}

void		ft_move_backward(t_win *game)
{
	if (game->map.map[(int)game->player->posy]\
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

void		ft_move(t_win *game)
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
