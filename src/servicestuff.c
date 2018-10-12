/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   servicestuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylisyak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 00:41:26 by ylisyak           #+#    #+#             */
/*   Updated: 2018/10/12 19:21:51 by ylisyak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

int					ft_count_files(char *path, t_win *c_cl)
{
	int				file_count;
	DIR				*dirp;
	struct dirent	*entry;

	file_count = 0;
	dirp = opendir(path);
	if (!dirp)
		ft_error_folder();
	ft_review_needed_folders(path, c_cl);
	while ((entry = readdir(dirp)) != NULL)
	{
		if (entry->d_type == DT_REG && ft_strcmp(entry->d_name, ".DS_Store"))
		{
			ft_help_count(path, c_cl, entry, file_count);
			file_count++;
		}
	}
	closedir(dirp);
	return (file_count);
}

void				ft_init_rander(t_win *c_cl)
{
	Uint32			render_flags;

	render_flags = (SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	c_cl->grenderer = SDL_CreateRenderer(c_cl->window, -1, render_flags);
	(c_cl->grenderer == NULL) ?\
	ft_truble_win("Render could not be created! SDL Error: ", c_cl) : 0;
}

void				ft_init_window(t_win *c_cl)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		ft_putstr(SDL_GetError());
		(c_cl->statement = FT_FALSE);
	}
	if (!(c_cl->statement & FT_FALSE))
	{
		(TTF_Init() == -1) ? ft_error_ttf_init() : 0;
		(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) ? \
		ft_putstr("Warning: Linear texture filtering not enabled!\n") : 0;
		c_cl->window = SDL_CreateWindow("Wolf3D", SDL_WINDOWPOS_CENTERED, \
		SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		(c_cl->window == NULL) ?\
		ft_truble_win("Window could not be created! SDL_Error: ", c_cl) : 0;
		(!(c_cl->statement & FT_FALSE)) ? ft_init_audios(c_cl) : 0;
		(!(c_cl->statement & FT_FALSE)) ? ft_init_rander(c_cl) : 0;
		(!(c_cl->statement & FT_FALSE)) ? ft_init_images(c_cl) : 0;
	}
}

void				sdl_close(t_win *c_sc)
{
	(c_sc->music.track != NULL) ? Mix_FreeMusic(c_sc->music.track) : 0;
	SDL_DestroyTexture(c_sc->gtexture);
	SDL_DestroyRenderer(c_sc->grenderer);
	SDL_DestroyWindow(c_sc->window);
	c_sc->gtexture = NULL;
	c_sc->window = NULL;
	c_sc->grenderer = NULL;
	c_sc->music.track = NULL;
	Mix_CloseAudio();
	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}
