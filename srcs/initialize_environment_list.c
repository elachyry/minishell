/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_environment_list.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 23:51:09 by akaddour          #+#    #+#             */
/*   Updated: 2024/05/02 00:03:17 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*extract_key(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (ft_substr(str, 0, i));
		i++;
	}
	return (NULL);
}

char	*extract_value(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			return (ft_substr(str, i, ft_strlen(str) - i));
		}
		i++;
	}
	return (NULL);
}

static t_env *create_environment_node(char *key, char *value)
{
    t_env *new_node;
    
    new_node = (t_env *)calloc(1, sizeof(t_env));
    if (!new_node)
        return NULL;
    new_node->key = strdup(key);
    if (value)
        new_node->value = strdup(value);
    new_node->next = NULL;
    return (new_node);
}

void add_to_environment_list(t_env *new_node)
{
    t_env *current;
    
    current = g_shell_data.environment_list;
    if (!current)
    {
        g_shell_data.environment_list = new_node;
        return;
    }
    while (current && current->next)
        current = current->next;
    current->next = new_node;
}

void initialize_environment_list(void)
{
	int		i;
	char	*key;
	char	*value;
	char	**environment;

	i = 0;
	environment = g_shell_data.environment;
	while (environment[i])
	{
		key = extract_key(environment[i]);
        value = extract_value(environment[i]);
        add_to_environment_list(create_environment_node(key, value));
        i++;
	}
}