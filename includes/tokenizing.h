/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 01:20:08 by akaddour          #+#    #+#             */
/*   Updated: 2024/05/23 14:52:42 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZING_H
# define TOKENIZING_H

typedef enum e_bool
{
	true = 1,
	false = 0,
}	t_bool;

// tokes types
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

// double linked list
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_ast_node
{
	t_token_type		type;
	char				**args;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

void		display_tokens(t_token *tokens);
t_token		*ft_tokenize(char *input);
void		ft_skip_spaces(char **line);
t_token		*add_token(t_token *token_list, t_token_type type, char *value);
t_token		*handle_less_than(char **input, t_token *token_list);
t_token		*handle_greater_than(char **input, t_token *token_list);
t_token		*handle_parenthesis(char **input, t_token *token_list);
t_token		*handle_pipe(char **input, t_token *token_list);
t_token		*create_token_node(const char *value, int type);
void		add_node_after(t_token *target_node, t_token *new_node);
void		remove_node(t_token **head, t_token *node);

//parsing
t_ast_node	*new_ast_node(t_token_type type);
t_ast_node	*new_ast_file_node(t_token *token);
t_ast_node	*parse_command(t_token	**tokens, t_bool is_custom);
t_ast_node	*parse_cmd_sep_args(t_token *tokens, t_token *args);
t_ast_node	*parse_parenthese(t_token **tokens);
t_ast_node	*parse_pipeline(t_token **tokens);
t_ast_node	*parse_logical_operator(t_token **tokens);
t_ast_node	*parse_tokens(t_token **tokens);
t_ast_node	*parse_redirection(t_token **tokens);
void		generate_ast_diagram(t_ast_node *root);

#endif