/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 04:27:20 by akaddour          #+#    #+#             */
/*   Updated: 2024/05/21 13:52:28 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_skip_spaces(char **line)
{
	while (**line && ft_isspace(**line))
		(*line)++;
}
t_token	*create_token_node(const char *value, int type)
{
	t_token *new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
	{
		printf("Error: malloc failed\n");
		exit(1);
	}
	new_token->value = strdup(value);
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
