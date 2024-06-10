/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 00:57:54 by melachyr          #+#    #+#             */
/*   Updated: 2024/06/07 19:41:00 by akaddour         ###   ########.fr       */
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
			ft_putstr_fd("exit\n", 1);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			(gc_cleanup(), exit(2));
		}
		status = ft_atoi(args[1]);
		if (args[2])
		{
			ft_putstr_fd("exit\n", 1);
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			g_shell_data.status = 1;
			return (1);
		}
	}
	if (!g_shell_data.simple_cmd->is_parenthis)
		ft_putstr_fd("exit\n", 1);
	return (gc_cleanup(), exit(g_shell_data.status), 0);
}
