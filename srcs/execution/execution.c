/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:29:34 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/28 14:32:43 by akaddour         ###   ########.fr       */
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
	{
		execute_ast(node->right->right);
		execute_ast(node->left);
	}
	else if (node->type == OpeningParenthesis)
		execute_parenthesis(node);
}

static void	handle_here_doc(void)
{
	char	*name;

	if (g_shell_data.simple_cmd->nbr_here_doc >= 17)
	{
		ft_putstr_fd("minishell: maximum here-document count exceeded\n", 2);
		exit(2);
	}
	g_shell_data.simple_cmd->here_doc_path = NULL;
	if (g_shell_data.simple_cmd->nbr_here_doc > 0)
	{
		name = get_here_doc_name();
		g_shell_data.simple_cmd->here_doc_path = ft_strjoin("/tmp/", name);
		free(name);
	}
	g_shell_data.simple_cmd->files = NULL;
	execute_here_doc(g_shell_data.ast);
}

void	execution(void)
{
	t_ast_node	*ast;
	t_files		*file;

	handle_here_doc();
	ast = g_shell_data.ast;
	if (g_shell_data.simple_cmd->here_doc_path)
	{
		file = new_file_node(g_shell_data.simple_cmd->here_doc_path,
				LessThanOperator);
		add_lst_file(&g_shell_data.simple_cmd->files, file);
	}
	g_shell_data.simple_cmd->is_first = 0;
		execute_ast(ast);
	g_shell_data.simple_cmd->nbr_here_doc = 0;
	if (g_shell_data.simple_cmd->here_doc_path)
		unlink(g_shell_data.simple_cmd->here_doc_path);
}
