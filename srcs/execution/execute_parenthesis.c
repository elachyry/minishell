/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_parenthesis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:32:55 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/20 11:10:28 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	less_than_operator(t_files *file)
{
	int	in_fd;

	in_fd = open(file->filename, O_RDONLY);
	if (in_fd == -1)
	{
		if (!file->is_opened)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(file->filename);
		}
		close(in_fd);
		exit(EXIT_FAILURE);
	}
	if (dup2(in_fd, STDIN_FILENO) == -1)
	{
		g_shell_data.simple_cmd->files = NULL;
		perror_message("dup2", EXIT_FAILURE);
	}
	close(in_fd);
}

static void	greater_than_operator(t_files *file)
{
	int	out_fd;

	out_fd = open(file->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out_fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(file->filename);
		close(out_fd);
		exit(EXIT_FAILURE);
	}
	if (dup2(out_fd, STDOUT_FILENO) == -1)
	{
		g_shell_data.simple_cmd->files = NULL;
		perror_message("dup2", EXIT_FAILURE);
	}
	close(out_fd);
}

static void	double_greater_than_operator(t_files *file)
{
	int	out_fd;

	out_fd = open(file->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (out_fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(file->filename);
		exit(EXIT_FAILURE);
	}
	if (dup2(out_fd, STDOUT_FILENO) == -1)
	{
		g_shell_data.simple_cmd->files = NULL;
		perror_message("dup2", EXIT_FAILURE);
	}
	close(out_fd);
}


void	redirect_files_2(void)
{
	t_files	*file;

	// dprintf(2, "redirect_files %s\n", g_shell_data.simple_cmd->files->filename);
	file = g_shell_data.simple_cmd->files;
	while (file)
	{
		// dprintf(2, "jjjjjj\n");
		if (file->type == LessThanOperator
			|| file->type == DoubleLessThanOperator)
			less_than_operator(file);
		else if (file->type == GreaterThanOperator)
		{
			// dprintf(2, "is parenthies = %d\n", g_shell_data.simple_cmd->is_parenthis);
				greater_than_operator(file);
		}
		else if (file->type == DoubleGreaterThanOperator)
			double_greater_than_operator(file);
		file = file->next;
	}
	// dprintf(2, "end redirect_files %s\n", g_shell_data.simple_cmd->files->filename);
}

void	execute_parenthesis(t_ast_node *node)
{
	t_token		*tokens;
	t_ast_node	*ast;
	char		*line;
	pid_t		pid;

	pid = fork();
	if (pid == -1)
		perror_message("fork", EXIT_FAILURE);
	if (pid == 0)
	{
		line = *node->args;
		line = ft_strjoin(line, " ");
		node->args++;
		// dprintf(2, "parenthies\n");
		while (*node->args)
		{
			if (*node->args[0] == '\0')
			{
				line = ft_strjoin(line, "\"\"");
				line = ft_strjoin(line, " ");
			}
			else
			{
				line = ft_strjoin(line, *node->args);
				line = ft_strjoin(line, " ");
			}
			node->args++;
		}
		g_shell_data.simple_cmd->is_parenthis = true;
		tokens = ft_tokenize(line);
		tokens = expand_tokens(tokens);
		free(line);
		ast = parse_tokens(&tokens);
		redirect_files_2();
		execute_ast(ast);
		exit(g_shell_data.status);
	}
	else
	{
		int	status = 0;
		waitpid(pid, &status, WCONTINUED);
		g_shell_data.status = WEXITSTATUS(status);
	}
}
