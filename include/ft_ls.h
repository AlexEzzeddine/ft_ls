/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 11:00:58 by aezzeddi          #+#    #+#             */
/*   Updated: 2017/09/16 18:14:25 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <limits.h>
# include <dirent.h>
# include <errno.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>

# define MONTH	(30 * 24 * 60 * 60)

typedef struct stat	t_stat;

typedef struct		s_ls_options
{
	t_list	*folders;
	t_list	*non_folders;
	t_list	*errors;
	int		one_per_line;
	int		long_format;
	int		recursive;
	int		show_all;
	int		reversed;
	int		order_by_time;
}					t_ls_options;

typedef struct		s_longest
{
	int links;
	int username;
	int groupname;
	int size;
	int major;
	int minor;
}					t_longest;

typedef struct		s_owner
{
	char *username;
	char *groupname;
}					t_owner;

typedef struct		s_entity
{
	char	*name;
	char	*path;
	t_owner	*owner;
	t_stat	*stats;
	t_list	*entities;
	int		total_blocks;
	int		error;
}					t_entity;

void				display_files(t_list *files);
void				display_folders(t_list *entities_list);
void				ls(t_entity *folder);
void				core();

int					parse_option(char option);
void				parse_options(char *options);
void				parse_entity(char *entity_name);
void				parse_arguments(int argc, char **argv);

int					compare_entities(void *a, void *b);
t_entity			*create_entity(char *name, char *parent_path);
void				add_entity(t_entity *parent, char *entity_name);
void				discover_children(t_entity *folder);

void				show_size(t_entity *entity, t_longest *longest);
void				show_date(t_entity *entity);
void				show_link_dest(t_entity *entity);
void				print_entity(t_entity *entity, t_longest *longest);
void				show_headers(t_entity *folder);

void				show_rights(t_entity *entity);
void				get_xrights(t_entity *entity, int mode_a,
	int mode_b, char *def);
t_owner				*get_owner(t_entity *entity);
char				*get_username(t_entity *entity);
char				*get_groupname(t_entity *entity);

void				get_max_lengths(t_list *files, t_longest *longest);
void				format_string(char *str, int max_space);
void				format_number(int value, int max_space);

time_t				*get_time(t_entity *entity);
void				free_entity(void *content, size_t size);

void				error_usage();
void				error_no_permission(t_entity *entity);
void				error_wrong_option(char option);
void				error_non_exist(t_entity *entity);
#endif
