/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:38:47 by akaddour          #+#    #+#             */
/*   Updated: 2024/05/21 15:31:47 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_env_array(t_env **env_array, int count)
{
	int	j;

	j = 0;
	while (j < count)
	{
		if (env_array[j]->value)
			printf("declare -x %s=\"%s\"\n", env_array[j]->key,
				env_array[j]->value);
		else
			printf("declare -x %s\n", env_array[j]->key);
		j++;
	}
}

static void	fill_env_array(t_env **env_array, t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env_array[i++] = env;
		env = env->next;
	}
}

static void	ft_export_print(void)
{
	t_env	*env;
	t_env	**env_array;
	int		count;

	env = g_shell_data.environment_list;
	env_array = NULL;
	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	env_array = (t_env **)malloc(count * sizeof(t_env *));
	if (!env_array)
	{
		perror("Memory allocation failed");
		exit(1);
	}
	env = g_shell_data.environment_list;
	fill_env_array(env_array, env);
	sort_env_array(env_array, count);
	print_env_array(env_array, count);
	free(env_array);
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
		return (ft_export_print(), 0);
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
		handle_key_value(args[i], key, value);
		free(key);
		if (value)
			free(value);
		i++;
	}
	return (0);
}
