/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:58:24 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/20 22:02:41 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void remove_node(t_token **head, t_token *node)
{
	if (!node) return;
	if (node->prev) node->prev->next = node->next;
	if (node->next) node->next->prev = node->prev;
	if (*head == node) *head = node->next;
	free(node->value);
	free(node);
}

//handle if the cmd starts with redirecion
//second if handle when command comes after the file ex: >a cat <b >>c
static t_ast_node	*help_func(t_token **tokens, t_token *ptr, t_bool is_parenth)
{
	t_ast_node	*redirection_node;
	t_token 	*to_delete;

	// dprintf(2, "ggggg in red next = %s\n", (*tokens)->next->value);
	// dprintf(2, "is_paren = %d\n", is_parenth);
	// dprintf(2, "1 in red next = %s\n", (*tokens)->next->value);
	// dprintf(2, "1 in red next next = %s\n", (*tokens)->next->next->value);
	if ((*tokens)->type == DoubleLessThanOperator)
		g_shell_data.simple_cmd->nbr_here_doc++;
	redirection_node = new_ast_node((*tokens)->type);
	char	*cmd = ft_strdup("");
	
	t_token	*tmp = *tokens;
	*tokens = NULL;
	while (tmp && tmp->next)
	{
		// printf("in while tmp %s tmp->next->next %s\n", tmp->value, tmp->next->next->value);
		if (tmp && tmp->next->next && tmp->next->next->type == IDENTIFIER && (tmp->type == LessThanOperator
		|| tmp->type == DoubleLessThanOperator
		|| tmp->type == GreaterThanOperator
		|| tmp->type == DoubleGreaterThanOperator))
		{
			// printf("in if\n");
			tmp = tmp->next->next;
			while (tmp && tmp->type == IDENTIFIER)
			{
				// printf("tmp in if = %s\n", tmp->value);
				cmd = ft_strjoin(cmd, tmp->value);
				cmd = ft_strjoin(cmd, " ");
				// printf("join in if = %s\n", cmd);
				to_delete = tmp;
                tmp = tmp->next;
                remove_node(tokens, to_delete);
				// printf("tmp in if after incrme = %s\n", tmp->value);
			}
			continue ;
		}
		tmp = tmp->next;
	}
	// printf("join result = %d\n", cmd[0]);
	if (is_parenth)
	{
		redirection_node->left = parse_parenthese(&ptr);
		// printf("ptrrrr = %s\n", ptr->value);
		redirection_node->right = new_ast_file_node(ptr->next->next);
		redirection_node->right->right = parse_redirection(&ptr->next->next->next);
	}
	else
	{
		if (cmd[0] != '\0')
		{
			redirection_node->left = new_ast_node(IDENTIFIER);
			redirection_node->left->args = ft_split(cmd, ' ');
		}
		redirection_node->right = parse_command(&ptr->next, false);
	}
	// redirection_node->left = parse_redirection(tokens);
	
	// if (redirection_node->left == NULL
	// 	&& tmp->next->next
	// 	&& tmp->next->next->type == IDENTIFIER)
	// {
	// 	tmp = tmp->next;
	// 	while (tmp && tmp->next && tmp->next->next == IDENTIFIER)
	// 	{
	// 		tmp = tmp->next;
	// 		ptr = ptr->next;
	// 	}
	// 	while (tmp && tmp->type == IDENTIFIER)
	// 	{
	// 		tmp = tmp->prev;
	// 		ptr = ptr->prev;
	// 	}
	// 	tmp = tmp->next->next;
	// 	ptr->next->next = NULL;
	// 	ptr = tmp2;
	// 	if (tmp && tmp->type == IDENTIFIER)
	// 		redirection_node->left = parse_cmd_sep_args(ptr->next->next, tmp);
	// 	else
	// 		redirection_node->left = parse_command(&ptr->next->next, true);
	// }
	// redirection_node->right = parse_command(&ptr->next, false);
	return (redirection_node);
}

