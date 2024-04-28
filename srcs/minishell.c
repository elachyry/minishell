/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 00:18:25 by kaddouri          #+#    #+#             */
/*   Updated: 2024/04/28 04:59:30 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_token	*token;

	(void)av;
	(void)envp;
	(void)ac;
	if (ac != 1)
	{
		printf("This program does not accept arguments\n");
		exit(0);
	}
	line = NULL;
	while (1)
	{
		display_prompt(&line);
		syntax_error_checker(line);
		token = ft_tokenize(line);
		free(line);
		display_tokens(token);
	}
	return (0);
}
