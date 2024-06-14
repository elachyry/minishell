/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_environment_list.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:11:04 by akaddour          #+#    #+#             */
/*   Updated: 2024/06/08 15:58:45 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*add_env_var(t_env *env_list, char *key, char *value)
{
	t_env	*new_env;

	new_env = gc_malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->key = ft_strdup(key);
	new_env->value = ft_strdup(value);
	new_env->next = env_list;
	return (new_env);
}

t_env	*initialize_default_env(t_env *env_list)
{
	env_list = add_env_var(env_list, "PWD", getcwd(NULL, 0));
	env_list = add_env_var(env_list, "SHLVL", "1");
	env_list = add_env_var(env_list, "_", "/usr/bin/env");
	return (env_list);
}

t_env	*initialize_environment_list(char **env)
{
	t_env	*env_list;
	t_env	*new_env;
	int		i;

	i = 0;
	env_list = NULL;
	if (!env || !*env)
	{
		env_list = initialize_default_env(env_list);
	}
	else
	{
		while (env[i])
		{
			new_env = gc_malloc(sizeof(t_env));
			if (!new_env)
				return (NULL);
			new_env->key = extract_key(env[i]);
			new_env->value = extract_value(env[i]);
			new_env->next = env_list;
			env_list = new_env;
			i++;
		}
	}
	return (env_list);
}
