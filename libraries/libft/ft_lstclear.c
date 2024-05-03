/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:42:29 by akaddour          #+#    #+#             */
/*   Updated: 2023/11/17 17:13:59 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;

	if (lst != NULL && del != NULL)
	{
		while (*lst != NULL)
		{
			current = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = current;
		}
	}
}
