/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:43:17 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/29 12:14:03 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	perror_message(char *file, int status)
{
	ft_putstr_fd("Minishell: ", 2);
	perror(file);
	exit(status);
}

void	execve_fail(char **args)
{
	if (!ft_strcmp(args[0], "."))
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": filename argument required", 2);
		ft_putstr_fd("\n", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": usage: . filename [arguments]", 2);
		ft_putstr_fd("\n", 2);
		exit(2);
	}
	if (access(args[0], F_OK) == 0)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": Is a directory", 2);
		ft_putstr_fd("\n", 2);
		exit(126);
	}
	perror_message("execve", EXIT_FAILURE);
}

void	cmd_not_found(char **args, int status)
{
	if (!status || status == 4)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": command not found", 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
	else if (status == 2)
		perror_message(args[0], 126);
	else if (status == 3)
		perror_message(args[0], 127);
}
