/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:00:16 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/17 16:05:51 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin_2(char const *s1, char const *s2, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0' && j < len)
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

static char	*replace_with_val(char *str, int fd, char **buff)
{
	char	*tmp;
	char	*result;
	char	*sub;
	int		i;

	i = 0;
	(void)fd;
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
		{
			// dprintf(2, "result = %s\n", result);
			*buff = ft_strjoin_2(*buff, result, ft_strlen(result));
			// dprintf(2, "buf21 = %s\n", *buff);
		}
			// write(fd, result, ft_strlen(result));
	}
	else
		*buff = ft_strjoin_2(*buff, str, 1);
		// write(fd, str, 1);
	return (tmp);
}

char	*expand_here_doc(char *str, int fd)
{
	int		i;
	char	*buff;
	
	buff = ft_strdup("");
	while (*str)
	{
		if (*str == '$')
		{
			i = 0;
			if (*(str + 1) == '$')
			{
				buff = ft_strjoin_2(buff, str, 2);
				// write(fd, str, 2);
				str += 2;
				continue ;
			}
			str = replace_with_val(str, fd, &buff);
		}
		if (*str != '$')
		{
			
			buff = ft_strjoin_2(buff, str, 1);
			// dprintf(2, "buf2 = %s\n", buff);
			
		}
			// write(fd, str, 1);
		if (*str && *str != '$')
			str++;
	}
	// dprintf(2, "buf = %s\n", buff);
	return (buff);
}
