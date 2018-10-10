/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylisyak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 21:15:09 by ylisyak           #+#    #+#             */
/*   Updated: 2018/10/10 22:38:23 by ylisyak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void			ft_error_textures(char *str, char *strtow)
{
	ft_putstr("\33[0;31m");
	ft_putstr("No enough ");
	ft_putstr(str);
	ft_putstr("<--- this textures. Please load more.");
	ft_putstr("\nOR PUT BACK FOLDER NAME OR CREATE: ");
	ft_putstr(strtow);
	ft_putstr(" folder.");
	exit(1);
}
