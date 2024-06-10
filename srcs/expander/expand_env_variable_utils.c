/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_variable_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 01:01:50 by akaddour          #+#    #+#             */
/*   Updated: 2024/06/10 06:38:37 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*retrieve_env_var(char *name, t_env *env)
{
	t_env	*var;

	var = env;
	while (var)
	{
		if (!ft_strcmp(var->key, name) && var->value)
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
		tmp = gc_malloc(2);
		tmp[0] = c;
		tmp[1] = 0;
		return (tmp);
	}
	len = ft_strlen(str);
	tmp = gc_malloc(len + 2);
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
	if (!ft_isalpha(*line) && *line != '_')
	{
		*value = "$";
		return (line - 1);
	}
	while (*line == '_' || ft_isalpha(*line))
	{
		name = concatenate_char(name, *line);
		line++;
	}
	if (!name)
		name = "";
	*value = retrieve_env_var(name, env);
	return (line - 1);
}
