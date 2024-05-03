/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 21:37:53 by akaddour          #+#    #+#             */
/*   Updated: 2023/11/18 10:27:39 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_sign(int neg)
{
	if (neg == 1)
		return (-1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	res;
	int		neg;

	i = 0;
	res = 0;
	neg = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		if (res > (9223372036854775807 - (str[i] - '0')) / 10)
			return (check_sign(neg));
		res = (str[i] - '0') + (res * 10);
		i++;
	}
	return ((int)res * neg);
}
