/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:51:56 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/16 14:14:09 by melachyr         ###   ########.fr       */
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
	while (*tokens && (*tokens)->next)
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
