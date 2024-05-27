/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:37:53 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/26 18:00:38 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast_node	*parse_tokens(t_token **tokens)
{
	t_token	*ptr;

	if (!tokens && !*tokens)
		return (NULL);
	ptr = *tokens;
	g_shell_data.simple_cmd->here_docs_files = NULL;
	while (ptr)
	{
		if (ptr->type == DoubleLessThanOperator)
			g_shell_data.simple_cmd->nbr_here_doc++;
		ptr = ptr->next;
	}
	if (g_shell_data.simple_cmd->nbr_here_doc >= 17)
	{
		ft_putstr_fd("minishell: maximum here-document count exceeded\n", 2);
		exit(2);
	}
	g_shell_data.simple_cmd->here_index = 0;
	g_shell_data.simple_cmd->here_docs_files
		= malloc(sizeof(char *) * (g_shell_data.simple_cmd->nbr_here_doc + 1));
	if (!g_shell_data.simple_cmd->here_docs_files)
		return (NULL);
	g_shell_data.simple_cmd->here_docs_files
	[g_shell_data.simple_cmd->nbr_here_doc] = NULL;
	return (parse_logical_operator(tokens));
}
