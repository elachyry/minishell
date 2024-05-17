/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:20:20 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/16 18:25:24 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_less_than(t_ast_node *node)
{
	int		fd;
	t_files	*file;
	t_files	*last;

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

	file = new_file_node(node->right->args[0], DoubleGreaterThanOperator);
	add_lst_file(&g_shell_data.simple_cmd->files, file);
	fd = open(node->right->args[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	close(fd);
	execute_ast(node->right->right);
	execute_ast(node->left);
}
