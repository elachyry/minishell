/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 17:17:12 by akaddour          #+#    #+#             */
/*   Updated: 2024/06/05 23:01:48 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list *head = NULL;

// Function to allocate memory and track it
void* gc_malloc(size_t size) {
    void *ptr = malloc(size);
    if (!ptr) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    t_list *newBlock = ft_lstnew(ptr);
    if (!newBlock) {
        printf("Memory block creation failed\n");
        free(ptr);
        exit(1);
    }
    ft_lstadd_back(&head, newBlock);
    return ptr;
}

// Function to clean up all remaining allocations
void gc_cleanup() 
{
    ft_lstclear(&head, free);
}
