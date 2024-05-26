/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:29:34 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/26 15:18:46 by melachyr         ###   ########.fr       */
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

static void	file_not_found(t_ast_node *node, int fd)
{
	t_files	*last;

	last = lst_file_last(g_shell_data.simple_cmd->files);
	last->is_opened = true;
	ft_putstr_fd("minishell: ", 2);
	perror(node->right->args[1]);
	close(fd);
	g_shell_data.status = 1;
}

void	execute_ast(t_ast_node *node)
{
	t_files	*file;
	int		fd;

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
		if (g_shell_data.simple_cmd->is_parenthis)
		{
			if (!g_shell_data.simple_cmd->is_parenthis_red_ch)
				g_shell_data.simple_cmd->files = NULL;
			g_shell_data.simple_cmd->is_parenthis_red_ch = true;
		}
		file = new_file_node(node->right->args[1], LessThanOperator);
		add_lst_file(&g_shell_data.simple_cmd->files, file);
		g_shell_data.simple_cmd->is_first++;
		fd = open(node->right->args[1], O_RDONLY);
		if (fd == -1)
		{
			file_not_found(node, fd);
			return ;
		}
		close(fd);
		execute_ast(node->right->right);
		execute_ast(node->left);
	}
	else if (node->type == OpeningParenthesis)
		execute_parenthesis(node);
}

void	extrac_ast_parenth(t_ast_node *node)
{
	char	*line;
	t_token		*tokens;

	if (!node)
		return ;
	if (node->type == OpeningParenthesis)
	{
		line = concat_cmd(node);
		tokens = ft_tokenize(line);
		tokens = expand_tokens(tokens);
		g_shell_data.ast_parenth = parse_tokens(&tokens);
		t_ast_node *tmp = g_shell_data.ast_parenth;
		extrac_ast_parenth(g_shell_data.ast_parenth);
		g_shell_data.ast_parenth = tmp;
	}
	else if (node->type == LessThanOperator
		|| node->type == GreaterThanOperator
		|| node->type == DoubleGreaterThanOperator
		|| node->type == DoubleLessThanOperator
		|| node->type == PipeSymbol
		|| node->type == LogicalAnd
		|| node->type == LogicalOr
		|| node->type == IDENTIFIER)
	{
		extrac_ast_parenth(node->left);
		extrac_ast_parenth(node->right);
	}
}

static void	handle_here_doc(void)
{

	g_shell_data.status = 0;
	g_shell_data.simple_cmd->files = NULL;
	if (g_shell_data.simple_cmd->is_parenthis)
	{
		t_ast_node *node = g_shell_data.ast;
		extrac_ast_parenth(node);
	}
	execute_here_doc(g_shell_data.ast);
}

void	execution(void)
{
	t_ast_node	*ast;
	
	g_shell_data.simple_cmd->here_index = 0;
	handle_here_doc();
	ast = g_shell_data.ast;
	if (!g_shell_data.status)
	{
		g_shell_data.simple_cmd->is_first = 0;
		execute_ast(ast);
	}
	g_shell_data.simple_cmd->nbr_here_doc = 0;
	while (*g_shell_data.simple_cmd->here_docs_files)
	{
		unlink(*g_shell_data.simple_cmd->here_docs_files);
		g_shell_data.simple_cmd->here_docs_files++;
	}
}
