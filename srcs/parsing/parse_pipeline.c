/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:51:56 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/18 20:34:19 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//this function for parsing the pipeline by creating a node type Pipeline
t_ast_node	*parse_pipeline(t_token **tokens)
{
	t_token		*next;
	t_token		*ptr;
	t_ast_node	*pipe_node;

	ptr = *tokens;
	pipe_node = NULL;
	// dprintf(2, "pipe = %s\n", ptr->value);
	if (*tokens  && (*tokens)->type == OpeningParenthesis)
	{
		// dprintf(2, "inside if in pipe = %s\n", (*tokens)->value);
		while ((*tokens && (*tokens)->next) && (*tokens)->type != ClosingParenthesis)
			*tokens = (*tokens)->next;
	}
	// dprintf(2, "afetr if in pipe = %s\n", (*tokens)->value);
	while (*tokens && (*tokens)->next && (*tokens)->next->type != OpeningParenthesis
		&& (*tokens)->type != OpeningParenthesis)
	{
		next = (*tokens)->next;
		if (next->type == PipeSymbol)
		{
			(*tokens)->next = NULL;
			pipe_node = new_ast_node(next->type);
			pipe_node->left = parse_redirection(&ptr);
			pipe_node->right = parse_pipeline(&(next->next));
			return (pipe_node);
		}
		*tokens = next;
	}
	return (parse_redirection(&ptr));
}
