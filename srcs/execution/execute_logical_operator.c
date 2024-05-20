/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_logical_operator.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:16:44 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/20 16:07:35 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_logical_and(t_ast_node *node)
{
	int	left_status;

	execute_ast(node->left);
	g_shell_data.simple_cmd->files = NULL;
	left_status = g_shell_data.status;
	if (left_status == 0 && !g_shell_data.sig_exit)
		execute_ast(node->right);
	else if (node->right
		&& (node->right->type == LogicalAnd || node->right->type == LogicalOr))
	{
		if (node->right->type == LogicalAnd)
		{
			if (left_status == 0)
				execute_ast(node->right->left);
		}
		if (node->right->type == LogicalOr)
		{
			if (left_status != 0)
				execute_ast(node->right->right);
		}
	}
}

void	execute_logical_or(t_ast_node *node)
{
	int	left_status;

	execute_ast(node->left);
	// printf("test\n");
	g_shell_data.simple_cmd->files = NULL;
	// printf("test2\n");
	left_status = g_shell_data.status;
	if (left_status != 0 || g_shell_data.sig_exit == 1)
	{
		execute_ast(node->right);
	}
	else if (node->right
		&& (node->right->type == LogicalAnd || node->right->type == LogicalOr))
	{
		if (node->right->type == LogicalAnd)
		{
			if (left_status == 0)
				execute_ast(node->right->right);
		}
		if (node->right->type == LogicalOr)
		{
			if (left_status != 0)
				execute_ast(node->right->left);
		}
	}
}
