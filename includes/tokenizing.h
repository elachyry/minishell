/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 01:20:08 by akaddour          #+#    #+#             */
/*   Updated: 2024/04/28 04:58:36 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZING_H
# define TOKENIZING_H

typedef enum e_token_type
{
	IDENTIFIER,
	LessThanOperator,
	GreaterThanOperator,
	DoubleLessThanOperator,
	DoubleGreaterThanOperator,
	PipeSymbol,
	OpeningParenthesis,
	ClosingParenthesis,
	LogicalAnd,
	LogicalOr,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

t_token	*ft_tokenize(char *input);
int		ft_isspace(char c);
void	ft_skip_spaces(char **line);
t_token	*add_token(t_token *token_list, t_token_type type, char *value);
t_token	*handle_less_than(char **input, t_token *token_list);
t_token	*handle_greater_than(char **input, t_token *token_list);
t_token	*handle_parenthesis(char **input, t_token *token_list);

#endif