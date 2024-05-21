/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:42:54 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/21 20:44:15 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	manage_builtins(char **args)
{
	int	old_stdin;
	int	old_stdout;
	int	status;

	old_stdin = dup(STDIN_FILENO);
	old_stdout = dup(STDOUT_FILENO);
	status = 0;
	if (redirect_files_buildin())
		return (1);
	status = execute_builtin(args);
	dup2(old_stdin, STDIN_FILENO);
	dup2(old_stdout, STDOUT_FILENO);
	return (status);
}

static void	wait_for_cmd(pid_t pid, int *status)
{
	waitpid(pid, status, 0);
	if (WIFEXITED(*status))
	{
		if (WEXITSTATUS(*status) != 0)
			g_shell_data.simple_cmd->files = NULL;
	}
	g_shell_data.simple_cmd->is_parenthis++;
	g_shell_data.simple_cmd->is_parenthis_red_ch = false;
}

static void	process_cmd(char **args)
{
	int	status;

	status = get_cmd_path(args[0]);
	cmd_not_found(args, status);
	execve(g_shell_data.simple_cmd->cmd_path,
		args, g_shell_data.environment);
	execve_fail(args);
}

int	execute_command(char **args)
{
	int		status;
	pid_t	pid;

	status = 0;
	signal(SIGQUIT, sigquit_handler);
	if (check_if_builtin(args[0]))
		return (manage_builtins(args));
	else
	{
		pid = fork();
		if (pid == -1)
			perror_message("fork", EXIT_FAILURE);
		else if (pid == 0)
		{
			if (g_shell_data.simple_cmd->is_parenthis > 1
				|| !g_shell_data.simple_cmd->is_parenthis
				|| (g_shell_data.simple_cmd->is_parenthis == 1
					&& g_shell_data.simple_cmd->is_parenthis_red_ch == 1))
				redirect_files();
			process_cmd(args);
		}
		else
			wait_for_cmd(pid, &status);
		return (WEXITSTATUS(status));
	}
}
