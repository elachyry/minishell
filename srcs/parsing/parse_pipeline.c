/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:51:56 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/29 11:38:32 by melachyr         ###   ########.fr       */
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

//this function for parsing the pipeline by creating a node type Pipeline
t_ast_node	*parse_pipeline(t_token **tokens)
{
	t_token		*next;
	t_token		*ptr;
	t_ast_node	*pipe_node;

	ptr = *tokens;
	pipe_node = NULL;
	help_func(tokens);
	while (*tokens && (*tokens)->next
		&& (*tokens)->next->type != OpeningParenthesis
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
