/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 05:30:45 by akaddour          #+#    #+#             */
/*   Updated: 2024/05/19 17:21:53 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint_handler(int sig)
{
	(void) sig;
	printf("\n");
	if(!g_shell_data.ctl)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	g_shell_data.status = 1;
	g_shell_data.sig_exit = 1;
	
	// dprintf(2, "pid = %d | ppid = %d \n", getpid(), getppid());
	// dprintf(2, "status in signal = %d\n", g_shell_data.status);
	// dprintf(2, "signal\n");
}

void	handle_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
