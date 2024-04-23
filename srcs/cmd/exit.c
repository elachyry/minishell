/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.1337.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 00:57:54 by melachyr          #+#    #+#             */
/*   Updated: 2024/04/02 01:03:56 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(void)
{
	int	pid;

	pid = getppid();
	if (kill(pid, SIGKILL) == -1)
	{
		perror("kill");
		exit(1);
	}
}
// int	main(int argc, char **argv, char **envp)
// {
// 	ft_exit();
// 	return (0);
// }
