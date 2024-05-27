/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:28:30 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/26 18:06:27 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	write_in_file(char *str, char *delimiter, \
	char **buff, char **content)
{
	if (ft_strcmp(delimiter, str) == 0)
	{
		*content = ft_strdup(*buff);
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

static void	here_doc(char **cmd, char **content)
{
	char	*str;
	char	*buff;
	char	*delimiter;

	str = NULL;
	delimiter = ft_strjoin(cmd[0], "\n");
	buff = ft_strdup("");
	write(1, "> ", 2);
	while (1)
	{
		str = get_next_line(0);
		if (str)
		{
			if (write_in_file(str, delimiter, &buff, content))
				break ;
		}
		else
		{
			*content = ft_strdup(buff);
			free(str);
			break ;
		}
	}
}

void	write_content_to_file(char *content, char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror_message("open", EXIT_FAILURE);
		return ;
	}
	write(fd, content, ft_strlen(content));
	close(fd);
}

static void	handle_here_doc(t_ast_node *node)
{
	pid_t	pid;
	char	*content;

	pid = fork();
	if (pid == -1)
		perror_message("fork", EXIT_FAILURE);
	if (pid == 0)
	{
		execute_here_doc(node->left);
		signal(SIGINT, SIG_DFL);
		here_doc(node->right->args, &content);
		write_content_to_file(content, node->right->args[1]);
		free(content);
		execute_here_doc(node->right->right);
		exit(EXIT_SUCCESS);
	}
	else
		waitpid(pid, NULL, 0);
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
	else if (node->type == OpeningParenthesis)
		execute_here_doc(g_shell_data.ast_parenth);
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
