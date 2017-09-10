/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 18:46:19 by aezzeddi          #+#    #+#             */
/*   Updated: 2017/09/09 22:17:50 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

/*
** if (file->ls->options.time_last_access)
**	return (&entity->stats->st_atime);
** else if (file->ls->options.time_creation)
**	return (&entity->stats->st_ctime);
*/

time_t	*get_time(t_entity *entity)
{
	return (&entity->stats->st_mtime);
}
