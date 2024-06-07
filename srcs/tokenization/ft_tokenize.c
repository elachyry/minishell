/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 01:25:38 by akaddour          #+#    #+#             */
/*   Updated: 2024/06/06 17:27:45 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_quote_status(char c, int *in_quote, char *quote_char)
{
	if (!*in_quote && (c == '\'' || c == '\"'))
	{
		*in_quote = 1;
		*quote_char = c;
	}
	else if (*in_quote && c == *quote_char)
		*in_quote = 0;
}

t_token	*handle_other_chars(char **input, t_token *token_list)
{
	char	*start;
	int		in_quote;
	char	quote_char;
	char	*identifier;

	start = *input;
	in_quote = 0;
	quote_char = '\0';
	while (**input)
	{
		update_quote_status(**input, &in_quote, &quote_char);
		if (!in_quote && ft_strchr(" \t\n><|()&", **input))
			break ;
		(*input)++;
	}
	identifier = ft_strndup(start, *input - start);
	if (identifier == NULL)
	{
		printf("Error: malloc failed\n");
		exit(1);
	}
	token_list = add_token(token_list, IDENTIFIER, identifier);
	return (token_list);
}

t_token	*handle_special_chars(char **input, t_token *token_list)
{
	if (**input == '<')
		token_list = handle_less_than(input, token_list);
	else if (**input == '>')
		token_list = handle_greater_than(input, token_list);
	else if (**input == '(' || **input == ')')
		token_list = handle_parenthesis(input, token_list);
	else if (**input == '&')
	{
		if (*(*input + 1) == '&')
		{
			token_list = add_token(token_list, LogicalAnd, "&&");
			*input += 2;
		}
		else
		{
			token_list = add_token(token_list, IDENTIFIER, "&");
			(*input)++;
		}
	}
	else if (**input == '|')
		token_list = handle_pipe(input, token_list);
	return (token_list);
}

t_token	*ft_tokenize(char *input)
{
	t_token	*token_list;

	token_list = NULL;
	while (*input)
	{
		if (ft_isspace(*input))
			ft_skip_spaces(&input);
		else if (*input == '<' || *input == '>' || *input == '('
			|| *input == ')' || *input == '&' || *input == '|')
			token_list = handle_special_chars(&input, token_list);
		else
		{
			token_list = handle_other_chars(&input, token_list);
		}
	}
	return (token_list);
}
