/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:53:01 by akaddour          #+#    #+#             */
/*   Updated: 2024/05/14 13:54:18 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*str;

	if (!s1)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr_2(set, s1[start]))
		start++;
	while (end > start && s1[end - 1] && ft_strchr_2(set, s1[end - 1]))
		end--;
	if (end <= start)
		return (ft_strdup(""));
	str = (char *)malloc(sizeof(char) * (end - start + 1));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, &s1[start], (end - start + 1));
	return (str);
}


// int main(void)
// {
// 	char *str = "\'\"$USER\'\"";
// 	printf("result : %s\n", ft_strtrim_2(str, "\'\""));
// }
