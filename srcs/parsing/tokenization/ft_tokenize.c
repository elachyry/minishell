/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 01:25:38 by akaddour          #+#    #+#             */
/*   Updated: 2024/04/29 07:00:24 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_token	*handle_other_chars(char **input, t_token *token_list)
{
	char	*start;
	char	*identifier;
	char	quote_type;

	start = *input;
	if (**input == '\'' || **input == '\"')
	{
		quote_type = **input;
		(*input)++;
		while (*(*input + 1) && **input != quote_type)
			(*input)++;
		(*input)++;
	}
	else
	{
		while (**input && **input != ' ' && **input != '<' && **input != '>'
			&& **input != '|' && **input != '(' && **input != ')'
			&& **input != '&' && **input != '|' && **input != '\''
			&& **input != '\"')
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

// main tokenizing function
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
			token_list = handle_other_chars(&input, token_list);
	}
	return (token_list);
}
