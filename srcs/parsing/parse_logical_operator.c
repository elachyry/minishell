/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_logical_operator.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:54:09 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/16 14:13:51 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	while (*tokens && (*tokens)->next
		&& (*tokens)->next->type != OpeningParenthesis
		&& (*tokens)->type != OpeningParenthesis)
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
	return (parse_pipeline(&ptr));
}
