/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 00:18:25 by kaddouri          #+#    #+#             */
/*   Updated: 2024/06/08 23:44:37 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell_data g_shell_data;

// get the name of the token type
const char	*get_token_type_name(t_token_type type)
{
	const char	*token_type_names[11];

	token_type_names[0] = "T_IDENTIFIER";
	token_type_names[1] = "T_LESS";
	token_type_names[2] = "T_GREAT";
	token_type_names[3] = "T_DLESS";
	token_type_names[4] = "T_DGREAT";
	token_type_names[5] = "T_PIPE";
	token_type_names[6] = "T_O_PARENT";
	token_type_names[7] = "T_C_PARENT";
	token_type_names[8] = "T_AND";
	token_type_names[9] = "T_OR";
	token_type_names[10] = "T_NL";
	if (type >= 0 && type < 11)
		return (token_type_names[type]);
	return ("UNKNOWN");
}

// just a test function to see if the tokens are correctly generated
void	display_tokens(t_token *tokens)
{
	t_token	*token;

	token = tokens;
	while (token)
	{
		printf("Token: \033[0;36m %-20s \033[0m |\t \
			Type: \033[0;35m %-18s \033[0m \n",
			token->value, get_token_type_name(token->type));
		printf("--------------------------------------------------\n");
		token = token->next;
	}
}

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

int	main(int ac, char **av, char **envp)
{
	t_token		*tokens;
	t_ast_node	*ast;
	
	(void)av;
	(void)ac;
	if (ac != 1)
	{
		printf("This program does not accept arguments\n");
		exit(0);
	}
	initialize_shell(envp);
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
		free(g_shell_data.line);
		ast = parse_tokens(&tokens);
		if (!ast)
			continue ;
		g_shell_data.ast = ast;
		g_shell_data.ctl = true;
		execution();
		g_shell_data.sig_exit = 0;
		g_shell_data.ctl= false;
	}
	gc_cleanup();
	return (0);
}
