/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 00:57:54 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/12 20:17:27 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(char **args)
{
	int		i;
	int		status;

	i = 0;
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
			return ;
		}
	}
	ft_putstr_fd("exit\n", 2);
	exit(status);
}
