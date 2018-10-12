/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_service_control.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylisyak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 00:33:45 by ylisyak           #+#    #+#             */
/*   Updated: 2018/10/12 16:23:04 by ylisyak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

char	**ft_doublerelloc_and_path(char **src, char *word, int size, char *path)
{
	if (src == NULL)
		return (ft_doub_part_one(word, path));
	else
		return (ft_doub_part_two(src, word, size, path));
}

char	**ft_doublerelloc(char **src, char *word, int size)
{
	if (src == NULL)
		return (ft_doub_one(word));
	else
		return (ft_doub_two(src, word, size));
}

void	ft_review_needed_folders(char *path, t_win *c_cl)
{
	c_cl->ofpresent = c_cl->nfpresent;
	(!ft_strcmp(path, "./imgs/ceiling/")) ? c_cl->nfpresent++ : 0;
	(!ft_strcmp(path, "./music/tracks/")) ? c_cl->nfpresent++ : 0;
	(!ft_strcmp(path, "./imgs/menu_elements/")) ? c_cl->nfpresent++ : 0;
	(!ft_strcmp(path, "./imgs/main_elements/")) ? c_cl->nfpresent++ : 0;
	(!ft_strcmp(path, "./imgs/walls/")) ? c_cl->nfpresent++ : 0;
	(!ft_strcmp(path, "./imgs/flats/")) ? c_cl->nfpresent++ : 0;
	(!ft_strcmp(path, "./fonts/")) ? c_cl->nfpresent++ : 0;
	(c_cl->ofpresent == c_cl->nfpresent) ? ft_error_folder() : 0;
}

void	ft_help_count_second_part(char *path, t_win *c_cl, \
		struct dirent *entry, int file_count)
{
	(!ft_strcmp(path, "./imgs/main_elements/")) ? (c_cl->main.names =\
ft_doublerelloc(c_cl->main.names, entry->d_name, file_count)) && \
(c_cl->main.names_with_path = ft_doublerelloc_and_path\
(c_cl->main.names_with_path, entry->d_name,\
	file_count, "./imgs/main_elements/")) : 0;
	(!ft_strcmp(path, "./imgs/walls/")) ? (c_cl->walls.names =\
ft_doublerelloc(c_cl->walls.names, entry->d_name, file_count)) && \
(c_cl->walls.names_with_path = ft_doublerelloc_and_path\
(c_cl->walls.names_with_path, entry->d_name,\
	file_count, "./imgs/walls/")) : 0;
	(!ft_strcmp(path, "./imgs/flats/")) ? (c_cl->flats.names =\
ft_doublerelloc(c_cl->flats.names, entry->d_name, file_count)) && \
(c_cl->flats.names_with_path = ft_doublerelloc_and_path\
(c_cl->flats.names_with_path, entry->d_name,\
	file_count, "./imgs/flats/")) : 0;
	(!ft_strcmp(path, "./imgs/skybox/")) ? (c_cl->skybox.names =\
ft_doublerelloc(c_cl->flats.names, entry->d_name, file_count)) && \
(c_cl->skybox.names_with_path = ft_doublerelloc_and_path\
(c_cl->skybox.names_with_path, entry->d_name,\
	file_count, "./imgs/skybox/")) : 0;
	(!ft_strcmp(path, "./fonts/") && !ft_strcmp("wolfenstein.ttf",\
entry->d_name)) ? (c_cl->main.font =\
TTF_OpenFont("./fonts/wolfenstein.ttf", 140)) : 0;
}

void	ft_help_count(char *path, t_win *c_cl, struct dirent *entry,\
int file_count)
{
	(!ft_strcmp(path, "./imgs/ceiling/")) ? (c_cl->ceiling.names =\
	ft_doublerelloc(c_cl->ceiling.names, entry->d_name, file_count)) && \
(c_cl->ceiling.names_with_path = ft_doublerelloc_and_path\
(c_cl->ceiling.names_with_path, entry->d_name, file_count,\
"./imgs/ceiling/")) : 0;
	(!ft_strcmp(path, "./music/tracks/")) ? (c_cl->music.track_names =\
ft_doublerelloc(c_cl->music.track_names, entry->d_name, file_count)) && \
(c_cl->music.track_name_and_path = ft_doublerelloc_and_path\
(c_cl->music.track_name_and_path, entry->d_name,\
	file_count, "./music/tracks/")) : 0;
	(!ft_strcmp(path, "./imgs/menu_elements/")) ? (c_cl->menu.names =\
ft_doublerelloc(c_cl->menu.names, entry->d_name, file_count)) && \
(c_cl->menu.names_with_path = ft_doublerelloc_and_path\
(c_cl->menu.names_with_path, entry->d_name,\
	file_count, "./imgs/menu_elements/")) : 0;
	ft_help_count_second_part(path, c_cl, entry, file_count);
}
