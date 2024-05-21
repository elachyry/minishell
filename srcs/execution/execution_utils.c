/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:36:16 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/21 17:49:11 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_files	*new_file_node(char *filename, t_token_type type)
{
	t_files	*node;

	node = malloc(sizeof(t_files));
	if (!node)
		return (NULL);
	node->filename = filename;
	node->type = type;
	node->next = NULL;
	node->is_opened = false;
	return (node);
}

t_files	*lst_file_last(t_files *head)
{
	if (!head)
		return (NULL);
	while (head->next != NULL)
	{
		head = head->next;
	}
	return (head);
}

void	add_lst_file(t_files **head, t_files *node)
{
	t_files	*last;

	if (!head)
		return ;
	if (!*head)
		*head = node;
	else
	{
		last = lst_file_last(*head);
		last->next = node;
	}
}

char	*get_here_doc_name(void)
{
	char	*name;
	char	line[2];
	int		fd;
	int		c;

	name = malloc(sizeof(char) * 12);
	if (name == NULL)
		return (NULL);
	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
	{
		free(name);
		return (NULL);
	}
	c = 0;
	while (c < 11)
	{
		read(fd, line, 1);
		if (ft_isalpha(line[0]))
			name[c++] = line[0];
	}
	name[c] = '\0';
	close(fd);
	return (name);
}
