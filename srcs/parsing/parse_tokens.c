/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:37:53 by melachyr          #+#    #+#             */
/*   Updated: 2024/06/08 23:46:15 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	help_function(void)
{
	if (g_shell_data.simple_cmd->nbr_here_doc >= 17)
	{
		ft_putstr_fd("minishell: maximum here-document count exceeded\n", 2);
		gc_cleanup();
		exit(2);
	}
}

t_ast_node	*parse_tokens(t_token **tokens)
{
	t_token	*ptr;

	if (!tokens && !*tokens)
		return (NULL);
	ptr = *tokens;
	g_shell_data.simple_cmd->here_docs_files = NULL;
	g_shell_data.simple_cmd->nbr_here_doc = 0;
	g_shell_data.parenth_count = 0;
	while (ptr)
	{
		if (ptr->type == DoubleLessThanOperator)
			g_shell_data.simple_cmd->nbr_here_doc++;
		ptr = ptr->next;
	}
	help_function();
	g_shell_data.simple_cmd->here_index = 0;
	g_shell_data.simple_cmd->here_docs_files
		= gc_malloc(sizeof(char *)
			* (g_shell_data.simple_cmd->nbr_here_doc + 1));
	if (!g_shell_data.simple_cmd->here_docs_files)
		return (NULL);
	g_shell_data.simple_cmd->here_docs_files
	[g_shell_data.simple_cmd->nbr_here_doc] = NULL;
	return (parse_logical_operator(tokens));
}
