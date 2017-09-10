/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 18:56:21 by aezzeddi          #+#    #+#             */
/*   Updated: 2017/09/09 22:15:15 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

extern t_ls_options g_ls_options;

int			compare_entities(void *a, void *b)
{
	int result;

	result = 0;
	if (g_ls_options.order_by_time)
	{
		if (*get_time(a) < *get_time(b))
			result = 1;
		else if (*get_time(a) > *get_time(b))
			result = -1;
	}
	if (!result)
		result = ft_strcmp(((t_entity *)a)->name, ((t_entity *)b)->name);
	return (g_ls_options.reversed ? -result : result);
}

t_entity	*create_entity(char *name, char *parent_path)
{
	t_entity *entity;

	entity = malloc(sizeof(t_entity));
	entity->name = ft_strdup(name);
	entity->path = parent_path ?
	ft_strfjoin(ft_strjoin(parent_path, "/"), name) : ft_strdup(entity->name);
	entity->stats = malloc(sizeof(t_stat));
	entity->entities = NULL;
	entity->total_blocks = 0;
	entity->error = 0;
	if (lstat(entity->path, entity->stats) == -1)
		entity->error = errno;
	entity->owner = get_owner(entity);
	return (entity);
}

void		add_entity(t_entity *parent, char *entity_name)
{
	t_entity *entity;

	if (entity_name[0] != '.' || g_ls_options.show_all)
	{
		entity = create_entity(entity_name, parent->path);
		ft_sorted_list_insert(&parent->entities,
			ft_lstnew(entity, sizeof(t_entity)), compare_entities);
		parent->total_blocks += entity->stats->st_blocks;
	}
}

void		discover_children(t_entity *folder)
{
	DIR				*dir_stream;
	struct dirent	*dir_entity;

	dir_stream = opendir(folder->path);
	if (dir_stream)
	{
		while ((dir_entity = readdir(dir_stream)) != NULL)
		{
			add_entity(folder, dir_entity->d_name);
		}
		closedir(dir_stream);
	}
	else
		folder->error = errno;
}
