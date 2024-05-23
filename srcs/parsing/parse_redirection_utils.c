/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 22:41:58 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/22 20:25:03 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void	help_func(t_token *tmp, char **cmd)
// {
// 	*cmd = ft_strjoin(*cmd, tmp->value);
// 	*cmd = ft_strjoin(*cmd, "\n");
// }

static void	extrac_cmd_args(t_token **tokens, int *count)
{
	t_token	*tmp;
	// t_token	*to_delete;

	tmp = *tokens;
	while (tmp && tmp->next)
	{
		if (tmp && tmp->next->next && tmp->next->next->type == IDENTIFIER
			&& (tmp->type == LessThanOperator
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

//handle if the cmd starts with redirecion
//second if handle when command comes after the file ex: >a cat <b >>c
t_ast_node	*cmd_before_red(t_token **tokens, t_token *ptr, t_bool is_parenth)
{
	t_ast_node	*redirection_node;
	t_token		*tmp;
	t_token		*to_delete;
	char		**cmd;
	int			count;
	int			i;

	if ((*tokens)->type == DoubleLessThanOperator)
		g_shell_data.simple_cmd->nbr_here_doc++;
	redirection_node = new_ast_node((*tokens)->type);
	count = 0;
	extrac_cmd_args(tokens, &count);
	tmp = *tokens;
	*tokens = NULL;
	cmd = malloc(sizeof(char *) * (count + 1));
	if (!cmd)
		return (NULL);
	i = 0;
	while (tmp && tmp->next)
	{
		if (tmp && tmp->next->next && tmp->next->next->type == IDENTIFIER
			&& (tmp->type == LessThanOperator
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
	if (is_parenth)
	{
		redirection_node->left = parse_parenthese(&ptr);
		redirection_node->right = new_ast_file_node(ptr->next->next);
		redirection_node->right->right
			= parse_redirection(&ptr->next->next->next);
	}
	else
	{
		if (cmd[0] != NULL)
		{
			redirection_node->left = new_ast_node(IDENTIFIER);
			redirection_node->left->args = cmd;
		}
		redirection_node->right = parse_command(&ptr->next, false);
	}
	return (redirection_node);
}

static void	extrac_cmd_args_2(t_token *next, int *count)
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

//handle if the redirecion comes after cmd
t_ast_node	*cmd_after_red(t_token **tokens, t_token *next, t_token *ptr)
{
	t_ast_node	*redirection_node;
	t_token		*to_delete;
	t_token		*tmp;
	char		**cmd;
	int			count;
	int			i;

	if (next->type == DoubleLessThanOperator)
		g_shell_data.simple_cmd->nbr_here_doc++;
	count = 0;
	redirection_node = new_ast_node(next->type);
	(*tokens)->next = NULL;
	tmp = ptr;
	while (tmp && tmp->type == IDENTIFIER)
	{
		count++;
		tmp = tmp->next;
	}
	extrac_cmd_args_2(next, &count);
	cmd = malloc(sizeof(char *) * (count + 1));
	if (!cmd)
		return (NULL);
	tmp = ptr;
	i = 0;
	while (tmp && tmp->type == IDENTIFIER)
	{
		cmd[i] = ft_strdup(tmp->value);
		to_delete = tmp;
		tmp = tmp->next;
		remove_node(tokens, to_delete);
		i++;
	}
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
				cmd[i] = ft_strdup(tmp->value);
				to_delete = tmp;
				tmp = tmp->next;
				remove_node(tokens, to_delete);
				i++;
			}
			continue ;
		}
		tmp = tmp->next;
	}
	cmd[i] = NULL;
	redirection_node->left = new_ast_node(IDENTIFIER);
	redirection_node->left->args = cmd;
	redirection_node->right = parse_command(&next->next, false);
	return (redirection_node);
}
