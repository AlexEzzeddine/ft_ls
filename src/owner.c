/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   owner.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 22:09:47 by aezzeddi          #+#    #+#             */
/*   Updated: 2017/09/09 22:09:24 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	show_rights(t_entity *entity)
{
	ft_putstr(S_ISDIR(entity->stats->st_mode) ? "d" : "");
	ft_putstr(S_ISFIFO(entity->stats->st_mode) ? "p" : "");
	ft_putstr(S_ISCHR(entity->stats->st_mode) ? "c" : "");
	ft_putstr(S_ISBLK(entity->stats->st_mode) ? "b" : "");
	ft_putstr(S_ISREG(entity->stats->st_mode) ? "-" : "");
	ft_putstr(S_ISLNK(entity->stats->st_mode) ? "l" : "");
	ft_putstr(S_ISSOCK(entity->stats->st_mode) ? "s" : "");
	ft_putchar((entity->stats->st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((entity->stats->st_mode & S_IWUSR) ? 'w' : '-');
	get_xrights(entity, S_IXUSR, S_ISUID, "Ssx-");
	ft_putchar((entity->stats->st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((entity->stats->st_mode & S_IWGRP) ? 'w' : '-');
	get_xrights(entity, S_IXGRP, S_ISGID, "Ssx-");
	ft_putchar((entity->stats->st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((entity->stats->st_mode & S_IWOTH) ? 'w' : '-');
	get_xrights(entity, S_IXOTH, S_ISVTX, "Ttx-");
	ft_putstr("  ");
}

void	get_xrights(t_entity *entity, int mode_a,
									int mode_b, char *def)
{
	if (!(entity->stats->st_mode & mode_a) && (entity->stats->st_mode & mode_b))
		ft_putchar(def[0]);
	else if ((entity->stats->st_mode & mode_a)
		&& (entity->stats->st_mode & mode_b))
		ft_putchar(def[1]);
	else
		ft_putchar((entity->stats->st_mode & mode_a) ? def[2] : def[3]);
}

char	*get_username(t_entity *entity)
{
	struct passwd	*user;

	user = getpwuid(entity->stats->st_uid);
	if (user)
		return (ft_strdup(user->pw_name));
	else
		return (ft_itoa(entity->stats->st_uid));
}

char	*get_groupname(t_entity *entity)
{
	struct group	*grp;

	grp = getgrgid(entity->stats->st_gid);
	if (grp)
		return (ft_strdup(grp->gr_name));
	else
		return (ft_itoa(entity->stats->st_gid));
}

t_owner	*get_owner(t_entity *entity)
{
	t_owner *owner;

	owner = malloc(sizeof(t_owner));
	owner->username = get_username(entity);
	owner->groupname = get_groupname(entity);
	return (owner);
}
