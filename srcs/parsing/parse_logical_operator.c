/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_logical_operator.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:54:09 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/29 11:38:45 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	help_func(t_token **tokens)
{
	if (*tokens && (*tokens)->type == OpeningParenthesis)
	{
		while ((*tokens && (*tokens)->next)
			&& (*tokens)->type != ClosingParenthesis)
			*tokens = (*tokens)->next;
	}
}

//this function for parsing the pipeline
//by creating a node type LogicalOr || LogicalAnd
//I check if the parenthesis to not 
//parse logical operators iside parenthes cmd
t_ast_node	*parse_logical_operator(t_token **tokens)
{
	t_token		*next;
	t_token		*ptr;
	t_ast_node	*logical_node;

	ptr = *tokens;
	logical_node = NULL;
	help_func(tokens);
	while (*tokens && (*tokens)->next)
	{
		help_func(tokens);
		if (*tokens && (*tokens)->next)
		{
			next = (*tokens)->next;
			if (next->type == LogicalAnd || next->type == LogicalOr)
			{
				(*tokens)->next = NULL;
				logical_node = new_ast_node(next->type);
				logical_node->left = parse_pipeline(&ptr);
				logical_node->right = parse_logical_operator(&(next->next));
				return (logical_node);
			}
			*tokens = next;
		}
	}
	return (parse_pipeline(&ptr));
}
