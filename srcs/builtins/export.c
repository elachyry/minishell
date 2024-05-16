/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:38:47 by akaddour          #+#    #+#             */
/*   Updated: 2024/05/16 09:51:45 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void sort_env_array(t_env **env_array, int count)
{
    t_env *temp;
    int sorted;
    int j;

    sorted = 0;
    while (!sorted)
    {
        sorted = 1;
        j = 0;
        while (j < count - 1)
        {
            if (ft_strcmp(env_array[j]->key, env_array[j + 1]->key) > 0)
            {
                temp = env_array[j];
                env_array[j] = env_array[j + 1];
                env_array[j + 1] = temp;
                sorted = 0;
            }
            j++;
        }
    }
}

static void print_env_array(t_env **env_array, int count)
{
    int j;

    j = 0;
    while (j < count)
    {
        if (env_array[j]->value)
            printf("declare -x %s=\"%s\"\n", env_array[j]->key, env_array[j]->value);
        else
            printf("declare -x %s\n", env_array[j]->key);
        j++;
    }
}

static void ft_export_print(void)
{
    t_env *env;
    t_env **env_array;
    int count;
    int i;

    env = g_shell_data.environment_list;
    env_array = NULL;
    count = 0;
    // Count the number of environment variables
    while (env) {
        count++;
        env = env->next;
    }
    // Allocate memory for environment variable pointers
    env_array = (t_env **)malloc(count * sizeof(t_env *));
    if (!env_array) {
        perror("Memory allocation failed");
        exit(1);
    }
    // Fill the array with environment variable pointers
    env = g_shell_data.environment_list;
    i = 0;
    while (env) {
        env_array[i++] = env;
        env = env->next;
    }
    sort_env_array(env_array, count);
    print_env_array(env_array, count);
    free(env_array); // Free the array of pointers
}

static void	display_export_error(char *key)
{
    ft_putstr_fd("minishell: export: `", 2);
    ft_putstr_fd(key, 2);
    ft_putstr_fd("': not a valid identifier\n", 2);
}

int	ft_export(char **args)
{
    int		i;
    char	*key;
    char	*value;

    if (!args[1])
        return (ft_export_print() ,0);
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
        // Only update the value if it's not null or if the key doesn't already exist
        if (value || !get_env_value(key))
            update_env_value(key, value);
        free(key);
        if (value)
            free(value);
        i++;
    }
    return (0);
}
