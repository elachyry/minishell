/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:58:24 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/27 10:27:56 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_ast_node	*help_function(t_token **tokens, t_token *ptr)
{
	t_bool		is_parenth;

	is_parenth = false;
	if ((*tokens)->type == OpeningParenthesis)
	{
		is_parenth = true;
		while ((*tokens && (*tokens)->next)
			&& (*tokens)->type != ClosingParenthesis)
			*tokens = (*tokens)->next;
		*tokens = (*tokens)->next;
	}
	if (*tokens && ((*tokens)->type == LessThanOperator
			|| (*tokens)->type == DoubleLessThanOperator
			|| (*tokens)->type == GreaterThanOperator
			|| (*tokens)->type == DoubleGreaterThanOperator)
		&& (*tokens)->next->type != OpeningParenthesis
		&& (*tokens)->type != OpeningParenthesis)
		return (cmd_before_red(tokens, ptr, is_parenth));
	return (NULL);
}

//this function for parsing the redirections
//by creating a node type of the redirecion
t_ast_node	*parse_redirection(t_token **tokens)
{
	t_token		*ptr;
	t_token		*next;
	t_ast_node	*node;

	if (!tokens || !*tokens)
		return (NULL);
	ptr = *tokens;
	node = help_function(tokens, ptr);
	if (node)
		return (node);
	while (*tokens && (*tokens)->next
		&& (*tokens)->next->type != OpeningParenthesis
		&& (*tokens)->type != OpeningParenthesis)
	{
		next = (*tokens)->next;
		if ((next->type == LessThanOperator
				|| next->type == DoubleLessThanOperator
				|| next->type == GreaterThanOperator
				|| next->type == DoubleGreaterThanOperator)
			&& (*tokens)->next->type != OpeningParenthesis
			&& (*tokens)->type != OpeningParenthesis)
			return (cmd_after_red(tokens, next, ptr));
		*tokens = next;
	}
	return (parse_parenthese(&ptr));
}
