/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 19:13:50 by aezzeddi          #+#    #+#             */
/*   Updated: 2017/09/09 22:05:06 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	get_max_lengths(t_list *files, t_longest *longest)
{
	t_entity *entity;

	while (files)
	{
		entity = files->content;
		if (ft_count_digits(entity->stats->st_nlink) > longest->links)
			longest->links = ft_count_digits(entity->stats->st_nlink);
		if ((int)ft_strlen(entity->owner->username) > longest->username)
			longest->username = ft_strlen(entity->owner->username);
		if ((int)ft_strlen(entity->owner->groupname) > longest->groupname)
			longest->groupname = ft_strlen(entity->owner->groupname);
		if (S_ISCHR(entity->stats->st_mode) || S_ISBLK(entity->stats->st_mode))
		{
			if (ft_count_digits(major(entity->stats->st_rdev)) > longest->major)
				longest->major = ft_count_digits(major(entity->stats->st_rdev));
			if (ft_count_digits(minor(entity->stats->st_rdev)) > longest->minor)
				longest->minor = ft_count_digits(minor(entity->stats->st_rdev));
		}
		else if (ft_count_digits(entity->stats->st_size) > longest->size)
			longest->size = ft_count_digits(entity->stats->st_size);
		files = files->next;
	}
}

void	format_string(char *str, int max_space)
{
	int		spaces;

	spaces = max_space - ft_strlen(str);
	ft_putstr(str);
	while (spaces-- > 0)
		ft_putchar(' ');
}

void	format_number(int value, int max_space)
{
	int		spaces;
	int		len;
	char	*str;

	str = ft_itoa(value);
	len = ft_strlen(str);
	if (str)
		free(str);
	spaces = max_space - len;
	while (spaces-- > 0)
		ft_putchar(' ');
	ft_putnbr(value);
}
