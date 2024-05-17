/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:29:34 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/17 09:56:52 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_ast(t_ast_node *node)
{
	if (node == NULL)
		return ;
	if (node->type == IDENTIFIER)
		g_shell_data.status = execute_command(node->args);
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
	{
		execute_ast(node->right->right);
		execute_ast(node->left);
	}
	else if (node->type == OpeningParenthesis)
		execute_parenthesis(node);
}

void	execution(void)
{
	t_ast_node	*ast;
	t_files		*file;

	if (g_shell_data.simple_cmd->nbr_here_doc >= 17)
	{
		ft_putstr_fd("minishell: maximum here-document count exceeded\n", 2);
		exit(2);
	}
	ast = g_shell_data.ast;
	g_shell_data.simple_cmd->here_doc_path = NULL;
	execute_here_doc(g_shell_data.ast);
	g_shell_data.simple_cmd->files = NULL;
	if (g_shell_data.simple_cmd->here_doc_path)
	{
		file = new_file_node(g_shell_data.simple_cmd->here_doc_path,
				LessThanOperator);
		add_lst_file(&g_shell_data.simple_cmd->files, file);
	}
	g_shell_data.simple_cmd->is_first = 0;
	execute_ast(ast);
	if (g_shell_data.simple_cmd->here_doc_path)
		unlink(g_shell_data.simple_cmd->here_doc_path);
}
