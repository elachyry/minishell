/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:38:47 by akaddour          #+#    #+#             */
/*   Updated: 2024/05/04 06:18:30 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_export_print(void)
{
    t_env	*env;

    env = g_shell_data.environment_list;
    while (env)
    {
        if (env->value)
            printf("declare -x %s=\"%s\"\n", env->key, env->value);
        else
            printf("declare -x %s\n", env->key);
        env = env->next;
    }
}

void	display_export_error(char *key)
{
    ft_putstr_fd("export: `", 2);
    ft_putstr_fd(key, 2);
    ft_putstr_fd("': not a valid identifier\n", 2);
}

int	ft_export(char **args)
{
    int		i;
    char	*key;
    char	*value;

    if (!args[1])
    {
        ft_export_print();
        return (0);
    }
    i = 1;
    while (args[i])
    {
        key = extract_key(args[i]);
        if (!key || !is_valid_key(key))
        {
            display_export_error(args[i]);
            free(key);
            return (1);
        }
        value = extract_value(args[i]);
        update_env_value(key, value);
        free(key);
        if (value)
            free(value);;
        i++;
    }
    return (0);
}