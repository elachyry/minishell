/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 08:53:00 by melachyr          #+#    #+#             */
/*   Updated: 2024/06/07 00:57:16 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_listt	*ft_lstneww(char *content)
{
	t_listt	*node;

	node = (t_listt *)malloc(sizeof(t_listt));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

void	ft_lstclearr(t_listt **lst)
{
	t_listt	*current;

	while (*lst != NULL)
	{
		current = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = current;
	}
}

int	ft_fetsh_new_line(t_listt *lst)
{
	int	i;

	if (lst == NULL)
		return (0);
	while (lst != NULL)
	{
		i = 0;
		while (lst->content[i] != '\0')
		{
			if (lst->content[i] == '\n')
				return (1);
			i++;
		}
		lst = lst->next;
	}
	return (0);
}

int	ft_get_next_line_len(t_listt *lst)
{
	int	i;
	int	len;

	len = 0;
	while (lst != NULL)
	{
		i = 0;
		while (lst->content[i] != '\0')
		{
			if (lst->content[i] == '\n')
			{
				len++;
				return (len);
			}
			i++;
			len++;
		}
		lst = lst->next;
	}
	return (len);
}

void	ft_free_lst(t_listt **lst, t_listt *new_node, char *str)
{
	if (lst == NULL)
		return ;
	ft_lstclearr(lst);
	if (new_node->content[0] != '\0')
		*lst = new_node;
	else
	{
		free(str);
		free(new_node);
	}
}
