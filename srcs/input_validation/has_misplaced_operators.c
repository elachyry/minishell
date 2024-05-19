/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_misplaced_operators.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:41:36 by melachyr          #+#    #+#             */
/*   Updated: 2024/05/19 12:16:22 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



t_bool has_misplaced_operators(const char *input) {
    int expect_command_next = 0;
    int s_q_count = 0;
    int d_q_count = 0;
    t_bool encountered_and_or = false;

    if (*input == '|' || *input == '&')
        return false;
    while (*input) {
        update_quote_counts(*input, &s_q_count, &d_q_count);
        if (!(s_q_count % 2) && !(d_q_count % 2) && (*input == '|' || *input == '&')){
			if (*(input + 1) == ')' || *(input - 1) == '(')
				return (false);
            if (!encountered_and_or) {
                encountered_and_or = true;
                const char *temp = input;
                temp++;
                if (*temp == *input) {
                    temp++;
                    if (*temp == *input) {
                        return false; // Return false if there are three consecutive | or & characters
                    }
                    input++;
                    continue;
                }
            }
            if (expect_command_next)
                return false;
            expect_command_next = 1;
        } else if (!ft_isspace(*input)) {
            expect_command_next = 0;
            encountered_and_or = false;
        }
        input++;
    }
    if (expect_command_next)
        return false;
    return true;
}
