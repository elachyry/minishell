/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:42:54 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/16 18:24:28 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	execve_fail(char **args)
{
	if (!ft_strcmp(args[0], "."))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": filename argument required", 2);
		ft_putstr_fd("\n", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": usage: . filename [arguments]", 2);
		ft_putstr_fd("\n", 2);
		exit(2);
	}
	if (access(args[0], F_OK) == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": is a directory", 2);
		ft_putstr_fd("\n", 2);
		exit(126);
	}
	perror_message("execve", EXIT_FAILURE);
}

static void	cmd_not_found(char **args, int status)
{
	if (!status)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": command not found", 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
	else if (status == 2)
		perror_message(args[0], 126);
}

static int	manage_builtins(char **args)
{
	int	old_stdin;
	int	old_stdout;
	int	status;

	old_stdin = dup(STDIN_FILENO);
	old_stdout = dup(STDOUT_FILENO);
	status = 0;
	redirect_files();
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
}

int	execute_command(char **args)
{
	int		status;
	pid_t	pid;

	status = 0;
	if (check_if_builtin(args[0]))
		return (manage_builtins(args));
	else
	{
		pid = fork();
		if (pid == -1)
			perror_message("fork", EXIT_FAILURE);
		else if (pid == 0)
		{
			redirect_files();
			status = get_cmd_path(args[0]);
			cmd_not_found(args, status);
			execve(g_shell_data.simple_cmd->cmd_path,
				args, g_shell_data.environment);
			execve_fail(args);
		}
		else
			wait_for_cmd(pid, &status);
		return (WEXITSTATUS(status));
	}
}
