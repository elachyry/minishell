/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:20:20 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/21 09:40:01 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_less_than(t_ast_node *node)
{
	int		fd;
	t_files	*file;
	t_files	*last;

	// dprintf(2, "less than = %s\n", node->right->args[0]);
	// dprintf(2, "node right = %p\n", node->right);
	// dprintf(2, "node right args = %p\n", node->right->args);
	if (g_shell_data.simple_cmd->is_parenthis)
	{
		if (!g_shell_data.simple_cmd->is_parenthis_red_ch)
			g_shell_data.simple_cmd->files = NULL;
		g_shell_data.simple_cmd->is_parenthis_red_ch = true;
	}
	file = new_file_node(node->right->args[0], LessThanOperator);
	add_lst_file(&g_shell_data.simple_cmd->files, file);
	g_shell_data.simple_cmd->is_first++;
	fd = open(node->right->args[0], O_RDONLY);
	if (fd == -1)
	{
		last = lst_file_last(g_shell_data.simple_cmd->files);
		last->is_opened = true;
		ft_putstr_fd("minishell: ", 2);
		perror(node->right->args[0]);
		close(fd);
		g_shell_data.status = 1;
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

	// dprintf(2, "great than = %s\n", node->right->args[0]);
	if (g_shell_data.simple_cmd->is_parenthis)
	{
		if (!g_shell_data.simple_cmd->is_parenthis_red_ch)
			g_shell_data.simple_cmd->files = NULL;
		g_shell_data.simple_cmd->is_parenthis_red_ch = true;
	}
	file = new_file_node(node->right->args[0], GreaterThanOperator);
	add_lst_file(&g_shell_data.simple_cmd->files, file);
	g_shell_data.simple_cmd->is_first++;
	fd = open(node->right->args[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
	file = new_file_node(node->right->args[0], DoubleGreaterThanOperator);
	add_lst_file(&g_shell_data.simple_cmd->files, file);
	fd = open(node->right->args[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	close(fd);
	execute_ast(node->right->right);
	execute_ast(node->left);
}
