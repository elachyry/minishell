/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:46:50 by melachyr          #+#    #+#             */
/*   Updated: 2024/06/07 00:57:10 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_fix_lst(t_listt **lst)
{
	t_listt	*new_node;
	t_listt	*last_node;
	int		i;
	int		j;
	char	*str;

	if (lst == NULL)
		return ;
	str = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (str == NULL)
		return ;
	last_node = *lst;
	while (last_node->next != NULL)
		last_node = last_node->next;
	j = 0;
	i = 0;
	while (last_node->content[i] != '\0' && last_node->content[i] != '\n')
		i++;
	while (last_node->content[i] != '\0')
		str[j++] = last_node->content[++i];
	str[j] = '\0';
	new_node = ft_lstneww(str);
	ft_free_lst(lst, new_node, str);
}

void	ft_get_string(t_listt *lst, char *str)
{
	int	i;
	int	j;

	j = 0;
	while (lst != NULL)
	{
		i = 0;
		while (lst->content[i] != '\0')
		{
			if (lst->content[i] == '\n')
			{
				str[j++] = '\n';
				str[j] = '\0';
				return ;
			}
			str[j++] = lst->content[i++];
		}
		lst = lst->next;
	}
	str[j] = '\0';
}

char	*ft_extract_line(t_listt *lst)
{
	char	*next_line;
	int		next_line_len;

	next_line_len = ft_get_next_line_len(lst);
	next_line = (char *)malloc(sizeof(char) * (next_line_len + 1));
	if (next_line == NULL)
		return (NULL);
	ft_get_string(lst, next_line);
	return (next_line);
}

void	ft_fill_lst(t_listt **lst, int fd, t_listt *last_node)
{
	int		nbr_char;
	char	*str;

	while (ft_fetsh_new_line(*lst) == 0 && lst != NULL)
	{
		str = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (str == NULL)
			return ;
		nbr_char = read(fd, str, BUFFER_SIZE);
		if (nbr_char <= 0)
		{
			free(str);
			return ;
		}
		str[nbr_char] = '\0';
		if (*lst == NULL)
			*lst = ft_lstneww(str);
		else
		{
			last_node = *lst;
			while (last_node->next != NULL)
				last_node = last_node->next;
			last_node->next = ft_lstneww(str);
		}
	}
}

char	*get_next_line(int fd)
{
	static t_listt	*lst = NULL;
	char			*next_line;
	t_listt			*last_node;

	last_node = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647
		|| read(fd, &next_line, 0) < 0)
	{
		ft_lstclearr(&lst);
		return (NULL);
	}
	ft_fill_lst(&lst, fd, last_node);
	if (lst == NULL)
	{
		ft_lstclearr(&lst);
		return (NULL);
	}
	next_line = ft_extract_line(lst);
	ft_fix_lst(&lst);
	return (next_line);
}
