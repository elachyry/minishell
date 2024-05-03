/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 00:57:54 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/03 00:53:42 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

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
			exit(1);
		}
	}
	ft_putstr_fd("exit\n", 2);
	exit(status);
}
