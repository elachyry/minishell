/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 01:36:59 by akaddour          #+#    #+#             */
/*   Updated: 2024/05/10 16:11:31 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static int check_option(char *s)
// {
//     int i = 1;

//     if (s[0] != '-')
//         return (0);
// 	if (s[1] == '\0')
//         return (0);
//     while (s[i])
//     {
//         if (s[i] != 'n')
//             return (0);
//         i++;
//     }
//     return (1);
// }

// int ft_echo(char **args)
// {
// 	int i;
// 	int flag;

// 	i = 1;
// 	flag = 0;
// 	while (args[i] && check_option(args[i]))
// 	{
// 		flag = 1;
// 		i++;
// 	}
// 	while (args[i])
// 	{
// 		printf("%s", args[i]);
// 		if (args[i + 1])
// 			printf(" ");
// 		i++;
// 	}
// 	if (!flag)
// 		printf("\n");
// 	return (0);
// }


static int	ft_check_option(char *s)
{
	int	i;

	i = 0;
	if (s[0] != '-')
		return (0);
	i++;
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
	int	opt;
	// int j = 0;
	
	// while (args[j])
	// {
	// 	printf("args[%d] = %s\n", j, args[j]);
	// 	j++;
	// }
	i = 1;
	opt = 0;
	while (args[i] != NULL && ft_check_option(args[i]) == 1)
	{
		opt = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1] && args[i][0] != '\0')
    		ft_putstr_fd(" ", 1);
		i++;
	}
	if (opt == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}