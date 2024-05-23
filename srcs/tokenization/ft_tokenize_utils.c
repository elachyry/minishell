/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 04:27:20 by akaddour          #+#    #+#             */
/*   Updated: 2024/05/23 14:19:29 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_skip_spaces(char **line)
{
	while (**line && ft_isspace(**line))
		(*line)++;
}

void	remove_node(t_token **head, t_token *node)
{
	if (!node)
		return ;
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	if (*head == node)
		*head = node->next;
	free(node->value);
	free(node);
}

void	add_node_after(t_token *target_node, t_token *new_node)
{
	if (!target_node || !new_node)
		return ;
	new_node->next = target_node->next;
	new_node->prev = target_node;
	if (target_node->next)
		target_node->next->prev = new_node;
	target_node->next = new_node;
}

t_token	*create_token_node(const char *value, int type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
	{
		printf("Error: malloc failed\n");
		exit(1);
	}
	new_token->value = ft_strdup(value);
	new_token->type = type;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

t_token	*add_token(t_token *token_list, t_token_type type, char *value)
{
	t_token	*new_token;
	t_token	*tmp;

	new_token = create_token_node(value, type);
	if (!token_list)
		return (new_token);
	tmp = token_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_token;
	new_token->prev = tmp;
	return (token_list);
}
