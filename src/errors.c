/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 19:04:29 by aezzeddi          #+#    #+#             */
/*   Updated: 2017/09/09 22:04:32 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	error_usage(void)
{
	ft_putendl_fd("usage: ls [-1alRrt] [file ...]", 2);
}

void	error_no_permission(t_entity *entity)
{
	ft_putstr_fd("ls: ", 2);
	ft_putstr_fd(entity->name, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(entity->error), 2);
}

void	error_wrong_option(char option)
{
	ft_putstr_fd("ls: illegal option -- ", 2);
	ft_putchar_fd(option, 2);
	ft_putchar_fd('\n', 2);
	error_usage();
	exit(1);
}

void	error_non_exist(t_entity *entity)
{
	ft_putstr_fd("ls: ", 2);
	if (entity->name[0] == '\0')
		ft_putstr_fd("fts_open", 2);
	else
		ft_putstr_fd(entity->name, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	if (entity->name[0] == '\0')
		exit(1);
}
