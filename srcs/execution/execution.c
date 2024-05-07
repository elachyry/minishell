/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:29:34 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/07 10:03:54 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_cmd_path(void)
{
	char			*cmd;
	char			*path;
	
	cmd = ft_strrchr(g_shell_data.ast->args[0], '/');
	// printf("cmd %s\n", g_shell_data.ast->args[0]);
	if (cmd)
	{
		if (access(g_shell_data.ast->args[0], X_OK) != -1)
		{
			g_shell_data.simple_cmd->cmd_path = g_shell_data.ast->args[0];
			// printf("simple_cmd path %s\n", g_shell_data.simple_cmd->cmd_path);
			return (1);
		}
	}
	else
	{
		cmd = g_shell_data.ast->args[0];
		// printf("cmd %s\n", cmd);
		while (*g_shell_data.path)
		{
			// printf("path %s\n", *g_shell_data.path);
			path = ft_strjoin(*g_shell_data.path, "/");
			path = ft_strjoin(path, cmd);
			// printf("path %s\n", path);
			if (access(path, X_OK) != -1)
			{
				// printf("before \n");
				g_shell_data.simple_cmd->cmd_path = path;
				// printf("simple_cmd path %s\n", g_shell_data.simple_cmd->cmd_path);
				return (1);
			}
			free(path);
			g_shell_data.path++;
		}
	}
	
	return (0);
}

void	execute_single_cmd(void)
{
	int	status;

	int	pid = fork();
	if (pid == 0)
	{
		if (!get_cmd_path())
		{
			ft_putstr_fd("command not found: ", 2);
			ft_putstr_fd(g_shell_data.ast->args[0], 2);
			ft_putstr_fd("\n", 2);
			exit(127);
		}
		execve(g_shell_data.simple_cmd->cmd_path, g_shell_data.ast->args, NULL);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_shell_data.status = WEXITSTATUS(status);
	}
}


void	execution(void)
{
	// printf("nbr cmd = %d\n", g_shell_data.nbr_cmd);
	if (g_shell_data.nbr_cmd == 1)
	{
		if (check_if_builtin(g_shell_data.ast->args[0]))
			execute_builtin(g_shell_data.ast->args);
		else
			execute_single_cmd();
	}
}
