/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:28:30 by melachyr          #+#    #+#             */
/*   Updated: 2024/06/02 18:34:24 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	help_function(t_ast_node *node);

static int	write_in_file(char *str, char *delimiter, \
	char **buff, char **content)
{
	if (ft_strcmp(delimiter, str) == 0)
	{
		*content = ft_strdup(*buff);
		// free(str);
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
			// free(str);
			break ;
		}
	}
}

void	write_content_to_file(char *content, char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return ;
	write(fd, content, ft_strlen(content));
	close(fd);
}

static void	handle_here_doc(t_ast_node *node)
{
	char	*content;

	help_function(node->left);
	if (node->right->args[0][0] == '\"' || node->right->args[0][0] == '\'')
		g_shell_data.simple_cmd->should_expand = false;
	expand_quotes(node->right->args);
	here_doc(node->right->args, &content);
	write_content_to_file(content, node->right->args[1]);
	// free(content);
	help_function(node->right->right);
}

void	help_function(t_ast_node *node)
{
	if (!node)
		return ;
	else if (node->type == OpeningParenthesis)
		help_function(g_shell_data.ast_parenth);
	else if (node->type == PipeSymbol
		|| node->type == LogicalAnd
		|| node->type == LogicalOr
		|| node->type == LessThanOperator
		|| node->type == GreaterThanOperator
		|| node->type == DoubleGreaterThanOperator
		|| node->type == IDENTIFIER)
	{
		help_function(node->left);
		help_function(node->right);
	}
	else if (node->type == DoubleLessThanOperator)
		handle_here_doc(node);
}

void	execute_here_doc(t_ast_node *node)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror_message("fork", EXIT_FAILURE);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (!node)
			return ;
		help_function(node);
		exit(EXIT_SUCCESS);
	}
	else
		waitpid(pid, NULL, 0);
}
