/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 00:18:25 by kaddouri          #+#    #+#             */
/*   Updated: 2024/04/29 06:54:28 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	**get_path(char **envp)
{
	char	**path;
	char	*path_str;
	int		i;

	i = 0;
	path_str = NULL;
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_str = ft_strdup(envp[i] + 5);
			break ;
		}
		i++;
	}
	if (path_str == NULL)
	{
		printf("Error: PATH not found in environment variables\n");
		exit(1);
	}
	path = ft_split(path_str, ':');
	free(path_str);
	return (path);
}

int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_token		*tokens;
	t_ast_node	*ast;
	t_minishell	minishell;

	(void)av;
	(void)ac;
	if (ac != 1)
	{
		printf("This program does not accept arguments\n");
		exit(0);
	}
	line = NULL;
	minishell.env = get_path(envp);
	for (int i = 0; minishell.env[i]; i++)
		printf("%s\n", minishell.env[i]);
	while (1)
	{
		handle_signals();
		display_prompt(&line);
		syntax_error_checker(line);
		tokens = ft_tokenize(line);
		free(line);
		display_tokens(tokens);
		ast = parse_tokens(tokens);
		generate_ast_diagram(ast);
	}
	return (0);
}
