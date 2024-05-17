/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:00:16 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/17 10:06:13 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*replace_with_val(char *str, int fd)
{
	char	*tmp;
	char	*result;
	char	*sub;
	int		i;

	i = 0;
	result = NULL;
	tmp = str;
	tmp++;
	while (*tmp && *tmp != '\'' && *tmp != '\"'
		&& !ft_isspace(*tmp) && *tmp != '$')
	{
		i++;
		tmp++;
	}
	sub = ft_substr(str, 1, i);
	if (sub)
	{
		result = get_env_value(sub);
		if (result)
			write(fd, result, ft_strlen(result));
	}
	else
		write(fd, str, 1);
	return (tmp);
}

void	expand_here_doc(char *str, int fd)
{
	int		i;

	while (*str)
	{
		if (*str == '$')
		{
			i = 0;
			if (*(str + 1) == '$')
			{
				write(fd, str, 2);
				str += 2;
				continue ;
			}
			str = replace_with_val(str, fd);
		}
		if (*str != '$')
			write(fd, str, 1);
		if (*str && *str != '$')
			str++;
	}
}
