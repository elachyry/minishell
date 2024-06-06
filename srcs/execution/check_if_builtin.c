/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:13:08 by akaddour          #+#    #+#             */
/*   Updated: 2024/06/05 21:15:31 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*str_to_lower(char *str)
{
	char	*result;
	int		i;

	result = gc_malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!result)
		return (NULL);
	i = -1;
	while (str[++i])
		result[i] = ft_tolower(str[i]);
	result[i] = '\0';
	return (result);
}

int	execute_builtin(char **args)
{
	char	*result;

	result = str_to_lower(args[0]);
	if (!ft_strcmp(result, "echo"))
		return (ft_echo(args));
	if (!ft_strcmp(result, "cd"))
		return (ft_cd(args[1]));
	if (!ft_strcmp(result, "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(result, "export"))
		return (ft_export(args));
	if (!ft_strcmp(result, "unset"))
		return (ft_unset(args));
	if (!ft_strcmp(result, "env"))
		return (ft_env());
	if (!ft_strcmp(result, "exit"))
		return (ft_exit(args));
	return (0);
}

t_bool	check_if_builtin(char *arg)
{
	char	*result;

	result = str_to_lower(arg);
	if (!arg)
		return (false);
	if (!ft_strcmp(result, "echo"))
		return (true);
	if (!ft_strcmp(result, "cd"))
		return (true);
	if (!ft_strcmp(result, "pwd"))
		return (true);
	if (!ft_strcmp(result, "export"))
		return (true);
	if (!ft_strcmp(result, "unset"))
		return (true);
	if (!ft_strcmp(result, "env"))
		return (true);
	if (!ft_strcmp(result, "exit"))
		return (true);
	return (false);
}
