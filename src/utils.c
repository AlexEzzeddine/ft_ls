/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 18:46:19 by aezzeddi          #+#    #+#             */
/*   Updated: 2017/09/12 08:05:37 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	free_entity(void *content, size_t size)
{
	t_entity *entity;

	(void)size;
	entity = content;
	free(entity->name);
	free(entity->path);
	free(entity->stats);
	free(entity->owner->username);
	free(entity->owner->groupname);
	free(entity->owner);
	ft_lstdel(&entity->entities, &free_entity);
	free(entity);
}

time_t	*get_time(t_entity *entity)
{
	return (&entity->stats->st_mtime);
}
