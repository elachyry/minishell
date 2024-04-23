/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.1337.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 04:59:08 by melachyr          #+#    #+#             */
/*   Updated: 2024/04/02 00:51:17 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*pwd(void) //returns NULL if there's a problem!!
{
	char	*path;

	path = getcwd(NULL, 0);
	return (path);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	printf("path is %s\n", pwd());
// 	return (0);
// }