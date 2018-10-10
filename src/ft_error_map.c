/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylisyak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 21:15:09 by ylisyak           #+#    #+#             */
/*   Updated: 2018/10/10 22:36:22 by ylisyak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void		ft_error_minus(void)
{
	ft_putstr("");
	ft_putstr("NOT WALID MAP! \'-\' is preasent! You funny...");
	ft_putstr("\nTry harder... (>_>) You know I hate you... ? .");
	ft_putstr("\nYou trying to kick my ass. I hope you will fail.");
	exit(1);
}

void		ft_error_notdigit(void)
{
	ft_putstr("Error: not digit value.\n");
	exit(1);
}

void		ft_error_hex(void)
{
	ft_putstr("Error: heximal input invalid.\n");
	exit(1);
}

void		ft_error_len(void)
{
	ft_putstr("Error: row not equal in each coloms.\n");
	exit(1);
}

void		ft_error_not_empty(void)
{
	ft_putstr("Error: try another point there to put player start position.\n");
	exit(1);
}
