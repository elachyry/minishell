/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:07:48 by akaddour          #+#    #+#             */
/*   Updated: 2024/05/23 02:50:33 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	process_pattern(const char **string, const char **pattern, \
const char **str_backup, const char **pattern_backup)
{
	if (**pattern == '*')
	{
		*pattern_backup = ++(*pattern);
		*str_backup = *string;
	}
	else if (**pattern == **string)
	{
		(*pattern)++;
		(*string)++;
	}
	else if (*pattern_backup)
	{
		*pattern = *pattern_backup;
		*string = ++(*str_backup);
	}
	else
		return (0);
	return (1);
}

int	match(const char *string, const char *pattern)
{
	const char	*str_backup;
	const char	*pattern_backup;

	str_backup = NULL;
	pattern_backup = NULL;
	while (*string)
	{
		if (!process_pattern(&string, &pattern, &str_backup, &pattern_backup))
			return (0);
	}
	while (*pattern == '*')
		pattern++;
	return (!*pattern);
}

void	process_parenthesis(t_token **tok)
{
	while (*tok && (*tok)->type == OpeningParenthesis)
		*tok = (*tok)->next;
	while (*tok && (*tok)->type != ClosingParenthesis)
		*tok = (*tok)->next;
	while (*tok && (*tok)->type == ClosingParenthesis)
		*tok = (*tok)->next;
}

int	check_wildcard(t_token *tok, char **tmp)
{
	int	has_wildcard;

	has_wildcard = 0;
	*tmp = tok->value;
	while (**tmp)
	{
		if (**tmp == '*')
		{
			has_wildcard = 1;
			break ;
		}
		(*tmp)++;
	}
	return (has_wildcard);
}

void	remove_quotes_and_advance(t_token **tok)
{
	char	*tmp;

	tmp = remove_all_quotes(*tok, (*tok)->value);
	free((*tok)->value);
	(*tok)->value = tmp;
	if (*tok)
		*tok = (*tok)->next;
}

void	update_file_list(char **file_list, const char *entry_name)
{
	char	*filename_with_space;
	char	*new_file_list;

	filename_with_space = ft_strjoin(entry_name, " ");
	if (*file_list)
		new_file_list = ft_strjoin(*file_list, filename_with_space);
	else
		new_file_list = ft_strdup(filename_with_space);
	free(filename_with_space);
	if (*file_list)
		free(*file_list);
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
	free(*file_list);
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
		free(filenames);
	}
}

t_token	*expand_wildcards(t_token *tokens)
{
	t_token			*tok;
	char			*file_list;
	char			*tmp;

	tok = tokens;
	file_list = NULL;
	while (tok)
	{
		if (tok->type == OpeningParenthesis)
		{
			process_parenthesis(&tok);
			continue ;
		}
		if ((tok->value[0] == '\'' || tok->value[0] == '\"') && check_wildcard(tok, &tmp))
		{
			remove_quotes_and_advance(&tok);
			continue ;
		}
		if (check_wildcard(tok, &tmp))
		{
			process_wildcard(&tok, &file_list);
			if (file_list)
				process_file_list(&file_list, &tok);
		}
		tok = tok->next;
	}
	return (tokens);
}
