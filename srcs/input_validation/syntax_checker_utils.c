/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:46:43 by akaddour          #+#    #+#             */
/*   Updated: 2024/06/10 06:33:11 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*help_function(char *str)
{
	char	*result;
	int		check;

	result = ft_strdup("");
	while (*str != '\0')
	{
		check = 0;
		if (*str < 9 || *str > 13)
		{
			if (!(ft_isspace(*str) && *(str + 1) == '\0'))
				if (!ft_isspace(*str))
					result = ft_strjoin_2(result, str, 1);
			while (ft_isspace(*str) && *str != '\0')
			{
				str++;
				check = 1;
			}
		}
		if (check == 0)
			str++;
	}
	return (result);
}

char	*epur_str(char *str)
{
	int		i;

	i = -1;
	while ((str[++i] >= 9 && str[i] <= 13) || str[i] == 32)
		;
	str = str + i;
	return (help_function(str));
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
		if (!check_redirection_operator(&input, &s_q, &d_q))
			return (false);
		input++;
	}
	return (true);
}

t_bool	has_misplaced_operators_2(const char *input)
{
	t_operator_data	data;

	init_var(&data);
	if ((*input == '|' || *input == '&'))
		return (false);
	while (*input)
	{
		update_quote_counts(*input, &data.s_q, &data.d_q);
		if (!(data.s_q % 2) && !(data.d_q % 2)
			&& (*input == '|' || *input == '&'))
		{
			if (is_misplaced_operator(input, &data))
				return (false);
			if (*(input + 1) == *input)
				input++;
		}
		else if (!ft_isspace(*input))
		{
			data.next_command = 0;
			data.enc_and_or = false;
		}
		input++;
	}
	return (!data.next_command);
}
