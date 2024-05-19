/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_parenthesis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:32:55 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/19 11:44:02 by melachyr         ###   ########.fr       */
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
	// dprintf(2, "parenthies\n");
	while (*node->args)
	{
		if (*node->args[0] == '\0')
		{
			line = ft_strjoin(line, "\"\"");
			line = ft_strjoin(line, " ");
		}
		else
		{
			line = ft_strjoin(line, *node->args);
			line = ft_strjoin(line, " ");
		}
		node->args++;
	}
	// g_shell_data.simple_cmd->is_parenthis = true;
	tokens = ft_tokenize(line);
	tokens = expand_tokens(tokens);
	free(line);
	ast = parse_tokens(&tokens);
	execute_ast(ast);
}
