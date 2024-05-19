/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 00:57:54 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/19 14:12:20 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit(char **args)
{
	int		status;

	status = 0;
	if (args[1])
	{
		if (!ft_isnumber(args[1]))
		{
			ft_putstr_fd("exit\nminishell: exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
		status = ft_atoi(args[1]);
		if (args[2])
		{
			ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
			g_shell_data.status = 1;
			// printf("g_shell_data.status = %d\n", g_shell_data.status);
			return (1);
		}
	}
	ft_putstr_fd("exit\n", 2);
	exit(status);
	return (0);
}
