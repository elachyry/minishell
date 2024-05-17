/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_parenthesis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:32:55 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/16 17:34:44 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_parenthesis(t_ast_node *node)
{
	t_token		*tokens;
	t_ast_node	*ast;
	char		*line;

	line = *node->args;
	line = ft_strjoin(line, " ");
	node->args++;
	while (*node->args)
	{
		line = ft_strjoin(line, *node->args);
		line = ft_strjoin(line, " ");
		node->args++;
	}
	tokens = ft_tokenize(line);
	free(line);
	ast = parse_tokens(&tokens);
	execute_ast(ast);
}
