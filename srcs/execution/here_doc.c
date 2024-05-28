/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:28:30 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/28 18:59:06 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	write_in_file(char *str, char *delimiter, char **buff, int *fd)
{
	if (ft_strcmp(delimiter, str) == 0)
	{
		*fd = open(g_shell_data.simple_cmd->here_doc_path,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (*fd == -1)
		{
			close(*fd);
			perror_message("open", EXIT_FAILURE);
		}
		write(*fd, *buff, ft_strlen(*buff));
		free(str);
		return (1);
	}
	write(1, "> ", 2);
	if (g_shell_data.simple_cmd->should_expand)
		*buff = ft_strjoin(*buff, expand_here_doc(str));
	else
		*buff = ft_strjoin(*buff, str);
	return (0);
}

static void	closing_here_doc(char *str, char **buff, int *fd)
{
	*fd = open(g_shell_data.simple_cmd->here_doc_path,
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd == -1)
	{
		close(*fd);
		perror_message("open", EXIT_FAILURE);
	}
	write(*fd, *buff, ft_strlen(*buff));
	free(str);
}

static void	here_doc(char *delimiter)
{
	char	*str;
	char	*buff;
	int		fd;

	str = NULL;
	delimiter = ft_strjoin(delimiter, "\n");
	buff = ft_strdup("");
	write(1, "> ", 2);
	while (1)
	{
		str = get_next_line(0);
		if (str)
		{
			if (write_in_file(str, delimiter, &buff, &fd))
				break ;
		}
		else
		{
			closing_here_doc(str, &buff, &fd);
			break ;
		}
	}
	close(fd);
}

static void	handle_here_doc(t_ast_node *node)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror_message("fork", EXIT_FAILURE);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (node->right->args[0][0] == '\"' || node->right->args[0][0] == '\'')
			g_shell_data.simple_cmd->should_expand = false;
		expand_quotes(node->right->args);
		here_doc(node->right->args[0]);
		execute_here_doc(node->right->right);
		execute_here_doc(node->left);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, NULL, 0);
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
