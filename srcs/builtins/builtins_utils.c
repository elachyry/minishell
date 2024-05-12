/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 06:00:18 by akaddour          #+#    #+#             */
/*   Updated: 2024/05/11 12:35:40 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void update_env_value(char *key, char *value)
{
    t_env *env;
    t_env *new;

    env = g_shell_data.environment_list;
    while (env)
    {
        if (!ft_strcmp(env->key, key))
        {
            free(env->value);
            if (value)
                env->value = ft_strdup(value);
            else
                env->value = NULL;
            return;
        }
        env = env->next;
    }
    new = malloc(sizeof(t_env));
    if (!new)
        return;
    new->key = ft_strdup(key);
    if (value)
        new->value = ft_strdup(value);
    else
        new->value = NULL;
    new->next = g_shell_data.environment_list;
    g_shell_data.environment_list = new;
}

char    *get_env_value(char *key)
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
