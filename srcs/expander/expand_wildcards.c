/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:07:48 by akaddour          #+#    #+#             */
/*   Updated: 2024/06/11 05:37:48 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_file_list(char **file_list, const char *entry_name)
{
	char	*filename_with_space;
	char	*new_file_list;

	filename_with_space = ft_strjoin(entry_name, " ");
	if (*file_list)
		new_file_list = ft_strjoin(*file_list, filename_with_space);
	else
		new_file_list = ft_strdup(filename_with_space);
	*file_list = new_file_list;
}

void	process_wildcard(t_token **tok, char **file_list)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	if (dir == NULL)
	{
		perror("opendir");
		return ;
	}
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (entry->d_name[0] == '.' && (*tok)->value[0] != '.')
			continue ;
		if (match(entry->d_name, (*tok)->value))
			update_file_list(file_list, entry->d_name);
	}
	closedir(dir);
}

void	process_file_list(char **file_list, t_token **tok)
{
	char	**filenames;
	t_token	*new_tok;
	t_token	*prev_tok;
	int		i;

	filenames = ft_split(*file_list, ' ');
	*file_list = NULL;
	if (filenames)
	{
		(*tok)->value = ft_strdup(filenames[0]);
		i = 1;
		prev_tok = *tok;
		while (filenames[i])
		{
			new_tok = create_token_node(filenames[i], IDENTIFIER);
			add_node_after(prev_tok, new_tok);
			prev_tok = new_tok;
			i++;
		}
	}
}

t_bool	process_token(t_token **tok)
{
	if ((*tok)->prev && (*tok)->prev->type == DoubleLessThanOperator)
	{
		*tok = (*tok)->next;
		return (true);
	}
	if ((*tok)->type == OpeningParenthesis)
	{
		process_parenthesis(tok);
		return (true);
	}
	if (((*tok)->value[0] == '\'' || (*tok)->value[0] == '\"') \
		&& check_wildcard(*tok))
	{
		*tok = (*tok)->next;
		return (true);
	}
	return (false);
}

t_token	*expand_wildcards(t_token *tokens)
{
	t_token			*tok;
	char			*file_list;

	tok = tokens;
	file_list = NULL;
	while (tok)
	{
		if (process_token(&tok))
			continue ;
		if (check_wildcard(tok))
		{
			process_wildcard(&tok, &file_list);
			if (file_list)
				process_file_list(&file_list, &tok);
		}
		tok = tok->next;
	}
	return (tokens);
}
