/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 05:30:45 by akaddour          #+#    #+#             */
/*   Updated: 2024/05/24 23:09:31 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint_handler(int sig)
{
	(void) sig;
	printf("\n");
	if (!g_shell_data.ctl)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	g_shell_data.status = 130;
	g_shell_data.sig_exit = 1;
}

void	sigint_herdoc_handler(int sig)
{
	(void) sig;
	gc_cleanup();
	exit(130);
}

void	sigquit_handler(int sig)
{
	(void) sig;
	printf("Quit (core dumped)\n");
	if (!g_shell_data.ctl)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	g_shell_data.status = 131;
	g_shell_data.sig_exit = 2;
}

void	handle_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
