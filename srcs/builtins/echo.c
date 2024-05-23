/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 01:36:59 by akaddour          #+#    #+#             */
/*   Updated: 2024/05/22 22:11:55 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_check_option(char *s)
{
	int	i;

	i = 1;
	if (s[0] != '-')
		return (0);
	if (s[1] == '\0')
		return (0);
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **args)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (args[i] != NULL && ft_check_option(args[i]) == 1)
	{
		flag = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1] && args[i][0] != '\0')
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (flag == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}
