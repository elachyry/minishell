/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:20:20 by melachyr          #+#    #+#             */
/*   Updated: 2024/06/13 15:12:21 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	file_not_found(char *filename)
{
	t_files	*last;

	last = lst_file_last(g_shell_data.simple_cmd->files);
	last->is_opened = true;
	ft_putstr_fd("minishell: ", 2);
	perror(filename);
	g_shell_data.status = 1;
}

void	execute_less_than(t_ast_node *node)
{
	int		fd;
	t_files	*file;

	if (g_shell_data.simple_cmd->is_parenthis)
	{
		if (!g_shell_data.simple_cmd->is_parenthis_red_ch)
			g_shell_data.simple_cmd->files = NULL;
		g_shell_data.simple_cmd->is_parenthis_red_ch = true;
	}
	expand_quotes(node->right->args);
	file = new_file_node(node->right->args[0], LessThanOperator);
	add_lst_file(&g_shell_data.simple_cmd->files, file);
	fd = open(node->right->args[0], O_RDONLY);
	if (fd == -1)
	{
		file_not_found(node->right->args[0]);
		return ;
	}
	close(fd);
	execute_ast(node->right->right);
	execute_ast(node->left);
}

void	execute_greater_than(t_ast_node *node)
{
	int		fd;
	t_files	*file;

	if (g_shell_data.simple_cmd->is_parenthis)
	{
		if (!g_shell_data.simple_cmd->is_parenthis_red_ch)
			g_shell_data.simple_cmd->files = NULL;
		g_shell_data.simple_cmd->is_parenthis_red_ch = true;
	}
	expand_quotes(node->right->args);
	file = new_file_node(node->right->args[0], GreaterThanOperator);
	add_lst_file(&g_shell_data.simple_cmd->files, file);
	fd = open(node->right->args[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		file_not_found(node->right->args[0]);
		return ;
	}
	close(fd);
	execute_ast(node->right->right);
	execute_ast(node->left);
}

void	execute_double_less_than(t_ast_node *node)
{
	t_files	*file;
	int		fd;

	if (g_shell_data.simple_cmd->is_parenthis)
	{
		if (!g_shell_data.simple_cmd->is_parenthis_red_ch)
			g_shell_data.simple_cmd->files = NULL;
		g_shell_data.simple_cmd->is_parenthis_red_ch = true;
	}
	file = new_file_node(node->right->args[1], LessThanOperator);
	add_lst_file(&g_shell_data.simple_cmd->files, file);
	fd = open(node->right->args[1], O_RDONLY);
	if (fd == -1)
		return ;
	close(fd);
	execute_ast(node->right->right);
	execute_ast(node->left);
}

void	execute_double_greater_than(t_ast_node *node)
{
	int		fd;
	t_files	*file;

	if (g_shell_data.simple_cmd->is_parenthis)
	{
		if (!g_shell_data.simple_cmd->is_parenthis_red_ch)
			g_shell_data.simple_cmd->files = NULL;
		g_shell_data.simple_cmd->is_parenthis_red_ch = true;
	}
	expand_quotes(node->right->args);
	file = new_file_node(node->right->args[0], DoubleGreaterThanOperator);
	add_lst_file(&g_shell_data.simple_cmd->files, file);
	fd = open(node->right->args[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		file_not_found(node->right->args[0]);
		return ;
	}
	close(fd);
	execute_ast(node->right->right);
	execute_ast(node->left);
}
