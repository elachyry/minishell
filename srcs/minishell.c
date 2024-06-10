/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 00:18:25 by kaddouri          #+#    #+#             */
/*   Updated: 2024/06/10 06:42:35 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell_data	g_shell_data;

void	display_prompt(char **line)
{
	*line = readline("Minishell:~$ ");
	if (!*line)
	{
		printf("exit\n");
		gc_cleanup();
		exit(0);
	}
	if (*line[0])
		add_history(*line);
}

void	initialize_shell(char **envp)
{
	g_shell_data.line = NULL;
	g_shell_data.trash = NULL;
	g_shell_data.environment = envp;
	g_shell_data.path = NULL;
	g_shell_data.tokens = NULL;
	g_shell_data.ast_parenth = NULL;
	g_shell_data.ast = NULL;
	g_shell_data.status = 0;
	g_shell_data.sig_exit = 0;
	g_shell_data.ctl = false;
	g_shell_data.simple_cmd = gc_malloc(sizeof(t_simple_cmd));
	g_shell_data.simple_cmd->should_expand = true;
	g_shell_data.simple_cmd->here_docs_files = NULL;
	g_shell_data.simple_cmd->here_name = NULL;
	g_shell_data.simple_cmd->is_parenthis = false;
	g_shell_data.simple_cmd->nbr_here_doc = 0;
	g_shell_data.simple_cmd->here_index = 0;
	if (!g_shell_data.simple_cmd)
		return ;
	g_shell_data.environment_list = initialize_environment_list(envp);
	extract_path();
}

static void	help_function(void)
{
	t_token		*tokens;
	t_ast_node	*ast;

	while (1)
	{
		handle_signals();
		display_prompt(&g_shell_data.line);
		if (!syntax_error_checker(g_shell_data.line))
		{
			g_shell_data.status = 2;
			continue ;
		}
		tokens = ft_tokenize(g_shell_data.line);
		g_shell_data.simple_cmd->should_expand = true;
		tokens = expand_tokens(tokens);
		ast = parse_tokens(&tokens);
		if (!ast)
			continue ;
		g_shell_data.ast = ast;
		g_shell_data.ctl = true;
		execution();
		g_shell_data.sig_exit = 0;
		g_shell_data.ctl = false;
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	(void)ac;
	if (ac != 1)
	{
		printf("This program does not accept arguments\n");
		exit(0);
	}
	initialize_shell(envp);
	help_function();
	gc_cleanup();
	return (0);
}
