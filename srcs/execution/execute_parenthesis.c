/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_parenthesis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:32:55 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/21 20:58:02 by melachyr         ###   ########.fr       */
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

static char	*concat_cmd(t_ast_node *node)
{
	char	*line;

	line = *node->args;
	line = ft_strjoin(line, " ");
	node->args++;
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
	g_shell_data.simple_cmd->is_parenthis_red_ch = false;
	return (line);
}

void	execute_parenthesis(t_ast_node *node)
{
	t_token		*tokens;
	t_ast_node	*ast;
	pid_t		pid;
	char		*line;
	int			status;

	pid = fork();
	status = 0;
	if (pid == -1)
		perror_message("fork", EXIT_FAILURE);
	if (pid == 0)
	{
		// dprintf(2, "node %s\n", node->args[0]);
		if (!node->args[0])
			exit(EXIT_SUCCESS);
		line = concat_cmd(node);
		// dprintf(2, "line  = %s\n", line);
		tokens = ft_tokenize(line);
		tokens = expand_tokens(tokens);
		// display_tokens(tokens);
		ast = parse_tokens(&tokens);
		redirect_files_2();
		execute_ast(ast);
		generate_ast_diagram(ast);
		exit(g_shell_data.status);
	}
	else
	{
		waitpid(pid, &status, WCONTINUED);
		g_shell_data.status = WEXITSTATUS(status);
	}
}
