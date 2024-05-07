/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 04:02:38 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/07 11:14:18 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(void)
{
	t_env	*env;

	env = g_shell_data.environment_list;
	while (env)
	{
		if (env->value && ft_strcmp(env->value, ""))
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}