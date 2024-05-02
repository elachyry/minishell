/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 04:02:38 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/02 00:34:00 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_env(void)
{
    t_env *current;
	
	current = g_shell_data.environment_list; // Start from the head of the environment list
    while (current)  // Traverse the environment list and print each environment variable
    {
		if (current->value != NULL)
        	printf("%s%s\n", current->key, current->value);
        current = current->next;
    }

    return 0; // Return 0 to indicate successful execution
}
