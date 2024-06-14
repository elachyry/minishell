/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 22:41:58 by melachyr          #+#    #+#             */
/*   Updated: 2024/06/02 17:21:22 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	count_cmd_args_2(t_token *next, int *count)
{
	t_token	*tmp;

	tmp = next;
	while (tmp && tmp->next)
	{
		if (tmp && tmp->next->next && tmp->next->next->type
			== IDENTIFIER && (tmp->type == LessThanOperator
				|| tmp->type == DoubleLessThanOperator
				|| tmp->type == GreaterThanOperator
				|| tmp->type == DoubleGreaterThanOperator))
		{
			tmp = tmp->next->next;
			while (tmp && tmp->type == IDENTIFIER)
			{
				(*count)++;
				tmp = tmp->next;
			}
			continue ;
		}
		tmp = tmp->next;
	}
}

static void	get_cmd_args_2(t_token *next, t_token **tokens, char **cmd, int i)
{
	t_token	*tmp;
	t_token	*to_delete;

	tmp = next;
	while (tmp && tmp->next)
	{
		if (tmp && tmp->next->next && tmp->next->next->type
			== IDENTIFIER && (tmp->type == LessThanOperator
				|| tmp->type == DoubleLessThanOperator
				|| tmp->type == GreaterThanOperator
				|| tmp->type == DoubleGreaterThanOperator))
		{
			tmp = tmp->next->next;
			while (tmp && tmp->type == IDENTIFIER)
			{
				cmd[i++] = ft_strdup(tmp->value);
				to_delete = tmp;
				tmp = tmp->next;
				remove_node(tokens, to_delete);
			}
			continue ;
		}
		tmp = tmp->next;
	}
	cmd[i] = NULL;
}

static char	**get_cmd_args(t_token **tokens, t_token *ptr, int *i, int count)
{
	t_token	*tmp;
	t_token	*to_delete;
	char	**cmd;

	cmd = gc_malloc(sizeof(char *) * (count + 1));
	if (!cmd)
		return (NULL);
	tmp = ptr;
	*i = 0;
	while (tmp && tmp->type == IDENTIFIER)
	{
		cmd[*i] = ft_strdup(tmp->value);
		to_delete = tmp;
		tmp = tmp->next;
		remove_node(tokens, to_delete);
		(*i)++;
	}
	return (cmd);
}

char	*get_here_doc_path(t_token_type type)
{
	char	*here_name;

	here_name = NULL;
	if (type == DoubleLessThanOperator)
	{
		here_name = ft_strjoin("/tmp/.", get_here_doc_name());
		g_shell_data.simple_cmd->here_docs_files
		[g_shell_data.simple_cmd->here_index++] = here_name;
	}
	return (here_name);
}

//handle if the redirecion comes after cmd
t_ast_node	*cmd_after_red(t_token **tokens, t_token *next, t_token *ptr)
{
	t_ast_node	*redirection_node;
	t_token		*tmp;
	char		**cmd;
	char		*here_name;
	int			counts[2];

	counts[0] = 0;
	redirection_node = new_ast_node(next->type);
	here_name = get_here_doc_path((*tokens)->next->type);
	(*tokens)->next = NULL;
	tmp = ptr;
	while (tmp && tmp->type == IDENTIFIER)
	{
		counts[0]++;
		tmp = tmp->next;
	}
	count_cmd_args_2(next, &counts[0]);
	cmd = get_cmd_args(tokens, ptr, &counts[1], counts[0]);
	get_cmd_args_2(next, tokens, cmd, counts[1]);
	redirection_node->left = new_ast_node(IDENTIFIER);
	redirection_node->left->args = cmd;
	redirection_node->right = parse_command(&next->next, false, here_name);
	return (redirection_node);
}
