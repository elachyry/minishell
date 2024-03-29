/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaddouri <kaddouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 00:18:25 by kaddouri          #+#    #+#             */
/*   Updated: 2024/03/29 23:00:40 by kaddouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void display_prompt(char **line)
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

int main(int ac, char **av, char **envp) {
    (void)av;
    (void)ac;
    (void)envp;

    char *line;
    if (ac != 1)
	{
		printf("This program does not accept arguments\n");
		exit(0);
	}
    line = NULL;
    while (1) {
        display_prompt(&line);
        printf("%s\n", line);
        free(line);
    }
}
