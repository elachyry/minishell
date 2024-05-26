/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:07:48 by akaddour          #+#    #+#             */
/*   Updated: 2024/05/26 17:44:35 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	update_file_list(char **file_list, const char *entry_name)
// {
// 	char	*filename_with_space;
// 	char	*new_file_list;

// 	filename_with_space = ft_strjoin(entry_name, " ");
// 	if (*file_list)
// 		new_file_list = ft_strjoin(*file_list, filename_with_space);
// 	else
// 		new_file_list = ft_strdup(filename_with_space);
// 	free(filename_with_space);
// 	if (*file_list)
// 		free(*file_list);
// 	*file_list = new_file_list;
// }

// void	process_wildcard(t_token **tok, char **file_list)
// {
// 	DIR				*dir;
// 	struct dirent	*entry;

// 	dir = opendir(".");
// 	if (dir == NULL)
// 	{
// 		perror("opendir");
// 		return ;
// 	}
// 	while (1)
// 	{
// 		entry = readdir(dir);
// 		if (entry == NULL)
// 			break ;
// 		if (entry->d_name[0] == '.' && (*tok)->value[0] != '.')
// 			continue ;
// 		if (match(entry->d_name, (*tok)->value))
// 			update_file_list(file_list, entry->d_name);
// 	}
// 	closedir(dir);
// }

// void	process_file_list(char **file_list, t_token **tok)
// {
// 	char	**filenames;
// 	t_token	*new_tok;
// 	t_token	*prev_tok;
// 	int		i;

// 	filenames = ft_split(*file_list, ' ');
// 	free(*file_list);
// 	*file_list = NULL;
// 	if (filenames)
// 	{
// 		(*tok)->value = ft_strdup(filenames[0]);
// 		i = 1;
// 		prev_tok = *tok;
// 		while (filenames[i])
// 		{
// 			new_tok = create_token_node(filenames[i], IDENTIFIER);
// 			add_node_after(prev_tok, new_tok);
// 			prev_tok = new_tok;
// 			i++;
// 		}
// 		free(filenames);
// 	}
// }

// void	handle_wildcard(t_token **tok, char **file_list)
// {
// 	process_wildcard(tok, file_list);
// 	if (*file_list)
// 		process_file_list(file_list, tok);
// }

// t_token	*expand_wildcards(t_token *tokens)
// {
// 	t_token			*tok;
// 	char			*file_list;
// 	char			*tmp;

// 	tok = tokens;
// 	file_list = NULL;
// 	while (tok)
// 	{
// 		if (tok->type == OpeningParenthesis)
// 		{
// 			process_parenthesis(&tok);
// 			continue ;
// 		}
// 		if ((tok->value[0] == '\'' || tok->value[0] == '\"')
// 			&& check_wildcard(tok, &tmp))
// 		{
// 			remove_quotes_and_advance(&tok);
// 			continue ;
// 		}
// 		if (check_wildcard(tok, &tmp))
// 			handle_wildcard(&tok, &file_list);
// 		tok = tok->next;
// 	}
// 	return (tokens);
// }
