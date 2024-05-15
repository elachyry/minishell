/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 00:18:25 by kaddouri          #+#    #+#             */
/*   Updated: 2024/05/15 20:54:05 by melachyr         ###   ########.fr       */
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
		exit(1);
	}
	if (*line[0])
		add_history(*line);
}

void	initialize_shell(char **envp)
{
	// printf("envp = %s\n", envp[0]);
	g_shell_data.line = NULL;
	g_shell_data.environment = envp;
	g_shell_data.path = NULL;
	g_shell_data.tokens = NULL;
	g_shell_data.ast = NULL;
	g_shell_data.status = 0;
	g_shell_data.nbr_cmd = 0;
	g_shell_data.sig_exit = false;
	g_shell_data.ctl = false;
	g_shell_data.simple_cmd = malloc(sizeof(t_simple_cmd));
	g_shell_data.simple_cmd->should_expand = true;
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
			continue ;
		tokens = ft_tokenize(g_shell_data.line);
		tokens = expand_tokens(tokens);
		free(g_shell_data.line);
		display_tokens(tokens);
		ast = parse_tokens(&tokens);
		g_shell_data.ast = ast;
		generate_ast_diagram(ast);
		g_shell_data.ctl = true;
		execution();
		g_shell_data.sig_exit = false;
		g_shell_data.ctl= false;
	}
	return (0);
}
