/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylisyak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 20:53:46 by ylisyak           #+#    #+#             */
/*   Updated: 2018/10/10 20:53:48 by ylisyak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void		ft_error_folder(void)
{
	ft_putstr("\33[0;31m");
	ft_putstr("PUT FOLDER BACK!!!");
	exit(1);
}

void		ft_error_buzz(void)
{
	ft_putstr_fd("Error: BUFF_SIZE must be grater then 0\n", 2);
	exit(1);
}

void		ft_error_gnl(t_win *params)
{
	ft_putstr("Error: get_next_line returned -1.\n");
	free(params->map.line);
	exit(1);
}

void		ft_error_alloc(void)
{
	ft_putstr("Error: allocate memory.\n");
	exit(1);
}

void		ft_error_gen(char *av)
{
	char	*notify;
	char	*tmp;

	notify = ft_strnew(1);
	tmp = ft_strjoin(notify, "error: ");
	free(notify);
	notify = ft_strjoin(tmp, strerror(errno));
	free(tmp);
	tmp = ft_strjoin(notify, " for ");
	free(notify);
	notify = ft_strjoin(tmp, av);
	free(tmp);
	tmp = ft_strjoin(notify, "\n");
	free(notify);
	ft_putstr_fd(tmp, 2);
	free(tmp);
	exit(1);
}
