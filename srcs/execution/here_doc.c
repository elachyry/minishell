/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:28:30 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/19 12:09:55 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	here_doc(char *delimiter)
{
	char	*str;
	char	*buff;
	int		fd = 0;

	str = NULL;
	delimiter = ft_strjoin(delimiter, "\n");
	buff = ft_strdup("");
	write(1, "> ", 2);
	while (1)
	{
		str = get_next_line(0);
		if (str)
		{
			if (ft_strcmp(delimiter, str) == 0)
			{
				fd = open(g_shell_data.simple_cmd->here_doc_path,
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd == -1)
				{
					close(fd);
					perror_message("open", EXIT_FAILURE);
				}
				write(fd, buff, ft_strlen(buff));
				free(str);
				break ;
			}
			write(1, "> ", 2);
			if (g_shell_data.simple_cmd->should_expand)
				buff  = ft_strjoin(buff, expand_here_doc(str, fd));
			else
				buff = ft_strjoin(buff, str);
				// write(fd, str, ft_strlen(str));
		}
		else
		{
			fd = open(g_shell_data.simple_cmd->here_doc_path,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				close(fd);
				perror_message("open", EXIT_FAILURE);
			}
			write(fd, buff, ft_strlen(buff));
			free(str);
			break ;
		}
	}
	close(fd);
}

// static void	here_doc_child_proc(t_ast_node *node)
// {
// 	// int		fd;

// 	// fd = open(g_shell_data.simple_cmd->here_doc_path,
// 	// 		O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	// if (fd == -1)
// 	// {
// 	// 	close(fd);
// 	// 	perror_message("open", EXIT_FAILURE);
// 	// }
// 	here_doc(node->right->args[0]);
// 	// exit(EXIT_SUCCESS);
// }

static void	handle_here_doc(t_ast_node *node)
{
	// char	*name;

	// // if (g_shell_data.simple_cmd->here_doc_path)
	// // 	unlink(g_shell_data.simple_cmd->here_doc_path);
	// name = get_here_doc_name();
	// g_shell_data.simple_cmd->here_doc_path = ft_strjoin("/tmp/", name);
	// free(name);
	// here_doc_child_proc(node);
	here_doc(node->right->args[0]);

}

void	sigint_heredoc(int sig)
{
	(void) sig;
	g_shell_data.status = 1;
	g_shell_data.simple_cmd->here_doc_path = NULL;
	exit(EXIT_SUCCESS);
	// g_shell_data.sig_exit = true;

	// dprintf(2, "status in signal = %d\n", g_shell_data.status);
	// dprintf(2, "signal\n");
}

void	execute_here_doc(t_ast_node *node)
{
	pid_t	pid;

	
	if (!node)
		return ;
	if (node->type == PipeSymbol
		|| node->type == LogicalAnd
		|| node->type == LogicalOr)
	{
		execute_here_doc(node->left);
		execute_here_doc(node->right);
	}
	else if (node->type == LessThanOperator
		|| node->type == GreaterThanOperator
		|| node->type == DoubleGreaterThanOperator
		|| node->type == IDENTIFIER)
	{
		execute_here_doc(node->left);
		execute_here_doc(node->right);
	}
	else if (node->type == DoubleLessThanOperator)
	{
		char	*name;

		name = get_here_doc_name();
		g_shell_data.simple_cmd->here_doc_path = ft_strjoin("/tmp/", name);
		printf("here doc path = %s\n", g_shell_data.simple_cmd->here_doc_path);
		free(name);
		pid = fork();
		if (pid == -1)
			perror_message("fork", EXIT_FAILURE);
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			handle_here_doc(node);
			execute_here_doc(node->right->right);
			execute_here_doc(node->left);
			exit(EXIT_SUCCESS);
		}
		else
		{
			waitpid(pid, NULL, 0);
		}
	}
}
