/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:29:34 by melachyr          #+#    #+#             */
/*   Updated: 2024/06/12 22:00:44 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_command(t_ast_node *node)
{
	int	status;

	status = execute_command(node->args);
	if (g_shell_data.sig_exit == 1)
		g_shell_data.status = 130;
	else if (g_shell_data.sig_exit == 2)
		g_shell_data.status = 131;
	else
		g_shell_data.status = status;
}

void	execute_ast(t_ast_node *node)
{
	if (node == NULL)
		return ;
	if (node->type == IDENTIFIER)
		handle_command(node);
	else if (node->type == PipeSymbol)
		execute_pipe(node);
	else if (node->type == LogicalAnd)
		execute_logical_and(node);
	else if (node->type == LogicalOr)
		execute_logical_or(node);
	else if (node->type == LessThanOperator)
		execute_less_than(node);
	else if (node->type == GreaterThanOperator)
		execute_greater_than(node);
	else if (node->type == DoubleGreaterThanOperator)
		execute_double_greater_than(node);
	else if (node->type == DoubleLessThanOperator)
		execute_double_less_than(node);
	else if (node->type == OpeningParenthesis)
		execute_parenthesis(node);
}

static void	handle_here_doc(void)
{
	g_shell_data.simple_cmd->files = NULL;
	dprintf(2, "handle_here_doc\n");
	g_shell_data.simple_cmd->parenth_index = 0;
	g_shell_data.ast_parenth
		= gc_malloc(sizeof(t_ast_node) * g_shell_data.parenth_count);
	if (!g_shell_data.ast_parenth)
		return ;
	ft_memset(g_shell_data.ast_parenth, 0, \
	sizeof(t_ast_node) * g_shell_data.parenth_count);
	extrac_ast_parenth(g_shell_data.ast);
	g_shell_data.simple_cmd->parenth_index = 0;
	execute_here_doc(g_shell_data.ast);
}

void	execution(void)
{
	t_ast_node	*ast;

	g_shell_data.simple_cmd->here_index = 0;
	handle_here_doc();
	ast = g_shell_data.ast;
	if ((!g_shell_data.status
			|| (g_shell_data.status && !g_shell_data.simple_cmd->nbr_here_doc)))
		execute_ast(ast);
	g_shell_data.simple_cmd->nbr_here_doc = 0;
	if (g_shell_data.simple_cmd->here_docs_files)
	{
		while (*g_shell_data.simple_cmd->here_docs_files)
		{
			unlink(*g_shell_data.simple_cmd->here_docs_files);
			g_shell_data.simple_cmd->here_docs_files++;
		}
	}
}
