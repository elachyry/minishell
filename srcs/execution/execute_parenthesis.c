/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_parenthesis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:32:55 by melachyr          #+#    #+#             */
/*   Updated: 2024/06/07 00:58:36 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redirect_files_2(void)
{
	t_files	*file;

	file = g_shell_data.simple_cmd->files;
	while (file)
	{
		if (file->type == LessThanOperator
			|| file->type == DoubleLessThanOperator)
			less_than_operator(file);
		else if (file->type == GreaterThanOperator)
			greater_than_operator(file);
		else if (file->type == DoubleGreaterThanOperator)
			double_greater_than_operator(file);
		file = file->next;
	}
}

char	*concat_cmd(t_ast_node *node)
{
	char	*line;
	int		i;

	if (!node || !node->args[0])
		return (NULL);
	i = 0;
	line = node->args[i++];
	line = ft_strjoin(line, " ");
	while (node->args[i])
	{
		if (node->args[i][0] == '\0')
		{
			line = ft_strjoin(line, "\"\"");
			line = ft_strjoin(line, " ");
		}
		else
		{
			line = ft_strjoin(line, node->args[i]);
			line = ft_strjoin(line, " ");
		}
		i++;
	}
	g_shell_data.simple_cmd->is_parenthis = true;
	g_shell_data.simple_cmd->is_parenthis_red_ch = false;
	return (line);
}

void	execute_parenthesis(t_ast_node *node)
{
	pid_t		pid;
	int			status;

	pid = fork();
	status = 0;
	if (pid == -1)
		perror_message("fork", EXIT_FAILURE);
	if (pid == 0)
	{
		if (!node->args[0])
			exit(EXIT_SUCCESS);
		g_shell_data.simple_cmd->is_parenthis = true;
		g_shell_data.simple_cmd->is_parenthis_red_ch = false;
		redirect_files_2();
		execute_ast(g_shell_data.ast_parenth);
		gc_cleanup();
		exit(g_shell_data.status);
	}
	else
	{
		waitpid(pid, &status, 0);
		g_shell_data.status = WEXITSTATUS(status);
	}
}
