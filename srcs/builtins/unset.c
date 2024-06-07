/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 00:39:02 by akaddour          #+#    #+#             */
/*   Updated: 2024/06/07 15:47:06 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	delete_env_value(char *key)
{
	t_env	*env;
	t_env	*prev;

	env = g_shell_data.environment_list;
	prev = NULL;
	while (env)
	{
		if (!strcmp(env->key, key))
		{
			if (prev)
				prev->next = env->next;
			else
				g_shell_data.environment_list = env->next;
			// free(env->key);
			// free(env->value);
			// free(env);
			return ;
		}
		prev = env;
		env = env->next;
	}
}

// static void	display_unset_error(char *key)
// {
// 	ft_putstr_fd("minishell: unset: `", 2);
// 	ft_putstr_fd(key, 2);
// 	ft_putstr_fd("': not a valid identifier\n", 2);
// }

int	ft_unset(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!is_valid_key(args[i]))
		{
			// display_unset_error(args[i]);
			return (0);
		}
		delete_env_value(args[i]);
		i++;
	}
	return (0);
}
