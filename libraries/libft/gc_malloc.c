/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 17:17:12 by akaddour          #+#    #+#             */
/*   Updated: 2024/06/08 23:31:27 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*gc_malloc(size_t size)
{
	void	*ptr;
	t_list	*new_block;

	ptr = malloc(size);
	if (!ptr)
	{
		printf("Memory allocation failed\n");
		exit(1);
	}
	new_block = ft_lstnew(ptr);
	if (!new_block)
	{
		printf("Memory block creation failed\n");
		free(ptr);
		exit(1);
	}
	ft_lstadd_back(&g_shell_data.trash, new_block);
	return (ptr);
}

void	gc_cleanup(void)
{
	ft_lstclear(&g_shell_data.trash, free);
}
