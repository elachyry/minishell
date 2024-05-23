/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:07:30 by akaddour          #+#    #+#             */
/*   Updated: 2024/05/23 00:19:58 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	contains_wildcard(char *ident)
{
	while (*ident)
	{
		if (*ident == '*')
			return (true);
		ident++;
	}
	return (false);
}

t_token	*skip_parentheses(t_token *token)
{
	while (token && token->type == OpeningParenthesis)
		token = token->next;
	while (token && token->type != ClosingParenthesis)
		token = token->next;
	while (token && token->type == ClosingParenthesis)
		token = token->next;
	return (token);
}

t_token	*expand_quotes(t_token *tokens)
{
	t_token	*token;
	char	*tmp;

	token = tokens;
	while (token)
	{
		if (token->type == OpeningParenthesis)
		{
			token = skip_parentheses(token);
			continue ;
		}
		if (token->type == IDENTIFIER)
		{
			if (contains_wildcard(token->value))
			{
				token = token->next;
				continue ;
			}
			tmp = remove_all_quotes(token, token->value);
			free(token->value);
			token->value = tmp;
		}
		token = token->next;
	}
	return (tokens);
}

// char	*remove_all_quotes(t_token *token, char *str)
// {
// 	char	*new_str;
// 	int		i;
// 	int		j;
// 	int		in_single_quotes;
// 	int		in_double_quotes;

// 	in_single_quotes = 0;
// 	in_double_quotes = 0;
// 	new_str = malloc(ft_strlen(str) + 1);
// 	if (!new_str)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\"' && !in_single_quotes)
// 		{
// 			if (token->prev && token->prev->type == DoubleLessThanOperator)
// 				g_shell_data.simple_cmd->should_expand = false;
// 			in_double_quotes = !in_double_quotes;
// 		}
// 		else if (str[i] == '\'' && !in_double_quotes)
// 		{
// 			if (token->prev && token->prev->type == DoubleLessThanOperator)
// 				g_shell_data.simple_cmd->should_expand = false;
// 			in_single_quotes = !in_single_quotes;
// 		}
// 		else
// 		{
// 			new_str[j] = str[i];
// 			j++;
// 		}
// 		i++;
// 	}
// 	new_str[j] = '\0';
// 	return (new_str);
// }

// t_token	*expand_quotes(t_token *tokens)
// {
// 	t_token	*token;
// 	char	*tmp;
// 	char	*ident;
// 	t_bool	wildcard;

// 	token = tokens;
// 	while (token)
// 	{
// 		if (token->type == OpeningParenthesis)
// 		{
// 			while (token && token->type == OpeningParenthesis)
// 				token = token->next;
// 			while (token && token->type != ClosingParenthesis)
// 				token = token->next;
// 			while (token && token->type == ClosingParenthesis)
// 				token = token->next;
// 			continue ;
// 		}
// 		if (token->type == IDENTIFIER)
// 		{
// 			ident = token->value;
// 			wildcard = false;
// 			while (*ident)
// 			{
// 				if (*ident == '*')
// 				{
// 					if (token)
// 						token = token->next;
// 					wildcard = true;
// 					break ;
// 				}
// 				ident++;
// 			}
// 			if (wildcard)
// 				continue ;
// 			tmp = remove_all_quotes(token, token->value);
// 			free(token->value);
// 			token->value = tmp;
// 		}
// 		token = token->next;
// 	}
// 	return (tokens);
// }
