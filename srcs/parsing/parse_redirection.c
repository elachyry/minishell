/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:58:24 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/19 14:02:08 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//handle if the cmd starts with redirecion
//second if handle when command comes after the file ex: >a cat <b >>c
static t_ast_node	*help_func(t_token **tokens, t_token *ptr)
{
	t_ast_node	*redirection_node;
	// t_token		*tmp;

	// dprintf(2, "ggggg in red next = %s\n", (*tokens)->next->value);
	// dprintf(2, "1 in red next = %s\n", (*tokens)->next->value);
	// dprintf(2, "1 in red next next = %s\n", (*tokens)->next->next->value);
	if ((*tokens)->type == DoubleLessThanOperator)
		g_shell_data.simple_cmd->nbr_here_doc++;
	redirection_node = new_ast_node((*tokens)->type);
	// tmp = *tokens;
	t_token	*tmp = *tokens;
	t_token	*tmp2 = *tokens;
	*tokens = NULL;
	// dprintf(2, "1 in ffff = %p\n", tmp);
	// if (tmp && tmp->next && tmp->next->next && tmp->next->next->type == IDENTIFIER)
	// 	redirection_node->left = parse_cmd_sep_args(ptr, tmp->next->next);
	// else
	redirection_node->left = parse_redirection(tokens);
	// dprintf(2, "left %p\n",redirection_node->left);
	// dprintf(2, "tmp %s\n", tmp->value);
	if (redirection_node->left == NULL
		&& ptr->next->next
		&& ptr->next->next->type == IDENTIFIER)
	{
		while (tmp && tmp->next && (tmp->type == LessThanOperator
		|| tmp->type == DoubleLessThanOperator
		|| tmp->type == GreaterThanOperator
		|| tmp->type == DoubleGreaterThanOperator
		|| tmp->type == IDENTIFIER))
		{
			// dprintf(2, "in while %s\n", tmp->value);
			tmp = tmp->next;
			ptr = ptr->next;
		}
		// dprintf(2, "result  %s\n", tmp->value);
		while (tmp && tmp->type == IDENTIFIER)
		{
			tmp = tmp->prev;
			ptr = ptr->prev;
		}
		// dprintf(2, "result2  %s\n", tmp->next->value);
		tmp = tmp->next->next;
		// dprintf(2, "result3  %s\n", tmp->value);
		// dprintf(2, "ptr next  %s\n", ptr->next->value);
		ptr->next->next = NULL;
		ptr = tmp2;
		if (tmp && tmp->type == IDENTIFIER)
			redirection_node->left = parse_cmd_sep_args(ptr->next->next, tmp);
		else
			redirection_node->left = parse_command(&ptr->next->next, true);
		// redirection_node->left = parse_command(&ptr->next->next, true);
	}
	redirection_node->right = parse_command(&ptr->next, false);
	return (redirection_node);
}

//handle if the redirecion comes after cmd
static t_ast_node	*help_func_2(t_token **tokens, t_token *next, t_token *ptr)
{
	t_ast_node	*redirection_node;

	// dprintf(2, "1 in red = %s\n", (*tokens)->value);
	if (next->type == DoubleLessThanOperator)
		g_shell_data.simple_cmd->nbr_here_doc++;
	redirection_node = new_ast_node(next->type);
	// dprintf(2, "2 in red = %s\n", (*tokens)->value);
	(*tokens)->next = NULL;
	// dprintf(2, "test %s\n", next->next->next->value);
	t_token	*tmp = next;
	t_token	*tmp2 = next;
	while (tmp && tmp->next && (tmp->type == LessThanOperator
		|| tmp->type == DoubleLessThanOperator
		|| tmp->type == GreaterThanOperator
		|| tmp->type == DoubleGreaterThanOperator
		|| tmp->type == IDENTIFIER))
	{
		tmp = tmp->next;
		next = next->next;
	}
	// dprintf(2, "result  %s\n", tmp->value);
	while (tmp && tmp->type == IDENTIFIER)
	{
		tmp = tmp->prev;
		next = next->prev;
	}
	// dprintf(2, "result2  %s\n", tmp->value);
	tmp = tmp->next->next;
	next->next->next = NULL;
	next = tmp2;
	// dprintf(2, "result3  %s\n", tmp->value);
	if (tmp && tmp->type == IDENTIFIER)
		redirection_node->left = parse_cmd_sep_args(ptr, tmp);
	else
		redirection_node->left = parse_redirection(&ptr);
	redirection_node->right = parse_command(&next->next, false);
	// dprintf(2, "created node in red = %s\n", redirection_node->right->args[0]);
	// dprintf(2, "3 in red = %s\n", (*tokens)->value);
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
	// dprintf(2, "red2 = %s\n", ptr->value);
	if ((*tokens)->type == OpeningParenthesis)
	{
		// dprintf(2, "inside if in red = %s\n", (*tokens)->value);
		while ((*tokens && (*tokens)->next) && (*tokens)->type != ClosingParenthesis)
			*tokens = (*tokens)->next;
	}
	// dprintf(2, "after if in red = %s\n", (*tokens)->value);
	// dprintf(2, "red = %s\n", ptr->value);
	if (((*tokens)->type == LessThanOperator
		|| (*tokens)->type == DoubleLessThanOperator
		|| (*tokens)->type == GreaterThanOperator
		|| (*tokens)->type == DoubleGreaterThanOperator)
		&& (*tokens)->next->type != OpeningParenthesis
		&& (*tokens)->type != OpeningParenthesis)
		return (help_func(tokens, ptr));
	while (*tokens && (*tokens)->next && (*tokens)->next->type != OpeningParenthesis
		&& (*tokens)->type != OpeningParenthesis)
	{
		// dprintf(2, "while in red = %s\n", (*tokens)->value);
		next = (*tokens)->next;
		if ((next->type == LessThanOperator
			|| next->type == DoubleLessThanOperator
			|| next->type == GreaterThanOperator
			|| next->type == DoubleGreaterThanOperator)
			&& (*tokens)->next->type != OpeningParenthesis
			&& (*tokens)->type != OpeningParenthesis)
			return (help_func_2(tokens, next, ptr));
		*tokens = next;
	}
	return (parse_parenthese(&ptr));
}
