/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 18:51:51 by aezzeddi          #+#    #+#             */
/*   Updated: 2017/09/12 07:49:42 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

extern t_ls_options g_ls_options;

void	show_size(t_entity *entity, t_longest *longest)
{
	int max_length;

	max_length = (longest->major + longest->minor) ?
		MAX(longest->size, longest->major + longest->minor + 3) :
			longest->size;
	if (S_ISCHR(entity->stats->st_mode) || S_ISBLK(entity->stats->st_mode))
	{
		format_number(major(entity->stats->st_rdev), longest->major + 1);
		ft_putstr(", ");
		format_number(minor(entity->stats->st_rdev), longest->minor);
		ft_putchar(' ');
	}
	else
	{
		format_number(entity->stats->st_size, max_length);
		ft_putchar(' ');
	}
}

void	show_date(t_entity *entity)
{
	char *str;

	str = ctime(get_time(entity));
	write(1, str + 4, 3);
	ft_putchar(' ');
	write(1, str + 8, 2);
	ft_putchar(' ');
	if (ABS(entity->stats->st_mtime - time(0)) > 6 * MONTH)
		write(1, str + 19, 5);
	else
		write(1, str + 11, 5);
	ft_putchar(' ');
	free(str);
}

void	show_link_dest(t_entity *entity)
{
	char	buf[PATH_MAX];
	int		len;

	len = readlink(entity->path, buf, PATH_MAX);
	buf[len] = '\0';
	ft_putstr(" -> ");
	ft_putstr(buf);
}

void	print_entity(t_entity *entity, t_longest *longest)
{
	if (entity->error)
		error_non_exist(entity);
	else if (g_ls_options.long_format)
	{
		show_rights(entity);
		format_number(entity->stats->st_nlink, longest->links);
		ft_putchar(' ');
		format_string(entity->owner->username, longest->username + 2);
		format_string(entity->owner->groupname, longest->groupname + 2);
		show_size(entity, longest);
		show_date(entity);
		ft_putstr(entity->name);
		if (S_ISLNK(entity->stats->st_mode))
			show_link_dest(entity);
		ft_putchar('\n');
	}
	else
		ft_putendl(entity->name);
}

void	show_headers(t_entity *folder)
{
	static int first_time = 1;

	if (!first_time
		|| ft_lstlen(g_ls_options.errors)
		|| ft_lstlen(g_ls_options.non_folders)
		|| ft_lstlen(g_ls_options.folders) > 1)
	{
		if (!first_time || ft_lstlen(g_ls_options.non_folders))
			ft_putchar('\n');
		ft_putstr(folder->path);
		ft_putendl(":");
	}
	if (folder->error)
		error_no_permission(folder);
	if (g_ls_options.long_format && folder->entities)
	{
		ft_putstr("total ");
		ft_putnbr(folder->total_blocks);
		ft_putchar('\n');
	}
	first_time = 0;
}
