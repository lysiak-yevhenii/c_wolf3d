/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_service_malloc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylisyak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 00:32:22 by ylisyak           #+#    #+#             */
/*   Updated: 2018/10/12 16:04:10 by ylisyak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void		free_darray(char **src, int size)
{
	int		i;

	i = 0;
	while (i < size)
		free(src[i++]);
	free(src);
}

char		**ft_doub_part_one(char *word, char *path)
{
	char	*tmp;
	char	**newptr;

	if (!(newptr = (char **)malloc(sizeof(char *) * 1)))
		return (NULL);
	ft_bzero(newptr, sizeof(newptr));
	tmp = ft_strjoin(path, word);
	*newptr = (char *)malloc(sizeof(char) * ft_strlen(tmp));
	ft_strcpy(*newptr, tmp);
	free(tmp);
	return (newptr);
}

char		**ft_doub_part_two(char **src, char *word, int size, char *path)
{
	int		i;
	char	*tmp;
	char	**newptr;
	char	**begin;

	i = 0;
	newptr = (char **)malloc(sizeof(char *) * size + 1);
	begin = newptr;
	while (i < size)
	{
		*newptr = (char *)malloc(sizeof(char) * ft_strlen(*src));
		ft_strcpy(*newptr, *src);
		newptr++;
		src++;
		i++;
	}
	free_darray(src - i, size);
	tmp = ft_strjoin(path, word);
	*newptr = (char *)malloc(sizeof(char) * ft_strlen(tmp));
	ft_strcpy(*newptr, tmp);
	free(tmp);
	return (begin);
}

char		**ft_doub_one(char *word)
{
	char	**newptr;

	if (!(newptr = (char **)malloc(sizeof(char *) * 1)))
		return (NULL);
	newptr[0] = (char *)malloc(sizeof(char) * ft_strlen(word));
	ft_strcpy(*newptr, word);
	return (newptr);
}

char		**ft_doub_two(char **src, char *word, int size)
{
	int		i;
	char	**newptr;
	char	**begin;

	i = 0;
	newptr = (char **)malloc(sizeof(char *) * size + 1);
	begin = newptr;
	while (i < size)
	{
		*newptr = (char *)malloc(sizeof(char) * ft_strlen(*src));
		ft_strcpy(*newptr, *src);
		newptr++;
		src++;
		i++;
	}
	free_darray(src - i, size);
	*newptr = (char *)malloc(sizeof(char) * ft_strlen(word));
	ft_strcpy(*newptr, word);
	return (begin);
}
