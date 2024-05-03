/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 01:36:59 by akaddour          #+#    #+#             */
/*   Updated: 2024/05/03 01:22:13 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int check_option(char *s)
{
    int i = 1;

    if (s[0] != '-')
        return 0;

    while (s[i])
    {
        if (s[i] != 'n')
            return 0;
        i++;
    }
    return 1;
}

int ft_echo(char **args)
{
	int i;
	int flag;

	i = 1;
	flag = 0;
	while (args[i] && check_option(args[i]))
	{
		flag = 1;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!flag)
		printf("\n");
	return (0);
}

// int main(int argc, char *argv[]) {
//     // Testing with various arguments
//     ft_echo(argv);
//     return 0;
// }