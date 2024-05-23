/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 00:19:45 by akaddour          #+#    #+#             */
/*   Updated: 2024/05/23 00:21:11 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_d_q(char current_char, int in_single_quotes, \
int in_double_quotes, t_token *token)
{
	if (current_char == '\"' && !in_single_quotes)
	{
		if (token->prev && token->prev->type == DoubleLessThanOperator)
			g_shell_data.simple_cmd->should_expand = false;
		in_double_quotes = !in_double_quotes;
	}
	return (in_double_quotes);
}

int	handle_s_q(char current_char, int in_double_quotes, \
int in_single_quotes, t_token *token)
{
	if (current_char == '\'' && !in_double_quotes)
	{
		if (token->prev && token->prev->type == DoubleLessThanOperator)
			g_shell_data.simple_cmd->should_expand = false;
		in_single_quotes = !in_single_quotes;
	}
	return (in_single_quotes);
}

char	*allocate_new_str(int length)
{
	char	*new_str;

	new_str = malloc(length + 1);
	if (!new_str)
		return (NULL);
	return (new_str);
}

char	*remove_all_quotes(t_token *token, char *str)
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
		in_d_q = handle_d_q(str[i], in_s_q, in_d_q, token);
		in_s_q = handle_s_q(str[i], in_d_q, in_s_q, token);
		if (!(str[i] == '\"' && !in_s_q) && !(str[i] == '\'' && !in_d_q))
		{
			new_str[j] = str[i];
			j++;
		}
	}
	new_str[j] = '\0';
	return (new_str);
}
