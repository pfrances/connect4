/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_with_error_check.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 13:49:04 by pfrances          #+#    #+#             */
/*   Updated: 2023/07/02 15:14:09 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "connect4.h"

static char	*check_sign(char *str_nbr, int *sign)
{
	if (*str_nbr == '+')
		return (str_nbr + 1);
	else if (*str_nbr == '-')
	{
		*sign = -1;
		return (str_nbr + 1);
	}
	else
		return (str_nbr);
}

int	ft_atoi_with_error_check(const char *nptr, bool *error_flag)
{
	long long	result;
	int			sign;
	char		*str_nbr;

	str_nbr = (char *)nptr;
	while (ft_isspace(*str_nbr))
		str_nbr++;
	sign = 1;
	str_nbr = check_sign(str_nbr, &sign);
	result = 0;
	if (!ft_isdigit(*str_nbr) || *str_nbr == '\0')
		return (0);
	while (*str_nbr != '\0' && ft_isdigit(*str_nbr))
	{
		result = result * 10 + (*str_nbr - '0');
		if (result - (sign == -1) > INT_MAX)
			return (0);
		str_nbr++;
	}
	if (*str_nbr == '\0')
		*error_flag = false;
	return ((int)(result * sign));
}
