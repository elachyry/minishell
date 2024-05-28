/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_variable_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 01:01:50 by akaddour          #+#    #+#             */
/*   Updated: 2024/05/28 20:57:23 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*retrieve_env_var(char *name, t_env *env)
{
	t_env	*var;
	int		max;

	var = env;
	while (var)
	{
		max = ft_strlen(var->key);
		if ((int) ft_strlen(name) > max)
			max = ft_strlen(name);
		if (!ft_strncmp(var->key, name, max) && var->value)
			return (var->value);
		var = var->next;
	}
	return ("");
}

char	*concatenate_char(char *str, char c)
{
	char	*tmp;
	int		len;

	if (!str)
	{
		tmp = malloc(2);
		tmp[0] = c;
		tmp[1] = 0;
		return (tmp);
	}
	len = ft_strlen(str);
	tmp = malloc(len + 2);
	ft_strlcpy(tmp, str, len + 1);
	tmp[len] = c;
	tmp[len + 1] = 0;
	return (tmp);
}

char	*fetch_variable_value(char **value, char *line, t_env *env)
{
	char	*name;

	name = NULL;
	if (*line == '?')
	{
		*value = ft_itoa(g_shell_data.status);
		return (line);
	}
	if (!ft_isalnum(*line) && *line != '_')
	{
		*value = "$";
		if (*line != -1)
			return (line - 1);
		return (line);
	}
	while (*line == '_' || ft_isalnum(*line))
	{
		name = concatenate_char(name, *line);
		line++;
	}
	if (!name)
		name = "";
	*value = retrieve_env_var(name, env);
	return (line - 1);
}
