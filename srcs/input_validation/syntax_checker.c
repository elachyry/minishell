/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:50:49 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/22 00:28:06 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*epur_str(char *str)
{
	int		i;
	int		l;
	char	*tmp;
	char	*result;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	tmp = str + i;
	result = ft_strdup("");
	while (*tmp != '\0')
	{
		l = 0;
		if (*tmp < 9 || *tmp > 13)
		{
			if (!(ft_isspace(*tmp) && *(tmp + 1) == '\0'))
				if (!ft_isspace(*tmp))
					result = ft_strjoin_2(result, tmp, 1);
			while (ft_isspace(*tmp) && *tmp != '\0')
			{
				tmp++;
				l = 1;
			}
		}
		if (l == 0)
			tmp++;
	}
	return (result);
}

t_bool	has_invalid_single_ampersand(const char *input)
{
	int			s_q_count;
	int			d_q_count;
	const char	*temp;

	s_q_count = 0;
	d_q_count = 0;
	while (*input)
	{
		update_quote_counts(*input, &s_q_count, &d_q_count);
		if (!(s_q_count % 2) && !(d_q_count % 2) && *input == '&')
		{
			temp = input + 1;
			while (*temp == ' ' || *temp == '\t')
				temp++;
			if (*temp != '&' && *temp != '\0' && *(input - 1) != '&')
				return (false);
		}
		input++;
	}
	return (true);
}

t_bool	has_misplaced_operators_2(const char *input)
{
	int			next_command;
	int			s_q;
	int			d_q;
	t_bool		enc_and_or;
	const char	*temp;

	init_var(&next_command, &s_q, &d_q, &enc_and_or);
	if (*input == '|' || *input == '&')
		return (false);
	while (*input)
	{
		update_quote_counts(*input, &s_q, &d_q);
		if (!(s_q % 2) && !(d_q % 2) && (*input == '|' || *input == '&'))
		{
			if (operator_mispla(&input, &next_command, &enc_and_or, &temp))
				return (false);
		}
		else if (!ft_isspace(*input))
		{
			next_command = 0;
			enc_and_or = false;
		}
		input++;
	}
	return (!next_command);
}

t_bool	has_invalid_redirections_2(const char *input)
{
	int		s_q;
	int		d_q;
	t_bool	enc_and_or;

	s_q = 0;
	d_q = 0;
	enc_and_or = false;
	while (*input)
	{
		update_quote_counts(*input, &s_q, &d_q);
		if (!check_redirection_operator(&input, &s_q, &d_q, &enc_and_or))
			return (false);
		input++;
	}
	return (true);
}

t_bool	syntax_error_checker(char	*input)
{
	char	*str;

	g_shell_data.line = ft_strtrim(input, " \t\n\v\f\r");
	str = epur_str(g_shell_data.line);
	if (ft_strncmp(g_shell_data.line, "", 1) == 0)
		return (false);
	if (!has_misplaced_operators(str)
		|| !has_misplaced_operators_2(g_shell_data.line)
		|| !has_invalid_redirections(str)
		|| !has_invalid_redirections_2(g_shell_data.line)
		|| !has_unclosed_quotes(g_shell_data.line)
		|| !has_unclosed_parenthesis(g_shell_data.line)
		|| !has_invalid_single_ampersand(g_shell_data.line))
	{
		free(g_shell_data.line);
		printf("syntax error\n");
		return (false);
	}
	return (true);
}
