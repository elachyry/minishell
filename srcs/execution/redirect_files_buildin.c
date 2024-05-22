/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_files_buildin.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:06:36 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/22 15:14:39 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	less_than_operator_2(t_files *file)
{
	int	in_fd;

	in_fd = open(file->filename, O_RDONLY);
	if (in_fd == -1)
	{
		if (!file->is_opened)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(file->filename);
		}
		close(in_fd);
		return (EXIT_FAILURE);
	}
	if (dup2(in_fd, STDIN_FILENO) == -1)
	{
		g_shell_data.simple_cmd->files = NULL;
		perror("dup2");
		return (EXIT_FAILURE);
	}
	close(in_fd);
	return (0);
}

static int	greater_than_operator_2(t_files *file)
{
	int	out_fd;

	out_fd = open(file->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out_fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(file->filename);
		close(out_fd);
		return (EXIT_FAILURE);
	}
	if (dup2(out_fd, STDOUT_FILENO) == -1)
	{
		g_shell_data.simple_cmd->files = NULL;
		perror("dup2");
		return (EXIT_FAILURE);
	}
	close(out_fd);
	return (0);
}

static int	double_greater_than_operator_2(t_files *file)
{
	int	out_fd;

	out_fd = open(file->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (out_fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(file->filename);
		exit(EXIT_FAILURE);
	}
	if (dup2(out_fd, STDOUT_FILENO) == -1)
	{
		g_shell_data.simple_cmd->files = NULL;
		perror("dup2");
		return (EXIT_FAILURE);
	}
	close(out_fd);
	return (0);
}

int	redirect_files_buildin(void)
{
	t_files	*file;

	file = g_shell_data.simple_cmd->files;
	while (file)
	{
		if (file->type == LessThanOperator
			|| file->type == DoubleLessThanOperator)
		{
			if (less_than_operator_2(file))
				return (1);
		}
		else if (file->type == GreaterThanOperator)
		{
			if (g_shell_data.simple_cmd->is_parenthis > 1)
			{
				if (double_greater_than_operator_2(file))
					return (1);
			}
			else
			{
				if (greater_than_operator_2(file))
					return (1);
			}
		}
		else if (file->type == DoubleGreaterThanOperator)
		{
			if (double_greater_than_operator_2(file))
				return (1);
		}
		file = file->next;
	}
	if (g_shell_data.simple_cmd->is_parenthis)
		g_shell_data.simple_cmd->is_parenthis++;
	return (0);
}
