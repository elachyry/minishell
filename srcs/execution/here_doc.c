/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:28:30 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/17 10:06:07 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	here_doc(char *delimiter, int fd)
{
	char	*str;

	str = NULL;
	delimiter = ft_strjoin(delimiter, "\n");
	write(1, "> ", 2);
	while (1)
	{
		str = get_next_line(0);
		if (str)
		{
			if (ft_strcmp(delimiter, str) == 0)
			{
				free(str);
				break ;
			}
			write(1, "> ", 2);
			if (g_shell_data.simple_cmd->should_expand)
				expand_here_doc(str, fd);
			else
				write(fd, str, ft_strlen(str));
		}
		else
			break ;
	}
	close(fd);
}

static void	here_doc_child_proc(t_ast_node *node)
{
	int		fd;

	signal(SIGINT, SIG_DFL);
	fd = open(g_shell_data.simple_cmd->here_doc_path,
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		close(fd);
		perror_message("open", EXIT_FAILURE);
	}
	here_doc(node->right->args[0], fd);
	exit(EXIT_SUCCESS);
}

static void	handle_here_doc(t_ast_node *node)
{
	char	*name;
	pid_t	pid;

	if (g_shell_data.simple_cmd->here_doc_path)
		unlink(g_shell_data.simple_cmd->here_doc_path);
	name = get_here_doc_name();
	g_shell_data.simple_cmd->here_doc_path = ft_strjoin("/tmp/", name);
	free(name);
	pid = fork();
	if (pid == -1)
		perror_message("fork", EXIT_FAILURE);
	if (pid == 0)
		here_doc_child_proc(node);
	else
	{
		waitpid(pid, NULL, 0);
		execute_here_doc(node->right->right);
		execute_here_doc(node->left);
	}
}

void	execute_here_doc(t_ast_node *node)
{
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
		handle_here_doc(node);
}
