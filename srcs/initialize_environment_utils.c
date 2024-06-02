/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_environment_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:21:34 by akaddour          #+#    #+#             */
/*   Updated: 2024/06/02 17:24:22 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	extract_path(void)
{
	char	*path;
	t_env	*env;

	env = g_shell_data.environment_list;
	path = NULL;
	while (env)
	{
		if (!ft_strcmp(env->key, "PATH"))
			path = env->value;
		env = env->next;
	}
	if (path)
		g_shell_data.path = ft_split(path, ':');
	else
		g_shell_data.path = ft_split("", ':');
}

char	*extract_key(char *env)
{
	char	*key;
	int		i;

	i = 0;
	while (env[i] && env[i] != '=' && !(env[i] == '+' && env[i + 1] == '='))
		i++;
	key = gc_malloc(i + 1);
	if (!key)
		return (NULL);
	ft_strncpy(key, env, i);
	key[i] = '\0';
	return (key);
}

char	*copy_value(char *env, int start)
{
	char	*value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	value = gc_malloc(strlen(env) - start + 1);
	if (!value)
		return (NULL);
	while (env[start])
	{
		if (env[start] != '\'' && env[start] != '\"')
			value[j++] = env[start];
		start++;
	}
	value[j] = '\0';
	return (value);
}

char	*extract_value(char *env)
{
	int		i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (!env[i])
		return (NULL);
	return (copy_value(env, i + 1));
}
