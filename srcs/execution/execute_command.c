/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:42:54 by melachyr          #+#    #+#             */
/*   Updated: 2024/06/10 23:16:16 by akaddour         ###   ########.fr       */
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
	{
		dup2(old_stdin, STDIN_FILENO);
		dup2(old_stdout, STDOUT_FILENO);
		return (1);
	}
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
	if (status == 4)
		return ;
	cmd_not_found(args, status);
	execve(g_shell_data.simple_cmd->cmd_path,
		args, g_shell_data.environment);
	execve_fail(args);
}

static int	tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

static int	help_function(char	**new_args)
{
	int		status;
	pid_t	pid;

	status = 0;
	if (check_if_builtin(new_args[0]))
		return (manage_builtins(new_args));
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
			process_cmd(new_args);
		}
		else
			wait_for_cmd(pid, &status);
		return (WEXITSTATUS(status));
	}
}

int	execute_command(char **args)
{
	char	**new_args;

	g_shell_data.simple_cmd->is_var = false;
	expand_env_variable(args);
	if (tablen(args) == 1)
		args = ft_split_2(args[0]);
	expand_quotes(args);
	new_args = args;
	if (g_shell_data.simple_cmd->is_var)
		new_args = remove_empty_args(args);
	if (new_args[0] == NULL)
		return (0);
	signal(SIGQUIT, sigquit_handler);
	return (help_function(new_args));
}