//handle if the redirecion comes after cmd
static t_ast_node	*help_func_2(t_token **tokens, t_token *next, t_token *ptr)
{
	t_ast_node	*redirection_node;
	t_token 	*to_delete;

	// dprintf(2, "1 in red = %s\n", (*tokens)->value);
	if (next->type == DoubleLessThanOperator)
		g_shell_data.simple_cmd->nbr_here_doc++;
	redirection_node = new_ast_node(next->type);
	// dprintf(2, "2 in red = %s\n", (*tokens)->value);
	(*tokens)->next = NULL;
	// dprintf(2, "test %s\n", next->next->next->value);
	char	*cmd = ft_strdup("");
	
	t_token	*tmp = ptr;
	while (tmp && tmp->type == IDENTIFIER)
	{
		cmd = ft_strjoin(cmd, tmp->value);
		cmd = ft_strjoin(cmd, " ");
		to_delete = tmp;
		tmp = tmp->next;
		remove_node(tokens, to_delete);
	}
	// printf("first join result = %s\n", cmd);
	tmp = next;
	// printf("tmp = %s\n", tmp->value);
	while (tmp && tmp->next)
	{
		// printf("in while tmp %s tmp->next->next %s\n", tmp->value, tmp->next->next->value);
		if (tmp && tmp->next->next && tmp->next->next->type == IDENTIFIER && (tmp->type == LessThanOperator
		|| tmp->type == DoubleLessThanOperator
		|| tmp->type == GreaterThanOperator
		|| tmp->type == DoubleGreaterThanOperator))
		{
			// printf("in if\n");
			tmp = tmp->next->next;
			while (tmp && tmp->type == IDENTIFIER)
			{
				// printf("tmp in if = %s\n", tmp->value);
				cmd = ft_strjoin(cmd, tmp->value);
				cmd = ft_strjoin(cmd, " ");
				// printf("join in if = %s\n", cmd);
				to_delete = tmp;
                tmp = tmp->next;
                remove_node(tokens, to_delete);
				// printf("tmp in if after incrme = %s\n", tmp->value);
			}
			continue ;
		}
		tmp = tmp->next;
	}
	// printf("join result = %s\n", cmd);
	redirection_node->left = new_ast_node(IDENTIFIER);
	redirection_node->left->args = ft_split(cmd, ' ');
	redirection_node->right = parse_command(&next->next, false);
	return (redirection_node);
}

//this function for parsing the redirections
//by creating a node type of the redirecion
t_ast_node	*parse_redirection(t_token **tokens)
{
	t_token		*ptr;
	t_token		*next;
	t_bool		is_parenth;

	if (!tokens || !*tokens)
		return (NULL);
	ptr = *tokens;
	// dprintf(2, "red2 = %s\n", ptr->value);
	is_parenth = false;
	if ((*tokens)->type == OpeningParenthesis)
	{
		is_parenth = true;
		// dprintf(2, "inside if in red = %s\n", (*tokens)->value);
		while ((*tokens && (*tokens)->next) && (*tokens)->type != ClosingParenthesis)
			*tokens = (*tokens)->next;
		*tokens = (*tokens)->next;
	}
	// dprintf(2, "after if in red = %s\n", (*tokens)->value);
	// dprintf(2, "red = %s\n", ptr->value);
	if (((*tokens)->type == LessThanOperator
		|| (*tokens)->type == DoubleLessThanOperator
		|| (*tokens)->type == GreaterThanOperator
		|| (*tokens)->type == DoubleGreaterThanOperator)
		&& (*tokens)->next->type != OpeningParenthesis
		&& (*tokens)->type != OpeningParenthesis)
		return (help_func(tokens, ptr, is_parenth));
	while (*tokens && (*tokens)->next && (*tokens)->next->type != OpeningParenthesis
		&& (*tokens)->type != OpeningParenthesis)
	{
		// dprintf(2, "while in red = %s\n", (*tokens)->value);
		next = (*tokens)->next;
		if ((next->type == LessThanOperator
			|| next->type == DoubleLessThanOperator
			|| next->type == GreaterThanOperator
			|| next->type == DoubleGreaterThanOperator)
			&& (*tokens)->next->type != OpeningParenthesis
			&& (*tokens)->type != OpeningParenthesis)
			return (help_func_2(tokens, next, ptr));
		*tokens = next;
	}
	return (parse_parenthese(&ptr));
}
// dprintf(2, "tmp = %s | tmp->next = %s tmp->next->next = %d | cond0 = %d | cond1 = %d | cond2 = %d | condF = %d\n", tmp->value, tmp->next->value, tmp->next->next->type == IDENTIFIER, tmp != NULL, tmp->next != NULL, (tmp->type == LessThanOperator
// 			|| tmp->type == DoubleLessThanOperator
// 			|| tmp->type == GreaterThanOperator
// 			|| tmp->type == DoubleGreaterThanOperator
// 			|| tmp->type == IDENTIFIER), tmp && tmp->next && tmp->next->next == IDENTIFIER && (tmp->type == LessThanOperator
// 			|| tmp->type == DoubleLessThanOperator
// 			|| tmp->type == GreaterThanOperator
// 			|| tmp->type == DoubleGreaterThanOperator
// 			|| tmp->type == IDENTIFIER));