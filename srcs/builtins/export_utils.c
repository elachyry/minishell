/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:28:59 by akaddour          #+#    #+#             */
/*   Updated: 2024/06/02 18:33:41 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_key_value(char *str, char *key, char *value)
{
	char	*old_value;
	char	*new_value;

	if (ft_strstr(str, "+=") && get_env_value(key))
	{
		old_value = get_env_value(key);
		new_value = gc_malloc(ft_strlen(old_value) + ft_strlen(value) + 1);
		ft_strcpy(new_value, old_value);
		ft_strcat(new_value, value);
		update_env_value(key, new_value);
		// free(new_value);
	}
	else if (value || !get_env_value(key))
		update_env_value(key, value);
}

void	sort_env_array(t_env **env_array, int count)
{
	t_env	*temp;
	int		sorted;
	int		j;

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
