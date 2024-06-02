/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:07:30 by akaddour          #+#    #+#             */
/*   Updated: 2024/06/02 18:34:29 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_d_q(char current_char, int in_single_quotes, \
int in_double_quotes)
{
	if (current_char == '\"' && !in_single_quotes)
	{
		in_double_quotes = !in_double_quotes;
	}
	return (in_double_quotes);
}

static int	handle_s_q(char current_char, int in_double_quotes, \
int in_single_quotes)
{
	if (current_char == '\'' && !in_double_quotes)
	{
		in_single_quotes = !in_single_quotes;
	}
	return (in_single_quotes);
}

static char	*allocate_new_str(int length)
{
	char	*new_str;

	new_str = gc_malloc(length + 1);
	if (!new_str)
		return (NULL);
	return (new_str);
}

char	*remove_all_quotes(char *str)
{
	char	*new_str;
	int		i;
	int		j;
	int		in_s_q;
	int		in_d_q;

	in_s_q = 0;
	in_d_q = 0;
	new_str = allocate_new_str(ft_strlen(str));
	if (!new_str)
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
	{
		in_d_q = handle_d_q(str[i], in_s_q, in_d_q);
		in_s_q = handle_s_q(str[i], in_d_q, in_s_q);
		if (!(str[i] == '\"' && !in_s_q) && !(str[i] == '\'' && !in_d_q))
		{
			new_str[j] = str[i];
			j++;
		}
	}
	new_str[j] = '\0';
	return (new_str);
}

void	expand_quotes(char **args)
{
	int		i;
	char	*new_str;

	i = 0;
	while (args[i] != NULL)
	{
		new_str = remove_all_quotes(args[i]);
		// free(args[i]);
		args[i] = new_str;
		i++;
	}
}

// t_bool	contains_wildcard(char *ident)
// {
// 	while (*ident)
// 	{
// 		if (*ident == '*')
// 			return (true);
// 		ident++;
// 	}
// 	return (false);
// }

// t_token	*skip_parentheses(t_token *token)
// {
// 	while (token && token->type == OpeningParenthesis)
// 		token = token->next;
// 	while (token && token->type != ClosingParenthesis)
// 		token = token->next;
// 	while (token && token->type == ClosingParenthesis)
// 		token = token->next;
// 	return (token);
// }

// t_token	*expand_quotes(t_token *tokens)
// {
// 	t_token	*token;
// 	char	*tmp;

// 	token = tokens;
// 	while (token)
// 	{
// 		if (token->type == OpeningParenthesis)
// 		{
// 			token = skip_parentheses(token);
// 			continue ;
// 		}
// 		if (token->type == IDENTIFIER)
// 		{
// 			if (contains_wildcard(token->value))
// 			{
// 				token = token->next;
// 				continue ;
// 			}
// 			tmp = remove_all_quotes(token, token->value);
// 			free(token->value);
// 			token->value = tmp;
// 		}
// 		token = token->next;
// 	}
// 	return (tokens);
// }
