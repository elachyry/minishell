/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 04:27:20 by akaddour          #+#    #+#             */
/*   Updated: 2024/05/05 07:08:20 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_skip_spaces(char **line)
{
	while (**line && ft_isspace(**line))
		(*line)++;
}

t_token	*add_token(t_token *token_list, t_token_type type, char *value)
{
	t_token	*new_token;
	t_token	*tmp;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		printf("Error: malloc failed\n");
		exit(1);
	}
	new_token->type = type;
	new_token->value = value;
	new_token->next = NULL;
	new_token->prev = NULL;
	if (!token_list)
		return (new_token);
	tmp = token_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_token;
	new_token->prev = tmp;
	return (token_list);
}
