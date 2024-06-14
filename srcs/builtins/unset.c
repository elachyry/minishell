/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 00:39:02 by akaddour          #+#    #+#             */
/*   Updated: 2024/06/08 15:20:59 by akaddour         ###   ########.fr       */
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
		if (!ft_strcmp(env->key, key))
		{
			if (prev)
				prev->next = env->next;
			else
				g_shell_data.environment_list = env->next;
			return ;
		}
		prev = env;
		env = env->next;
	}
}

int	ft_unset(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		delete_env_value(args[i]);
		i++;
	}
	return (0);
}
