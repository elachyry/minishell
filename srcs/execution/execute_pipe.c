/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:20:34 by melachyr          #+#    #+#             */
/*   Updated: 2024/06/07 00:58:42 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	execute_left_child(t_ast_node *node, int pipefd[2])
{
	close(pipefd[0]);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		perror_message("dup2", EXIT_FAILURE);
	close(pipefd[1]);
	execute_ast(node->left);
	gc_cleanup();
	exit(g_shell_data.status);
}

static void	execute_right_child(t_ast_node *node, int pipefd[2])
{
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		perror_message("dup2", EXIT_FAILURE);
	close(pipefd[0]);
	execute_ast(node->right);
	gc_cleanup();
	exit(g_shell_data.status);
}

void	execute_pipe(t_ast_node *node)
{
	int		pipefd[2];
	int		right_status;
	pid_t	left_pid;
	pid_t	right_pid;

	if (pipe(pipefd) == -1)
		perror_message("pipe", EXIT_FAILURE);
	left_pid = fork();
	if (left_pid == -1)
		perror_message("fork", EXIT_FAILURE);
	else if (left_pid == 0)
		execute_left_child(node, pipefd);
	right_pid = fork();
	if (right_pid == -1)
		perror_message("fork", EXIT_FAILURE);
	else if (right_pid == 0)
		execute_right_child(node, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(right_pid, &right_status, WCONTINUED);
	waitpid(left_pid, NULL, WCONTINUED);
	if (WIFEXITED(right_status))
		g_shell_data.status = WEXITSTATUS(right_status);
	else
		g_shell_data.status = 1;
}
