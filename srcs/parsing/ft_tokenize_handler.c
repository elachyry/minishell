/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 04:46:34 by akaddour          #+#    #+#             */
/*   Updated: 2024/04/28 04:52:36 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*handle_less_than(char **input, t_token *token_list)
{
	if (*(*input + 1) == '<')
	{
		token_list = add_token(token_list, DoubleLessThanOperator, "<<");
		*input += 2;
	}
	else
	{
		token_list = add_token(token_list, LessThanOperator, "<");
		(*input)++;
	}
	return (token_list);
}

t_token	*handle_greater_than(char **input, t_token *token_list)
{
	if (*(*input + 1) == '>')
	{
		token_list = add_token(token_list, DoubleGreaterThanOperator, ">>");
		*input += 2;
	}
	else
	{
		token_list = add_token(token_list, GreaterThanOperator, ">");
		(*input)++;
	}
	return (token_list);
}

t_token	*handle_parenthesis(char **input, t_token *token_list)
{
	if (**input == '(')
	{
		token_list = add_token(token_list, OpeningParenthesis, "(");
		(*input)++;
	}
	else if (**input == ')')
	{
		token_list = add_token(token_list, ClosingParenthesis, ")");
		(*input)++;
	}
	return (token_list);
}
