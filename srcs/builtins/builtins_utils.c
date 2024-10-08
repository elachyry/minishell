/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 06:00:18 by akaddour          #+#    #+#             */
/*   Updated: 2024/06/14 20:23:27 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_new_key(char *key, char *value)
{
	t_env	*new;

	new = gc_malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = g_shell_data.environment_list;
	g_shell_data.environment_list = new;
}

void	update_env_value(char *key, char *value)
{
	t_env	*env;

	env = g_shell_data.environment_list;
	while (env)
	{
		if (!ft_strcmp(env->key, key))
		{
			if (value)
				env->value = ft_strdup(value);
			else
				env->value = NULL;
			return ;
		}
		env = env->next;
	}
	add_new_key(key, value);
}

char	*get_env_value(char *key)
{
	t_env	*env;

	env = g_shell_data.environment_list;
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	is_valid_key(char *key)
{
	if (!ft_isalpha(*key) && *key != '_')
		return (0);
	while (*key)
	{
		if (!ft_isalnum(*key) && *key != '_')
			return (0);
		key++;
	}
	return (1);
}

void	update_env(void)
{
	t_env	*env;
	int		i;
	char	**new_env;

	env = g_shell_data.environment_list;
	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	new_env = gc_malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		perror_message("malloc", EXIT_FAILURE);
	i = 0;
	env = g_shell_data.environment_list;
	while (env)
	{
		new_env[i] = ft_strjoin(env->key, "=");
		new_env[i] = ft_strjoin(new_env[i], env->value);
		i++;
		env = env->next;
	}
	new_env[i] = NULL;
	g_shell_data.environment = new_env;
}
