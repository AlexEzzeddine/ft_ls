/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 11:09:17 by aezzeddi          #+#    #+#             */
/*   Updated: 2017/09/09 22:07:36 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

extern t_ls_options g_ls_options;

int		parse_option(char option)
{
	g_ls_options.one_per_line = (option == '1') ? 1 : g_ls_options.one_per_line;
	g_ls_options.long_format = (option == 'l') ? 1 : g_ls_options.long_format;
	g_ls_options.recursive = (option == 'R') ? 1 : g_ls_options.recursive;
	g_ls_options.show_all = (option == 'a') ? 1 : g_ls_options.show_all;
	g_ls_options.reversed = (option == 'r') ? 1 : g_ls_options.reversed;
	g_ls_options.order_by_time = (option == 't') ?
		1 : g_ls_options.order_by_time;
	return (ft_strcount("Rlrta1", option));
}

void	parse_options(char *options)
{
	int i;

	i = 0;
	while (options[++i])
		if (!parse_option(options[i]))
			error_wrong_option(options[i]);
}

void	parse_entity(char *entity_name)
{
	t_entity *entity;

	entity = create_entity(entity_name, NULL);
	if (entity->error)
		ft_sorted_list_insert(&(g_ls_options.errors),
			ft_lstnew(entity, sizeof(t_entity)), compare_entities);
	else if (S_ISDIR(entity->stats->st_mode)
		|| (S_ISLNK(entity->stats->st_mode) && !g_ls_options.long_format))
		ft_sorted_list_insert(&(g_ls_options.folders),
			ft_lstnew(entity, sizeof(t_entity)), compare_entities);
	else
		ft_sorted_list_insert(&(g_ls_options.non_folders),
			ft_lstnew(entity, sizeof(t_entity)), compare_entities);
}

void	parse_arguments(int argc, char **argv)
{
	int i;
	int end_of_params;

	i = 1;
	end_of_params = 0;
	while (i < argc && argv[i][0] == '-'
		&& ft_strlen(argv[i]) > 1 && !end_of_params)
	{
		end_of_params = !ft_strcmp(argv[i], "--");
		if (!end_of_params)
			parse_options(argv[i]);
		i++;
	}
	while (i < argc)
	{
		parse_entity(argv[i]);
		i++;
	}
}
