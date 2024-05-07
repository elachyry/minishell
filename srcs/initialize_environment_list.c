/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_environment_list.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:11:04 by akaddour          #+#    #+#             */
/*   Updated: 2024/05/07 03:53:45 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	extract_path(void)
{
	char	*path;
	t_env	*env;
	
	env = g_shell_data.environment_list;
	
	while (env)
	{
		if (!ft_strcmp(env->key, "PATH"))
			path = env->value;
		env = env->next;
	}
	g_shell_data.path = ft_split(path, ':');
	// for (int i = 0; g_shell_data.path[i] != NULL; i++)
	// {
	// 	printf("%s\n", g_shell_data.path[i]);
	// }
	free(path);
}

char    *extract_key(char *env)
{
    char    *key;
    int     i;

    i = 0;
    while (env[i] && env[i] != '=')
        i++;
    key = malloc(i + 1);
    if (!key)
        return (NULL);
    i = 0;
    while (env[i] && env[i] != '=')
    {
        key[i] = env[i];
        i++;
    }
    key[i] = '\0';
    return (key);
}

char    *extract_value(char *env)
{
    char    *value;
    int     i;
    int     j;

    i = 0;
    while (env[i] && env[i] != '=')
        i++;
    if (!env[i])
        return (NULL);
    i++;
    j = i;
    while (env[j])
        j++;
    value = malloc(j - i + 1);
    if (!value)
        return (NULL);
    j = 0;
    while (env[i])
    {
        value[j] = env[i];
        i++;
        j++;
    }
    value[j] = '\0';
    return (value);
}

t_env	*initialize_environment_list(char **env)
{
    t_env	*env_list;
    t_env	*new_env;
    int		i;

    i = 0;
    env_list = NULL;
    while (env[i])
    {
        new_env = malloc(sizeof(t_env));
        if (!new_env)
            return (NULL);
        new_env->key = extract_key(env[i]);
        new_env->value = extract_value(env[i]);
        new_env->next = env_list;
        env_list = new_env;
        i++;
    }
    return (env_list);
}
