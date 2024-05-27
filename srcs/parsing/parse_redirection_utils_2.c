/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection_utils_2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 22:41:58 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/27 10:46:40 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_cmd_args(t_token **tokens)
{
	t_token	*tmp;
	int		count;

	tmp = *tokens;
	count = 0;
	while (tmp && tmp->next)
	{
		if (tmp && tmp->next->next && tmp->next->next->type == IDENTIFIER
			&& (tmp->type >= 1 && tmp->type <= 4))
		{
			tmp = tmp->next->next;
			while (tmp && tmp->type == IDENTIFIER)
			{
				count++;
				tmp = tmp->next;
			}
			continue ;
		}
		tmp = tmp->next;
	}
	return (count);
}

static void	get_cmd_args_3(t_token *tmp, t_token **tokens, char **cmd, int i)
{
	t_token	*to_delete;

	while (tmp && tmp->next)
	{
		if (tmp && tmp->next->next && tmp->next->next->type == IDENTIFIER
			&& (tmp->type >= 1 && tmp->type <= 4))
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

static void	help_function(t_ast_node **redirection_node, t_token *ptr, \
	t_bool is_parenth, char **cmd)
{
	char	*here_name;

	here_name = g_shell_data.simple_cmd->here_name;
	if (is_parenth)
	{
		(*redirection_node)->left = parse_parenthese(&ptr);
		(*redirection_node)->right
			= new_ast_file_node(ptr->next->next, here_name);
		(*redirection_node)->right->right
			= parse_redirection(&ptr->next->next->next);
	}
	else
	{
		if (cmd[0] != NULL)
		{
			(*redirection_node)->left = new_ast_node(IDENTIFIER);
			(*redirection_node)->left->args = cmd;
		}
		(*redirection_node)->right
			= parse_command(&ptr->next, false, here_name);
	}
}

//handle if the cmd starts with redirecion
//second if handle when command comes after the file ex: >a cat <b >>c
t_ast_node	*cmd_before_red(t_token **tokens, t_token *ptr, t_bool is_parenth)
{
	t_ast_node	*redirection_node;
	t_token		*tmp;
	char		**cmd;
	int			counts[2];

	g_shell_data.simple_cmd->here_name
		= get_here_doc_path((*tokens)->type);
	redirection_node = new_ast_node((*tokens)->type);
	counts[0] = count_cmd_args(tokens);
	tmp = *tokens;
	*tokens = NULL;
	cmd = malloc(sizeof(char *) * (counts[0] + 1));
	if (!cmd)
		return (NULL);
	counts[1] = 0;
	get_cmd_args_3(tmp, tokens, cmd, counts[1]);
	help_function(&redirection_node, ptr, is_parenth, cmd);
	return (redirection_node);
}
