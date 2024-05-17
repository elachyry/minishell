/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:58:24 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/16 14:20:50 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//handle if the cmd starts with redirecion
//second if handle when command comes after the file ex: >a cat <b >>c
static t_ast_node	*help_func(t_token **tokens, t_token *ptr)
{
	t_ast_node	*redirection_node;

	if ((*tokens)->type == DoubleLessThanOperator)
		g_shell_data.simple_cmd->nbr_here_doc++;
	redirection_node = new_ast_node((*tokens)->type);
	*tokens = NULL;
	redirection_node->left = parse_redirection(tokens);
	if (redirection_node->left == NULL
		&& ptr->next->next
		&& ptr->next->next->type == IDENTIFIER)
		redirection_node->left = parse_command(&ptr->next->next, true);
	redirection_node->right = parse_command(&ptr->next, false);
	return (redirection_node);
}

//handle if the redirecion comes after cmd
static t_ast_node	*help_func_2(t_token **tokens, t_token *next, t_token *ptr)
{
	t_ast_node	*redirection_node;

	if (next->type == DoubleLessThanOperator)
		g_shell_data.simple_cmd->nbr_here_doc++;
	redirection_node = new_ast_node(next->type);
	(*tokens)->next = NULL;
	if (next->next->next && next->next->next->type == IDENTIFIER)
		redirection_node->left = parse_cmd_sep_args(ptr, next->next->next);
	else
		redirection_node->left = parse_redirection(&ptr);
	redirection_node->right = parse_command(&next->next, false);
	return (redirection_node);
}

//this function for parsing the redirections
//by creating a node type of the redirecion
t_ast_node	*parse_redirection(t_token **tokens)
{
	t_token		*ptr;
	t_token		*next;

	if (!tokens || !*tokens)
		return (NULL);
	ptr = *tokens;
	if ((*tokens)->type == LessThanOperator
		|| (*tokens)->type == DoubleLessThanOperator
		|| (*tokens)->type == GreaterThanOperator
		|| (*tokens)->type == DoubleGreaterThanOperator)
		return (help_func(tokens, ptr));
	while (*tokens && (*tokens)->next)
	{
		next = (*tokens)->next;
		if (next->type == LessThanOperator
			|| next->type == DoubleLessThanOperator
			|| next->type == GreaterThanOperator
			|| next->type == DoubleGreaterThanOperator)
			return (help_func_2(tokens, next, ptr));
		*tokens = next;
	}
	return (parse_parenthese(&ptr));
}
