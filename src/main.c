/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/16 22:43:45 by aezzeddi          #+#    #+#             */
/*   Updated: 2017/09/09 22:03:57 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

t_ls_options g_ls_options;
const t_longest g_default_length = {0, 0, 0, 1, 0, 0};

void	display_files(t_list *files)
{
	t_list		*file;
	t_longest	longest;

	longest = g_default_length;
	get_max_lengths(files, &longest);
	file = files;
	while (file)
	{
		print_entity(((t_entity *)file->content), &longest);
		file = file->next;
	}
}

void	display_folders(t_list *entities_list)
{
	t_list		*list_node;
	t_entity	*entity;

	list_node = entities_list;
	while (list_node)
	{
		entity = list_node->content;
		ls(entity);
		list_node = list_node->next;
	}
}

void	ls(t_entity *folder)
{
	t_list		*list_node;
	t_entity	*entity;

	discover_children(folder);
	show_headers(folder);
	display_files(folder->entities);
	if (g_ls_options.recursive)
	{
		list_node = folder->entities;
		while (list_node)
		{
			entity = list_node->content;
			if (S_ISDIR(entity->stats->st_mode)
			&& ft_strcmp(entity->name, ".") && ft_strcmp(entity->name, ".."))
				ls(entity);
			list_node = list_node->next;
		}
	}
}

void	core(void)
{
	t_entity *entity;

	display_files(g_ls_options.errors);
	if (!ft_lstlen(g_ls_options.non_folders)
		&& !ft_lstlen(g_ls_options.folders))
	{
		entity = create_entity(".", NULL);
		ft_sorted_list_insert(&g_ls_options.folders,
			ft_lstnew(entity, sizeof(t_entity)), compare_entities);
	}
	display_files(g_ls_options.non_folders);
	display_folders(g_ls_options.folders);
}

int		main(int argc, char **argv)
{
	parse_arguments(argc, argv);
	core();
	return (0);
}
